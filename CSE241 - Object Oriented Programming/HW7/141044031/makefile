all: exe

exe: _mainTester.o Bigram.o BigramMap.o BigramDyn.o Fmap.o 
	g++ _mainTester.o Bigram.o BigramMap.o BigramDyn.o Fmap.o -o exe

_mainTester.o: _mainTester.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 _mainTester.cpp

Bigram.o: Bigram.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 Bigram.cpp
BigramMap.o: BigramMap.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 BigramMap.cpp
BigramDyn.o:
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 BigramDyn.cpp
Fmap.o:
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 Fmap.cpp
clean:
	rm *.o exe