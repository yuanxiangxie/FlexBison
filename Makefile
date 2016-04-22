all: clanguage
clanguage: lex.yy.c
	gcc -g lex.yy.c -o clanguage
lex.yy.c: clanguage.l
	flex clanguage.l
clean:
	rm -rf lex.yy.c clanguage
