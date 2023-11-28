all:
	flex lexico.l
	bison -d sintatico.y --debug -v 
	gcc -o gera sintatico.tab.c lex.yy.c -Wno-implicit-function-declaration -Wno-implicit-int



run:
	./gera.exe 