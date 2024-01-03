all:
	clang -Wall -Wpedantic -Werror -Wextra  -c newspeak.c bv.c bf.c hash.c ll.c speck.c gs.c
	flex words.l
	clang -Wall -Wpedantic -Werror -Wextra  -c lex.yy.c
	clang -o newspeak newspeak.o bv.c bf.c hash.c ll.c speck.c gs.c lex.yy.o -lfl
clean:
	rm -rf newspeak 
	rm -rf newspeak.o
	rm -rf lex.yy.o
	rm -rf lex.yy.c
	rm -rf bv.o
	rm -rf bf.o
	rm -rf hash.o
	rm -rf ll.o
	rm -rf speck.o
	rm -rf gs.o
	rm -rf infer-out
infer: 
	infer-capture -- make; infer-analyze -- make
