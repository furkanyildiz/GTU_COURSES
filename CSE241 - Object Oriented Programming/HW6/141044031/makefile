all: exe

exe: _mainTester.o CPU.o Memory.o CPUProgramDyn.o Computer.o 
	g++ _mainTester.o CPU.o Memory.o CPUProgramDyn.o Computer.o -o exe

_mainTester.o: _mainTester.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 _mainTester.cpp

CPU.o: CPU.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 CPU.cpp
Memory.o: Memory.cpp
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 Memory.cpp
CPUProgramDyn.o:
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 CPUProgramDyn.cpp
Computer.o:
	g++ -c -ansi -pedantic-errors -Wall --std=c++11 Computer.cpp
clean:
	rm *.o exe