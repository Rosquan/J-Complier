all: jc

jc: hash.o token.o tokenizer.o jc.c

	clang -g hash.o token.o tokenizer.o jc.c -o jc

hash.o: hash.c

	clang -c hash.c
	
token.o: token.c

	clang -c token.c
	
tokenizer.o: tokenizer.c

	clang -c tokenizer.c
	
clean:
	rm -rf *.o

clobber: clean
	rm -rf hash
