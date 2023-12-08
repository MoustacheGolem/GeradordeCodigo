/* Analisador Lexico */
%{
#include "sintatico.tab.h"
%}
%%

\+                      { return ADD;}
\-                      { return SUB;}
\*                      { return MUL;}
\\                      { return DIV;}

int                     {return INT;}
char                    {return CHAR;}

void                  {return VOID;}
if                   {return IF;}
else                 {return ELSE;}
while                {return WHILE;}
for                  {return FOR;}
return               {return RETURN;}
extern                {return EXTERN;}

escreva		              {return ESCREVA;}
[0-9]+		              {yylval.inteiro = atoi(yytext); return NUM;}
[a-zA-Z][a-zA-Z0-9]*	  {yylval.cadeia= (char *) strdup(yytext); return ID;}
[ \t\n]+	              {;}
.		                    {return yytext[0];}
%%
int yywrap() {
  return 1;
}
