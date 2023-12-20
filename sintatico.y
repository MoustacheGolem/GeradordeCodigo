%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "codegen.h"

	//#define YYDEBUG 1

	extern FILE *yyin;
	extern FILE *yyout;

	// Tabela de símbolos
	struct regTabSimb {
		char *nome;
		char *tipo;
		int locMem;
		struct regTabSimb *prox; /* ponteiro */
	};

	typedef struct regTabSimb regTabSimb;
	regTabSimb *tabSimb = (regTabSimb *)0;
	regTabSimb *colocaSimb();
	
	int erroSemantico;

	static int proxLocMemVar = 0;
	int locMemId = 0; 

	static int labelIf = 0;
	static int labelFor = 0;
	static int labelWhile = 0;

	char *type_info;
	int val_info = 1;
	static struct astNode* astRoot;

	char* concatNum(char *src, int num);
	char* recuperaTipo(char *nomeSimb);

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
		switch(erroSemantico){
			case(1):
				printf("\nErro semantico: Variavel não declarada");
			break;
			case(2):
				printf("\nErro semantico: variavel ja declarada anteriormente");
			break;
			default:
			break;
		}

		if(erroSemantico == 0)
		{
			astNode* dec = appendNodes(createAstNode(AST_SECTION,(union ARG) 0, (union ARG) 0, (union ARG) 0, ".data"), 
								appendNodes(createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, "buffer"),$1));
			astNode* cmds = appendNodes(createAstNode(AST_SECTION,(union ARG) 0, (union ARG) 0, (union ARG) 0, ".text"), $3);
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
			appendNodes(createAstNode(AST_JEQ, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("IFEND", labelIf), ""), 
				appendNodes($6, createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,concatNum("ENDIF", labelIf)))));
		labelIf++;
		
	}
	|   IF '(' expr ')' '{' lista_cmds '}' ELSE '{'lista_cmds '}' 
	{
		astNode* nodeLeft = 
		appendNodes($3 , 
			appendNodes(createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("ELSE",labelIf), ""), 
					appendNodes($6,
						 createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("ENDIF", labelIf), ""))));

		astNode* nodeRight = 
		appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, concatNum("ELSE",labelIf)),
			appendNodes($10, createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, concatNum("ENDIF",labelIf))));

		
		$$ = appendNodes(nodeLeft, nodeRight);
		labelIf++;
	}
;

stmt_while: WHILE '(' expr ')' '{' lista_cmds'}'  
	{
		$$ = 
		appendNodes(createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("WHILE", labelWhile), ""),
			appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("WHILEB", labelWhile)) ,
				appendNodes($6,
					appendNodes($3, 
						appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("WHILE", labelWhile)), 
							createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("WHILEB", labelWhile), ""))))));
		labelWhile++;
	}
;

stmt_for: FOR '(' for_atr  for_expr  final_for  '{' lista_cmds'}'  
	{
		$$ = appendNodes($3, 
				appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("FOR", labelFor)),
					appendNodes($4,
						appendNodes(createAstNode(AST_JLE, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("ENDFOR", labelFor), ""),
							appendNodes($7,
								appendNodes($5,
									appendNodes(createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("FOR", labelFor), ""), 
										createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("ENDFOR", labelFor)))))))));
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
		$$ = appendNodes($3, createAstNode(AST_OUT, (union ARG) RS, (union ARG) 0, (union ARG) 0, recuperaTipo($3)));

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
		$$ = createAstNode(AST_LI, (union ARG) RS, (union ARG) ZERO,(union ARG)$1, "");
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
		$$ = createAstNode(AST_LI, (union ARG) AC, (union ARG) ZERO, (union ARG) $1, "");
	}
	|	ID
	{
		if (!constaTabSimb($1)) 
		{

		  erroSemantico = 1;
		  $$ = createAstNode(AST_ERROR,(union ARG) 0, (union ARG) 0, (union ARG) 0, "");
		} else {
		  locMemId = recuperaLocMemId($1);
		   $$ = createAstNode(AST_LD, (union ARG) AC, (union ARG)0, (union ARG)AU, $1) ;
		}
	}
;

%%


// ------------------------------------------------ SEMANTICO ------------------------------------------------


regTabSimb *colocaSimb(char *nomeSimb, char *tipoSimb, char *naturezaSimb, char *usadoSimb,int loc){
	regTabSimb *ptr;
	ptr = (regTabSimb *) malloc (sizeof(regTabSimb));

	ptr->nome= (char *) malloc(strlen(nomeSimb)+1);
	ptr->tipo= (char *) malloc(strlen(tipoSimb)+1);

	strcpy (ptr->nome,nomeSimb);
	strcpy (ptr->tipo,tipoSimb);
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

char * recuperaTipo(char *nomeSimb){
	regTabSimb *ptr;
	for (ptr=tabSimb; ptr!=(regTabSimb *)0; ptr=(regTabSimb *)ptr->prox)
	  if (strcmp(ptr->nome,nomeSimb)==0)
	  {
		return ptr->tipo;
	  } 
	return "";
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
	// yydebug=1;

	erroSemantico=0;

	yyin = fopen("entrada.cm","rt");
	yyout = fopen("saida.s","wt");

	yyparse ();
	generateCode(yyout, astRoot);

	fclose(yyin);
	fclose(yyout);
	
}
yyerror (s) /* Called by yyparse on error */
	char *s;
{
	printf ("Problema com a analise sintatica: %s!\n", s);
}
