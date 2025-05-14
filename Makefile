flexTest:
	flex mylexer.l
	gcc -o mylexer.o lex.yy.c -lfl
	./mylexer.o < example.la
bison:
	bison -dvr all myanalyzer.y
	flex mylexer.l
	gcc -o mycompiler lex.yy.c myanalyzer.tab.c cgen.c -lfl
