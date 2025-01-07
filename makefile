.PHONY: clean compile run
compile program: main.o library.o
	@gcc -o program main.o library.o
run:
	@./program
main.o: main.c library.h
	@gcc -c main.c
library.o: library.c library.h
	@gcc -c library.c
clean:
	rm *.o
	rm program
