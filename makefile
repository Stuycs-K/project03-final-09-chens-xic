.PHONY: clean compile run
compile program: main.o library.o player.o node.o
	@gcc -o program main.o library.o player.o node.o
run:
	@./program
main.o: main.c library.h player.h node.h
	@gcc -c main.c
node.o: node.c node.h
	@gcc -c node.c
library.o: library.c library.h node.h
	@gcc -c library.c
player.o: player.c player.h
	@gcc -c player.c
clean:
	rm *.o
	rm program
