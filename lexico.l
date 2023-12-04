/* Analisador Lexico */
%{
#include "sintatico.tab.h"
%}
%%

\+                      {yylval.inteiro = 1; return ADD;}
\-                      {yylval.inteiro = 2; return SUB;}
\*                      {yylval.inteiro = 3; return MUL;}
\\                      {yylval.inteiro = 4; return DIV;}
int                     {return INT;}
var		                  {return VAR;}
inteiro		              {return INTEIRO;}
escreva		              {return ESCREVA;}
[0-9]+		              {yylval.inteiro = atoi(yytext); return NUM;}
[a-zA-Z][a-zA-Z0-9]*	  {yylval.cadeia= (char *) strdup(yytext); return ID;}
[ \t\n]+	              {;}
.		                    {return yytext[0];}
%%
int yywrap() {
  return 1;
}
