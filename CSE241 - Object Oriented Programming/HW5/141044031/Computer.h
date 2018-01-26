/* 
 * File:   Computer.h
 * Author: furkan
 *
 * Created on October 29, 2016, 10:38 PM
 */

#ifndef COMPUTER_H
#define COMPUTER_H
#include "CPU.h"
#include "Memory.h"
#include "CPUProgram.h"

class Computer {
public:
    Computer();
    Computer(int option);
    Computer(CPU myCPU, CPUProgram myCPUProgram, Memory myMemory, int option);
    CPU getCPU()const{return pcCPU;}
    CPUProgram getCPUProgram()const{return pcCPUProgram;}
    Memory getMemory()const{return pcMemory;}
    int getOption()const{return pcOption;}
    void setCPU(CPU myCPU){ pcCPU = myCPU ;}
    void setCPUProgram(CPUProgram myCPUProgram){ pcCPUProgram =  myCPUProgram;}
    void setMemory(Memory myMemory){ pcMemory = myMemory ;}
    void setOption(int option) { pcOption = option;}
    void execute();
    void execute(const string& filename);

private:
    CPU pcCPU;
    CPUProgram pcCPUProgram;
    Memory pcMemory;
    int pcOption = 0;
    void isOptionValid(int progOption)const;
};
#endif /* COMPUTER_H */