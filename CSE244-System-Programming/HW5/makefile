all: grephSh

grephSh: main.o 
	gcc main.o -o grephSh -pthread

main.o: main.c
	gcc -c main.c -pthread

clean:
	rm *.o grephSh
