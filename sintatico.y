%{
	#include <stdio.h>
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
	static int labelIWhile = 0;


	char *type_info;
	int val_info = 1;
%}

// ------------------------------------------------ TIPOS e PRIORIDADE ------------------------------------------------

%union{
	int inteiro;
	char *cadeia;
	astNode* node;
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
%type <cadeia> type lista_id

%nonassoc THEN
%nonassoc ELSE

%%

// ------------------------------------------------ SINTATICO------------------------------------------------

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
			astRoot = $3;
		}
		else
		{
			astRoot = createAstNode(AST_ERROR, 0, 0, 0, "");
		}
		

		YYACCEPT;
	}
;


declaracoes: linha_decl				{;}
		| linha_decl declaracoes 	{;}
;

linha_decl: type {type_info = $1;} lista_id ';'	{}
;

type: 	INT		{$$ = "type_int"; }
		|CHAR	{$$ = "type_char";}
;

lista_id: ID
	{	
		
		if(constaTabSimb($1))
		{
			erroSemantico = 2;a
		}

		colocaSimb($1,type_info,"variavel","nao",proxLocMemVar++);
	}
	| ID ',' lista_id
	{
		if(constaTabSimb($1))
		{
			erroSemantico = 2;
		}
		else
		colocaSimb($1,type_info,"variavel","nao",proxLocMemVar++);
	}
;

lista_cmds:	cmd ';'					{$$ = $1;}
			| stmt					{$$ = $1;}
			| cmd ';' lista_cmds	{$$ = appendNodes($1, $2);}
			| stmt lista_cmds 		{$$ = appendNodes($1, $2);}
;		

cmd:	 cmd_saida			{$$ = $1 ;}
		| cmd_atribuicao	{$$ = $1 ;}
;

stmt: 	stmt_if 		{$$ = $1;}
		| stmt_while 	{$$ = $1;}
		| stmt_for 		{$$ = $1;}
;


stmt_if:  	IF '(' expr ')' '{' lista_cmds'}'   %prec THEN
	{
		$$ = 
		appendNodes($3 , 
			appendNodes(createAstNode(AST_JGT, RS, ZERO, "IF#"+atoi(labelIf), ""), 
				appendNodes($6, createAstNode(AST_LABEL, 0, 0, 0, "IF#"+atoi(labelIf)))));
		labelIf++;
		
	} 
	|   IF '(' expr ')' '{' lista_cmds '}' ELSE '{'lista_cmds '}' 
	{
		astNode* nodeLeft = 
		appendNodes($3 , 
			appendNodes(createAstNode(AST_JGT, RS, ZERO, "ELSE#"+atoi(labelIf), ""), 
					appendNodes($6, 
						appendNodes(createAstNode(AST_LABEL, 0, 0, 0, "")), createAstNode(AST_JEQ, 0, 0, 0, "ENDIF#"+atoi(labelIf)))));

		astNode* nodeRight = 
		appendNodes(createAstNode(AST_LABEL, 0, 0, 0, "ELSE#"+atoi(labelIf)),
			appendNodes($10, createAstNode(AST_LABEL, 0, 0, 0, "ENDIF#"+atoi(labelIf))));

		
		$$ = appendNodes(nodeLeft, nodeRight);
		labelIf++;
	}
;

stmt_while: WHILE '('expr')' '{' lista_cmds'}'  
	{
		$$ = 
		appendNodes(createAstNode(AST_JEQ, ZERO, ZERO, 0, "WHILE#"+atoi(labelWhile)),
			appendNode(createAstNode(AST_LABEL, 0, 0, 0, "WHILEB#"+atoi(labelWhile)) ,
				appendNodes($6,
					appendNodes($3, createAstNode(AST_JGT, RS, ZERO, "WHILEB#"+atoi(labelWhile), "")))));
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
		$$ = createAstNode(AST_OUT, RS, 0, 0, "");
		emitRO("OUT",ac,0,0,"escreve ac");
	}
;

cmd_atribuicao: ID '=' expr
	{	
		if (!constaTabSimb($1)) 
		{
		  	erroSemantico = 1;
		  	$$ = createAstNode(AST_ERROR, 0, 0, 0, "");
		} else
		{
			// push st
			locMemId = recuperaLocMemId($1);
			emitRM("ST",ac,locMemId,gp,"atribuicao: armazena valor");
			$$ = createAstNode(AST_ST, RS, 1, locMemId, "");
		}
		
	}
;


expr:	term
	| 	expr binop term2 
	{
        switch($2){
			// TODO see registers
			case 1:
				emitRO("ADD",ac,ac,tmp,"soma operandos");
				$$ = createAstNode(AST_ADD, RS, AC, AU, "");
			break;

			case 2:
				emitRO("SUB",ac,ac,tmp,"subtrai operandos");
				$$ = createAstNode(AST_SUB, RS, AC, AU, "");
			break;

			case 3:
				emitRO("MUL",ac,ac,tmp,"multiplica operandos");
				$$ = createAstNode(AST_MUL, RS, AC, AU, "");
			break;

			case 4:
				emitRO("DIV",ac,ac,tmp,"divide operandos");
				$$ = createAstNode(AST_DIV, RS, AC, AU, "");
			break;

			case 5:
				emitRO("DIV",ac,ac,tmp,"divide operandos");
				$$ = createAstNode(AST_LT, RS, AC, AU, "");
			break;

			case 6:
				emitRO("DIV",ac,ac,tmp,"divide operandos");
				$$ = createAstNode(AST_LE, RS, AC, AU, "");
			break;

			case 7:
				emitRO("DIV",ac,ac,tmp,"divide operandos");
				$$ = createAstNode(AST_GT, RS, AC, AU, "");
			break;

			case 8:
				emitRO("DIV",ac,ac,tmp,"divide operandos");
				$$ = createAstNode(AST_GE, RS, AC, AU, "");
			break;

			case 9:
				emitRO("DIV",ac,ac,tmp,"divide operandos");
				$$ = createAstNode(AST_EQ, RS, AC, AU, "");
			break;
		}
	}
;

binop: 	ADD 	{$$ = 1;}
		|SUB 	{$$ = 2;}
		|MUL 	{$$ = 3;}
		|DIV 	{$$ = 4;}	
		|LT 	{$$ = 5;}	
		|LE 	{$$ = 6;}	
		|GT 	{$$ = 7;}	
		|GE 	{$$ = 8;}	
		|EQ 	{$$ = 9;}	
;

term:	NUM
	{
		emitRM("LDC",ac,$1*val_info,0,"carrega constante em ac");
		$$ = createAstNode(AST_ADDI, AC, zero, $1, "");
	}
	|	ID
	{
		if (!constaTabSimb($1)) 
		{
		  erroSemantico = 1;
		  $$ = NULL;
		} else {
		  locMemId = recuperaLocMemId($1);
		  emitRM("LD",ac,locMemId,gp,"carrega valor de id em ac");
		  $$ = appendNode(createAstNode(AST_LD, RS, 1, locMemId, "")  ,createAstNode(AST_ADD, AC, ZERO, RS, "")) ;
		}
	}	
;	
	
term2:	NUM
	{
		emitRM("LDC",tmp,$1,0,"carrega constante em ac");
		$$ = createAstNode(AST_ADDI, AU, zero, $1, "");
	}
	|	ID
	{
		if (!constaTabSimb($1)) 
		{
		  erroSemantico = 1;
		  $$ = NULL;
		} else {
		  locMemId = recuperaLocMemId($1);
		  emitRM("LD",tmp,locMemId,gp,"carrega valor de id em ac");
		   $$ = appendNode(createAstNode(AST_LD, RS, 1, locMemId, "")  ,createAstNode(AST_ADD, AU, ZERO, RS, "")) ;
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

int main(argc, argv) int argc; char **argv;
	{
	int ra, rd, rs, r, rz, ra;


//	extern int yydebug;
//	yydebug=1;

	erroSemantico=0;

	++argv; --argc; 	    /* abre arquivo de entrada se houver */
	if(argc > 0)
		yyin = fopen(argv[0],"rt");
	else
		yyin = stdin;    /* cria arquivo de saida se especificado */
	if(argc > 1)
		yyout = fopen(argv[1],"wt");
	else
		yyout = stdout;
		//yyout = fopen("saida.tm","wt");

	//emitComment("Standard prelude:");
	emitRM("LD",mp,0,ac,"load maxaddress from location 0");
	emitRM("ST",ac,0,ac,"clear location 0");
	//emitComment("End of standard prelude.");

	yyparse ();
	imprimeTabSimb(tabSimb);
	//emitComment("End of execution.");
	emitRO("HALT",0,0,0,"");

		fclose(yyin);
		fclose(yyout);
	
}
yyerror (s) /* Called by yyparse on error */
	char *s;
{
	printf ("Problema com a analise sintatica!\n", s);
}
