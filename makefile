all: shell.o
	gcc shell.o

run:
	./a.out

mystr.o: shell.c shell.h
	gcc -c shell.c

clean:
	rm ./a.out
	rm *.o
