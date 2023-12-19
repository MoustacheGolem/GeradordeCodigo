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

	char* concatNum(char *src, int num);

%}

// ------------------------------------------------ TIPOS e PRIORIDADE ------------------------------------------------

%union{
	int inteiro;
	char *cadeia;
	struct astNode* node;
}

%token INT CHAR
%token INTEIRO ESCREVA ENTRADA
%token <inteiro> NUM 
%token <cadeia> ID 
%token IF ELSE              
%token WHILE FOR 
%token ADD SUB DIV MUL
%token AND OR LT GT LE GE EQ DIF

%left ADD SUB UMINUS
%left DIV MUL

%type <inteiro> binop logop 
%type <cadeia> type 
%type <node> declaracoes lista_id linha_decl lista_cmds cmd stmt cmd_saida cmd_atribuicao  cmd_entrada  
%type <node> stmt_if stmt_while stmt_for for_atr for_expr final_for term expr term2 
 
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

		buffer:

		if(erroSemantico == 0)
		{
			astNode* dec = appendNodes(createAstNode(AST_SECTION,(union ARG) 0, (union ARG) 0, (union ARG) 0, ".section .data"), 
								appendNodes(createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, "buffer"),$1));
			astNode* cmds = appendNodes(createAstNode(AST_SECTION,(union ARG) 0, (union ARG) 0, (union ARG) 0, ".section .text"), $3);
			astRoot = appendNodes(dec,appendNodes(cmds,createAstNode(AST_HALT,(union ARG) 0, (union ARG) 0, (union ARG) 0, "")));
		}
		else
		{
			astRoot = createAstNode(AST_ERROR,(union ARG) 0, (union ARG) 0, (union ARG) 0, "");
		}

		YYACCEPT;
	}
;


declaracoes: linha_decl declaracoes	{$$ = appendNodes($1, $2);}  
		// |	 linha_func declaracoes
		|    linha_decl				{$$ = $1;}
;

linha_decl: type {type_info = $1;} lista_id ';'	{ $$ = $3;}
;

type: 	INT		{$$ = "type_int"; }
		|CHAR	{$$ = "type_char";}
;

lista_id: ID ',' lista_id
	{
		if(constaTabSimb($1))
		{
			erroSemantico = 2; 
		}

		colocaSimb($1,type_info,"variavel","nao",proxLocMemVar++);
		$$ = appendNodes(createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, $1), $3);
	}
	|  ID
	{	
		
		if(constaTabSimb($1))
		{
			erroSemantico = 2;
		}
		colocaSimb($1,type_info,"variavel","nao",proxLocMemVar++);
		$$ = createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, $1);
		
	}
	
;

// TODO empilhar contexto
// lista_func: func ';'
// 			func lista_func ';'
// ;

// func: type ID '(' func_args ')' '{' lista_cmds '}'
// ;

// func_args: func_arg
// 		 | func_arg ',' func_args 
// ;

// func_arg: type ID
// ;


lista_cmds:	cmd ';'					{$$ = $1; }
			| stmt					{$$ = $1;}
			| cmd ';' lista_cmds	{$$ = appendNodes($1, $3);}
			| stmt  lista_cmds 		{$$ = appendNodes($1, $2);}
;		
cmd:	 cmd_saida			{$$ = $1 ;}
		| cmd_entrada		{$$ = $1 ;}
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
			appendNodes(createAstNode(AST_JEQ, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("IFEND#", labelIf), ""), 
				appendNodes($6, createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,concatNum("ENDIF#", labelIf)))));
		labelIf++;
		
	}
	|   IF '(' expr ')' '{' lista_cmds '}' ELSE '{'lista_cmds '}' 
	{
		astNode* nodeLeft = 
		appendNodes($3 , 
			appendNodes(createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("ELSE#",labelIf), ""), 
					appendNodes($6,
						 createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("ENDIF#", labelIf), ""))));

		astNode* nodeRight = 
		appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, concatNum("ELSE#",labelIf)),
			appendNodes($10, createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, concatNum("ENDIF#",labelIf))));

		
		$$ = appendNodes(nodeLeft, nodeRight);
		labelIf++;
	}
;

stmt_while: WHILE '(' expr ')' '{' lista_cmds'}'  
	{
		$$ = 
		appendNodes(createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("WHILE#", labelWhile), ""),
			appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("WHILEB#", labelWhile)) ,
				appendNodes($6,
					appendNodes($3, 
						appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("WHILE#", labelWhile)), 
							createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("WHILEB#", labelWhile), ""))))));
		labelWhile++;
	}
;

stmt_for: FOR '(' for_atr  for_expr  final_for  '{' lista_cmds'}'  
	{
		$$ = appendNodes($3, 
				appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("FOR#", labelFor)),
					appendNodes($4,
						appendNodes(createAstNode(AST_JLE, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("ENDFOR#", labelFor), ""),
							appendNodes($7,
								appendNodes($5,
									appendNodes(createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("FOR#", labelFor), ""), 
										createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("ENDFOR#", labelFor)))))))));
	}
;

for_atr:  ';' 
	{ $$ = createAstNode(AST_NONE, (union ARG) ZERO, (union ARG) ZERO, (union ARG) "", ""); }
		| term  ';'
	
	{ $$ = $1; }
		| cmd_atribuicao ';'
	{ $$ = $1; }  
;
		
for_expr:  ';' 			{ $$ = createAstNode(AST_NONE, (union ARG) ZERO, (union ARG) ZERO, (union ARG) "", ""); }
		| 	expr ';' 	{ $$ = $1 ;}
		
;

final_for:  ')'  { $$ = createAstNode(AST_NONE, (union ARG) ZERO, (union ARG) ZERO, (union ARG) "", "") ;}
			|  cmd_atribuicao ')' { $$ = $1 ;}
;

cmd_saida:	ESCREVA '(' expr ')'
	{ 
		$$ = appendNodes($3, createAstNode(AST_OUT, (union ARG) RS, (union ARG) 0, (union ARG) 0, ""));
	}
;

cmd_entrada:	ENTRADA '('	ID ')'
	{ 
		
		if (!constaTabSimb($3)) 
		{
		  	erroSemantico = 1;
		  	$$ = appendNodes($3, createAstNode(AST_ERROR, (union ARG) 0, (union ARG) 0, (union ARG) 0, ""));
		} else
		{
			locMemId = recuperaLocMemId($3);
			$$ = appendNodes(createAstNode(AST_IN, (union ARG) RS, (union ARG) 0, (union ARG) 0, ""), 
					createAstNode(AST_LD, (union ARG) RS, (union ARG) 0, (union ARG) AC, $3));
		}
	}
;

cmd_atribuicao: ID '=' expr
	{	
		
		if (!constaTabSimb($1)) 
		{
		  	erroSemantico = 1;
		  	$$ = appendNodes($3, createAstNode(AST_ERROR, (union ARG) 0, (union ARG) 0, (union ARG) 0, ""));
		} else
		{
			locMemId = recuperaLocMemId($1);
			$$ = appendNodes($3, createAstNode(AST_ST, (union ARG) RS, (union ARG) 0, (union ARG) AC, $1));
		}
		
	}
;


expr:	term 		{ $$ = $1; }
	| 	expr binop term2 
	{
        switch($2){
			case 1:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_ADD, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 2:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_SUB, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 3:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_MUL, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 4:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_DIV, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;
		}
	}

	| 	expr logop term2 
	{
        switch($2){
			case 1:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_GE, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 2:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_LE, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 3:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_GT, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 4:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_LT, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 5:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_EQ, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 6:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_DIF, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 7:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_AND, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 8:
				$$ = appendNodes($1, 
						appendNodes($3, 
							createAstNode(AST_OR, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;
		}
	}
;

binop: 	ADD 	{$$ = 1;}
		|SUB 	{$$ = 2;}
		|MUL 	{$$ = 3;}
		|DIV 	{$$ = 4;}	
;

logop: 	GE 		{$$ = 1;}		
		|LE 	{$$ = 2;}		
		|GT 	{$$ = 3;}		
		|LT 	{$$ = 4;}		
		|EQ 	{$$ = 5;}		
		|DIF 	{$$ = 6;}		
		|AND 	{$$ = 7;}		
		|OR 	{$$ = 8;}	
;

term:	NUM
	{
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
		  $$ = createAstNode(AST_LD, (union ARG) RS, (union ARG)0, (union ARG) AC, $1);
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
		   $$ = appendNodes(createAstNode(AST_LD, (union ARG) AU, (union ARG)0, (union ARG)0, "")  ,createAstNode(AST_ADD, (union ARG) AC, (union ARG) ZERO, (union ARG) AU, "")) ;
		}
	}
;

%%


// ------------------------------------------------ SEMANTICO ------------------------------------------------

// TODO se for fazer função fazer removeSimb = código para remvoer node de lista de encadeada

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

int recuperaLocMemId(char *nomeSimb) {
	regTabSimb *ptr;
	for (ptr=tabSimb; ptr!=(regTabSimb *)0; ptr=(regTabSimb *)ptr->prox)
	  if (strcmp(ptr->nome,nomeSimb)==0) return ptr->locMem;
	return -1;
}

char* concatNum(char *src, int num) {
	int length = strlen(src) + snprintf(NULL, 0, "%d", num) + 1;
 	char *result = malloc(length);

    if (result == NULL) {
        return NULL;  
	}

    sprintf(result, "%s%d", src, num);

    return result;
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


void generateCode(FILE* file, astNode* node)
{
	if(node == NULL)
	{
		return;
	}
	if(node->left != NULL)
	{
		generateCode(file, node->left);
	}
	if(node->right != NULL)
	{
		generateCode(file, node->right);
	}
	writeCode(file, node);
}



int main(argc, argv) int argc; char **argv;
	{
	yydebug=1;

	erroSemantico=0;

	yyin = fopen("entrada.cm","rt");
	yyout = fopen("saida.s","wt");

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
	printf ("Problema com a analise sintatica: %s!\n", s);
}
