all: server client results

server: timeServer.o
	gcc -o server timeServer.o -lm

client: seeWhat.o
	gcc -o client seeWhat.o -lm

results: showResults.o
	gcc -o results showResults.o -lm

timeServer.o: timeServer.c
	gcc -c timeServer.c

seeWhat.o : seeWhat.c
	gcc -c seeWhat.c

showResults.o : showResults.c
	gcc -c showResults.c

clean:
	rm *.o server client results

