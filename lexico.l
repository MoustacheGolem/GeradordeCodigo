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

&&|and                {return AND;}
\|\||or               {return OR;}
\<=                   {return LE;}
\>=                   {return GE;}
\<                    {return LT;}
\>                    {return GT;} 
==                    {return EQ;}
\!=                   {return DIF;}

if                    {return IF;}
else                  {return ELSE;}
while                 {return WHILE;}
for                   {return FOR;}

\/\*.*?\*\/           { /* ignore comments*/ }

escreva		              {return ESCREVA;}
entrada		              {return ENTRADA;}

[0-9]+		              {yylval.inteiro = atoi(yytext); return NUM;}
[a-zA-Z][a-zA-Z0-9]*	  {yylval.cadeia= (char *) strdup(yytext); return ID;}
[ \t\n]+	              {;}
.		                    {return yytext[0];}
%%
int yywrap() {
  return 1;
}
