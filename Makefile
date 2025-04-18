flexTest:
	flex mylexer.l
	gcc -o mylexer.o lex.yy.c -lfl
	./mylexer.o < example.la
