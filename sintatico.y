%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "code.h"
	#include "sintatic_tree.h"

	//#define YYDEBUG 1

	extern FILE *yyin;
	extern FILE *yyout;

	// SEMANTICO
	struct regTabSimb {
		char *nome; /* nome do simbolo */
		char *tipo; /* tipo_int ou tipo_cad ou nsa */
		char *natureza; /* variavel ou procedimento */
		char *usado; /* sim ou nao */
		int locMem;
		struct regTabSimb *prox; /* ponteiro */
	};

	typedef struct regTabSimb regTabSimb;
	regTabSimb *tabSimb = (regTabSimb *)0;
	regTabSimb *colocaSimb();
	int erroSemantico;

	static int proxLocMemVar = 0;
	// FIM SEMANTICO

	// GERA CODIGO
	int locMemId = 0; /* para recuperacao na TS */

	/* TM location number for current instruction emission */
	static int emitLoc = 0 ;

	/* Highest TM location emitted so far
	For use in conjunction with emitSkip,
	emitBackup, and emitRestore */
	static int highEmitLoc = 0;
	// FIM GERA CODIGO

	static int labelIf = 0;
	static int labelFor = 0;
	static int labelWhile = 0;

	char *type_info;
	int val_info = 1;
	static struct astNode* astRoot;

%}

// ------------------------------------------------ TIPOS e PRIORIDADE ------------------------------------------------

%union{
	int inteiro;
	char *cadeia;
	struct astNode* node;
}

%token INT CHAR
%token INTEIRO ESCREVA
%token <inteiro> NUM 
%token <cadeia> ID 
%token IF ELSE              
%token WHILE FOR RETURN EXTERN VOID
%token  ADD SUB DIV MUL

%left ADD SUB UMINUS
%left DIV MUL

%type <inteiro> binop term expr term2
%type <cadeia> type 
%type <node> declaracoes lista_id linha_decl lista_cmds cmd stmt cmd_saida cmd_atribuicao stmt_if stmt_while 
 
%nonassoc THEN
%nonassoc ELSE

%%

// ------------------------------------------------ SINTATICO------------------------------------------------

// TODO declaracoes no .data
programa: declaracoes '{' lista_cmds '}'
	{
		printf("\nok programa\n");
		switch(erroSemantico){
			case(0):
				printf("\nO programa não possui erros semânticos");
			break;
			case(1):
				printf("\nErro semantico: Variavel não declarada");
			break;

			case(2):
				printf("\nErro semantico: variavel ja declarada anteriormente");
			break;

			case(3):
				printf("\nErro semantico: ");
			break;
		}

		if(erroSemantico == 0)
		{
			astNode* dec = appendNodes(createAstNode(AST_LABEL,(union ARG) 0, (union ARG) 0, (union ARG) 0, ".data"), $1);
			// astNode* cmds = appendNodes(createAstNode(AST_LABEL,(union ARG) 0, (union ARG) 0, (union ARG) 0, ".text"), $3);
			astRoot = dec;
		}
		else
		{
			astRoot = createAstNode(AST_ERROR,(union ARG) 0, (union ARG) 0, (union ARG) 0, "");
		}

		YYACCEPT;
	}
;


declaracoes: linha_decl declaracoes	{$$ = appendNodes($1, $2); printf("la");}  
		|    linha_decl				{$$ = $1; printf("aq");}
;

linha_decl: type {type_info = $1;} lista_id ';'	{ $$ = $3; printf("%d/n", $3->type);}
;

type: 	INT		{$$ = "type_int"; }
		|CHAR	{$$ = "type_char";}
;

lista_id: ID ',' lista_id
	{
		if(constaTabSimb($1))
		{
			erroSemantico = 2;
			printf("\nSímbolos na tabel already");
		}

		colocaSimb($1,type_info,"variavel","nao",proxLocMemVar++);
		$$ = appendNodes(createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, $1), $3);
	}
	|  ID
	{	
		
		if(constaTabSimb($1))
		{
			erroSemantico = 2;
			printf("\nSímbolo na tabel already");
		}
		colocaSimb($1,type_info,"variavel","nao",proxLocMemVar++);
		$$ = createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, $1);
		
	}
	
;

lista_cmds:	cmd ';'					{$$ = $1;}
			| stmt					{$$ = $1;}
			| cmd ';' lista_cmds	{$$ = appendNodes($1, $3);}
			| stmt  lista_cmds 		{$$ = appendNodes($1, $2);}
;		
cmd:	 cmd_saida			{$$ = $1 ;}
		| cmd_atribuicao	{$$ = $1 ;}
;

stmt: 	stmt_if 		{$$ = $1;}
		| stmt_while 	{$$ = $1;}
		// | stmt_for 		{$$ = $1;}
;


stmt_if:  	IF '(' expr ')' '{' lista_cmds'}'   %prec THEN
	{
		    char result[50];
			sprintf(result, "%d", labelIf);
			printf("\nif");

		$$ = 
		appendNodes($3 , 
			appendNodes(createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) strcat("IF#", result), ""), 
				appendNodes($6, createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, strcat("IF#", result)))));
		labelIf++;
		
	} 
	|   IF '(' expr ')' '{' lista_cmds '}' ELSE '{'lista_cmds '}' 
	{
		char result[50];
		sprintf(result, "%d", labelIf);

		printf("\nifelse");
		astNode* nodeLeft = 
		appendNodes($3 , 
			appendNodes(createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) strcat("ELSE#", result), ""), 
					appendNodes($6,
						appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, ""), createAstNode(AST_JEQ, (union ARG) 0, (union ARG) 0, (union ARG) 0, strcat("ENDIF#", result))))));

		astNode* nodeRight = 
		appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, strcat("ELSE#", result)),
			appendNodes($3, createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, strcat("ENDIF#", result))));

		
		$$ = appendNodes(nodeLeft, nodeRight);
		labelIf++;
	}
;

stmt_while: WHILE '('expr')' '{' lista_cmds'}'  
	{
		char result[50];
		printf("\nwhile");
		sprintf(result, "%d", labelIf);
		$$ = 
		appendNodes(createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) 0, strcat("WHILE#", result)),
			appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  strcat("WHILEB#", result)) ,
				appendNodes($6,
					appendNodes($3, createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) strcat("WHILEB#", result), "")))));
		labelWhile++;
	}
;



// stmt_for: FOR '(' cmd_atribuicao  for_expr  expr ')' '{' lista_cmds'}'  
// 	{
// 		astNode* rootFor = NULL
// 		if($3 != NULL)
// 		{
// 			rootFor = $3
// 		}

// 		lastNode* labelFor = createAstNode(AST_LABEL, 0, 0, 0, "FOR#");
// 		rootFor == NULL ? rootFor = labelFor : rootFor.left = labelFor;


// 		lastNode* nodeExpr = createAstNode(AST_LABEL, 0, 0, 0, "FOR#");
// 		else if($4 != NULL)
// 		{
// 			rootFor.left == NULL ? rootFor.left = $4 : rootFor.right = nodeExpr.left = 4;
// 		}	

// 		root createAstNode(AST_JE, 0, 0, 0, "");

// 		else if($5 != NULL)
// 		{

// 		}
// 		createAstNode(AST_JE, 0, 0, 0, "");
// 		createAstNode(AST_LABEL, 0, 0, 0, "FINALFOR#");

// 	}
;

// for_atr:  term  
// 		| ';' { $$ = NULL; } 
// 		| cmd_atribuicao ';'
	
// 	{	
// 		if (!constaTabSimb($1)) 
// 		{
// 		  	erroSemantico = 1;
// 		} else{
// 			locMemId = recuperaLocMemId($1);
// 			emitRM("ST",ac,locMemId,gp,"atribuicao: armazena valor");
// 			$$ = createAstNode(AST_MUL, 0, 0, 0, "");
// 		}
// 	}
// ;
		
// // TODO ADD index for label
// for_expr: expr ';' 	{ $$ = createAstNode(AST_NONE, 0, 0, 0, ""); }
// 		| ';' 		{ $$ = NULL; }
// ;

cmd_saida:	ESCREVA '(' expr ')'
	{
		printf("\nescrvea");
		$$ = createAstNode(AST_OUT, (union ARG) RS, (union ARG) 0, (union ARG) 0, "");
	}
;

cmd_atribuicao: ID '=' expr
	{	
		printf("\natribui");
		if (!constaTabSimb($1)) 
		{
		  	erroSemantico = 1;
		  	$$ = appendNodes($3, createAstNode(AST_ERROR, (union ARG) 0, (union ARG) 0, (union ARG) 0, ""));
		} else
		{
			// push st
			locMemId = recuperaLocMemId($1);
			// emitRM("ST",ac,locMemId,gp,"atribuicao: armazena valor");
			$$ = appendNodes($3, createAstNode(AST_ST, (union ARG) RS, (union ARG) 0, (union ARG) locMemId, ""));
		}
		
	}
;


expr:	term 		{$$ = $1;}
	| 	expr binop term2 
	{
		printf("\nexpr");
        switch($2){
			case 1:
				$$ = appendNodes($1, 
						createAstNode(AST_ADD, (union ARG) RS, (union ARG) RS, (union ARG) AC, ""));
			break;

			case 2:
				$$ = appendNodes($1, 
						createAstNode(AST_SUB, (union ARG) RS, (union ARG) RS, (union ARG) AC, ""));
			break;

			case 3:
				$$ = appendNodes($1, 
						createAstNode(AST_MUL, (union ARG) RS, (union ARG) RS, (union ARG) AC, ""));
			break;

			case 4:
				$$ = appendNodes($1, 
						createAstNode(AST_DIV, (union ARG) RS, (union ARG) RS, (union ARG) AC, ""));
			break;

			// case 5:
			// 	emitRO("DIV",ac,ac,tmp,"divide operandos");
			// 	$$ = createAstNode(AST_LT, RS, AC, AU, "");
			// break;

			// case 6:
			// 	emitRO("DIV",ac,ac,tmp,"divide operandos");
			// 	$$ = createAstNode(AST_LE, RS, AC, AU, "");
			// break;

			// case 7:
			// 	emitRO("DIV",ac,ac,tmp,"divide operandos");
			// 	$$ = createAstNode(AST_GT, RS, AC, AU, "");
			// break;

			// case 8:
			// 	emitRO("DIV",ac,ac,tmp,"divide operandos");
			// 	$$ = createAstNode(AST_GE, RS, AC, AU, "");
			// break;

			// case 9:
			// 	emitRO("DIV",ac,ac,tmp,"divide operandos");
			// 	$$ = createAstNode(AST_EQ, RS, AC, AU, "");
			// break;
		}
	}
;

binop: 	ADD 	{$$ = 1;}
		|SUB 	{$$ = 2;}
		|MUL 	{$$ = 3;}
		|DIV 	{$$ = 4;}	
		// |LT 	{$$ = 5;}	
		// |LE 	{$$ = 6;}	
		// |GT 	{$$ = 7;}	
		// |GE 	{$$ = 8;}	
		// |EQ 	{$$ = 9;}	
;

term:	NUM
	{
		printf("\nterm");
		$$ = createAstNode(AST_ADDI, (union ARG) RS, (union ARG) ZERO,(union ARG)$1, "");
	}
	|	ID
	{
		if (!constaTabSimb($1)) 
		{
		  erroSemantico = 1;
		  $$ = createAstNode(AST_ERROR,(union ARG) 0, (union ARG) 0, (union ARG) 0, "");
		} else {
		  locMemId = recuperaLocMemId($1);
		  $$ = createAstNode(AST_LD, (union ARG) RS, (union ARG)0, (union ARG) locMemId, "");
		}
	}	
;	
	
term2:	NUM
	{
		$$ = createAstNode(AST_ADDI, (union ARG) AC, (union ARG) ZERO, (union ARG) $1, "");
	}
	|	ID
	{
		if (!constaTabSimb($1)) 
		{
		  erroSemantico = 1;
		  $$ = createAstNode(AST_ERROR,(union ARG) 0, (union ARG) 0, (union ARG) 0, "");
		} else {
		  locMemId = recuperaLocMemId($1);
		   $$ = appendNodes(createAstNode(AST_LD, (union ARG) AU, (union ARG)0, (union ARG)locMemId, "")  ,createAstNode(AST_ADD, (union ARG) AC, (union ARG) ZERO, (union ARG) AU, "")) ;
		}
	}
;

// func: type ID'(' declaracoes ')' '{' lista_cmds '}'
	// {
		// push label na lsita de comandos
		// push dos registradores store em todos
		// push na lsita de comandos
		// push loads
		// remove na tabela de simbolos
	// }
;

%%



// ------------------------------------------------ SEMANTICO ------------------------------------------------


regTabSimb *colocaSimb(char *nomeSimb, char *tipoSimb, char *naturezaSimb, char *usadoSimb,int loc){
	regTabSimb *ptr;
	ptr = (regTabSimb *) malloc (sizeof(regTabSimb));

	ptr->nome= (char *) malloc(strlen(nomeSimb)+1);
	ptr->tipo= (char *) malloc(strlen(tipoSimb)+1);
	ptr->natureza= (char *) malloc(strlen(naturezaSimb)+1);
	ptr->usado= (char *) malloc(strlen(usadoSimb)+1);

	strcpy (ptr->nome,nomeSimb);
	strcpy (ptr->tipo,tipoSimb);
	strcpy (ptr->natureza,naturezaSimb);
	strcpy (ptr->usado,usadoSimb);
	ptr->locMem= loc;

	ptr->prox= (struct regTabSimb *)tabSimb;
	tabSimb= ptr;
	return ptr;
}
int constaTabSimb(char *nomeSimb) {
	regTabSimb *ptr;
	for (ptr=tabSimb; ptr!=(regTabSimb *)0; ptr=(regTabSimb *)ptr->prox)
	  if (strcmp(ptr->nome,nomeSimb)==0) return 1;
	return 0;
}
// FIM SEMANTICO

// GERA CODIGO
void emitRO( char *op, int r, int s, int t, char *c)
{ fprintf(yyout,"%3d:  %5s  %d,%d,%d ",emitLoc++,op,r,s,t);
//  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(yyout,"\n") ;
//  if (highEmitLoc < emitLoc) highEmitLoc = emitLoc ;
} /* emitRO */

/* Procedure emitRM emits a register-to-memory
 * TM instruction
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM( char * op, int r, int d, int s, char *c)
{ fprintf(yyout,"%3d:  %5s  %d,%d(%d) ",emitLoc++,op,r,d,s);
//  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(yyout,"\n") ;
//  if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc ;
} /* emitRM */

// recupera locacao de memoria de um id cujo nome eh passado em parametro
int recuperaLocMemId(char *nomeSimb) {
	regTabSimb *ptr;
	for (ptr=tabSimb; ptr!=(regTabSimb *)0; ptr=(regTabSimb *)ptr->prox)
	  if (strcmp(ptr->nome,nomeSimb)==0) return ptr->locMem;
	return -1;
}
// printar estrutura da tabela de simbulos
void imprimeTabSimb(regTabSimb *tabSimb) {
  regTabSimb *ptr;
	printf("TabSimb:\n");
  for (ptr = tabSimb; ptr != NULL; ptr = ptr->prox) {
    printf("  Nome: %s ,", ptr->nome);
    printf("Tipo: %s ,", ptr->tipo);
    printf("Natureza: %s ,", ptr->natureza);
    printf("Usado: %s ,", ptr->usado);
    printf("LocMem: %d\n", ptr->locMem);
  }
}
// FIM GERA CODIGO

static int chups = 0;

void generateCode(FILE* file, astNode* node)
{
	printf("chups: %d\n", chups++);
	if(node == NULL)
	{
		return;
	}
	printf("tipo: %d\n", node->type);
	if(node->left != NULL)
	{
		generateCode(file, node->left);
	}
	printf("tipo1: %d\n", node->type);
	if(node->right != NULL)
	{
		generateCode(file, node->right);
	}
	printf("tipo2: %d\n", node->type);
	writeCode(file, node);
	printf("tipo3: %d\n", node->type);
}



int main(argc, argv) int argc; char **argv;
	{
	int ra, rd, rs, r, rz;


//	extern int yydebug;
	yydebug=1;

	erroSemantico=0;

	// ++argv; --argc; 	    /* abre arquivo de entrada se houver */
	// if(argc > 0)
	// 	yyin = fopen(argv[0],"rt");
	// else
	// 	yyin = stdin;    /* cria arquivo de saida se especificado */
	// if(argc > 1)
	// 	yyout = fopen(argv[1],"wt");
	// else
		// yyout = stdout;
	yyin = fopen("entrada.cm","rt");
	yyout = fopen("saida.tm","wt");

	yyparse ();
	generateCode(yyout, astRoot);
	imprimeTabSimb(tabSimb);
	//emitComment("End of execution.");
	// emitRO("HALT",0,0,0,"");

	fclose(yyin);
	fclose(yyout);
	
}
yyerror (s) /* Called by yyparse on error */
	char *s;
{
	printf ("Problema com a analise sintatica!\n", s);
}
