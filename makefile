all: shell.o
	gcc -o hello shell.o

shell.o:shell.c
	gcc -c shell.c

run:
	./hello

clear:
	rm *.o
	rm *out
