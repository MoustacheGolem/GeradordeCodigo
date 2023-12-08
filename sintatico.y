/* gera codigo para cmd de saida com constante numerica inteira */
%{
#include <stdio.h>
#include "code.h"


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

char *type_info;
int val_info = 1;
%}
%union{
	int inteiro;
	char *cadeia;

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
programa:	declaracoes '{' lista_cmds '}'
	{
		printf("\nSintaxe ok.\n");
		switch(erroSemantico){
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
			
		
		if (erroSemantico <= 0) {
			printf("\nSemantica ok: se variaveis usadas, elas foram declaradas ok.\n");;
			
		}

		YYACCEPT;
	}
;


declaracoes: linha_decl			{;}
		| linha_decl declaracoes	{;}
;

linha_decl: type {type_info = $1;} lista_id ';'	{}
;

type: 	INT		{$$ = "type_int"; }
		|CHAR	{$$ = "type_char";}
;

lista_id: ID
	{	
		
		if(constaTabSimb($1)){
			// printf("variavel já declarada\n");
			erroSemantico = 2;//erro variavel já declarada
		}
		// printf("declarando id\n");
		colocaSimb($1,type_info,"variavel","nao",proxLocMemVar++);
	}
	| ID ',' lista_id
	{
		if(constaTabSimb($1)){
			// printf("variavel já declarada\n");
			erroSemantico = 2;//erro variavel já declarada
		}
		// printf("declarando id\n");
		colocaSimb($1,type_info,"variavel","nao",proxLocMemVar++);
	}
;
lista_cmds:	cmd ';'				{;}
			| cmd ';' lista_cmds	{;}
			| stmt
			| stmt lista_cmds

cmd:	 cmd_saida			{;}
		| cmd_atribuicao		{;}
;

stmt: 	stmt_if
		| stmt_while

stmt_if:  	IF '(' expr ')' '{' lista_cmds'}'   %prec THEN
		{printf("if DETECTED\n");} 
		|   IF '(' expr ')' '{' lista_cmds '}' ELSE '{'lista_cmds '}' 
		{printf("ifelse DETECTED\n");}

stmt_while: WHILE '('expr')' '{' lista_cmds'}'  
		{printf("while DETECTED\n");}

cmd_saida:	ESCREVA '(' expr ')'
	{
		/* generate code for expression to write */
//		cGen(tree->child[0]);
		/* now output it */
		emitRO("OUT",ac,0,0,"escreve ac");

	}
;
cmd_atribuicao: ID '=' expr
	{	if (!constaTabSimb($1)) {
		  erroSemantico = 1;
		} else{
			locMemId = recuperaLocMemId($1);
			emitRM("ST",ac,locMemId,gp,"atribuicao: armazena valor");
		}
	}
;


expr:	term
	| 	expr binop term2 {
        switch($2){
                case 1:
                    emitRO("ADD",ac,ac,tmp,"soma operandos");
                break;

                case 2:
                    emitRO("SUB",ac,ac,tmp,"subtrai operandos");
                break;

                case 3:
                    emitRO("MUL",ac,ac,tmp,"multiplica operandos");
                break;

                case 4:
                    emitRO("DIV",ac,ac,tmp,"divide operandos");
                break;
            }
	}
	// | '(' expr ')' {$$ =$2;}
	
	// |	 SUB {val_info = -1;} expr  {;}
;
//term eh usado para implicitamente tornar binop associativa a esquerda %left n funciona com regras
term:	NUM
	{
		emitRM("LDC",ac,$1*val_info,0,"carrega constante em ac");
	}
	|	ID
	{
		if (!constaTabSimb($1)) {
		  erroSemantico = 1;
		} else {
		  locMemId = recuperaLocMemId($1);
		  emitRM("LD",ac,locMemId,gp,"carrega valor de id em ac");
		}
	}	
	
	
term2:	NUM
	{
		emitRM("LDC",tmp,$1,0,"carrega constante em ac");
	}
	|	ID
	{
		if (!constaTabSimb($1)) {
		  erroSemantico = 1;
		} else {
		  locMemId = recuperaLocMemId($1);
		  emitRM("LD",tmp,locMemId,gp,"carrega valor de id em ac");
		}
	}
	// | '(' expr ')' {$$ = $2;}

binop: 	ADD {$$ = 1;}
		|SUB {$$ = 2;}
		|MUL {$$ = 3;}
		|DIV {$$ = 4;}
	
		
;
%%
// SEMANTICO
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
