all: shell.o
	gcc shell.o

run:
	./a.out

shell.o: shell.c shell.h
	gcc -c shell.c

clean:
	rm ./a.out
	rm *.o
