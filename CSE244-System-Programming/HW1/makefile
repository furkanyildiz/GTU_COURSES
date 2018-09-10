all: list

list: hw1.o 
	gcc hw1.o -o list

hw1.o: hw1.c
	gcc -c -ansi -pedantic-errors hw1.c

clean:
	rm *.o list
