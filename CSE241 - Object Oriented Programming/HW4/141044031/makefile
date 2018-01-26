all: exe

exe: _mainTester.o CPU.o Memory.o CPUProgram.o Computer.o
	g++ _mainTester.o CPU.o Memory.o CPUProgram.o Computer.o -o exe

_mainTester.o: _mainTester.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 _mainTester.cpp

main.o: main.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 main.cpp

CPU.o: CPU.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 CPU.cpp
	
Memory.o: Memory.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 Memory.cpp
CPUProgram.o:
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 CPUProgram.cpp
Computer.o:
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 Computer.cpp
clean:
	rm *.o exe