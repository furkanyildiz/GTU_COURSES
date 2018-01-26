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
#include "CPUProgramDyn.h"
using FurkanCPUProgDyn::CPUProgramDyn;


class Computer {
public:
    Computer();
    Computer(int option);
    Computer(CPU myCPU, CPUProgramDyn myCPUProgram, Memory myMemory, int option);
    CPU getCPU()const{return pcCPU;}
    CPUProgramDyn getCPUProgramDyn()const{return pcCPUProgramDyn;}
    Memory getMemory()const{return pcMemory;}
    int getOption()const{return pcOption;}
    void setCPU(CPU myCPU){ pcCPU = myCPU ;}
    void setCPUProgramDyn(CPUProgramDyn myCPUProgram);
    void setMemory(Memory myMemory){ pcMemory = myMemory ;}
    void setOption(int option) { pcOption = option;}
    void execute();
    void execute(const string& filename);

private:
    CPU pcCPU;
    CPUProgramDyn pcCPUProgramDyn;
    Memory pcMemory;
    int pcOption = 0;
    void isOptionValid(int progOption)const;
};
#endif /* COMPUTER_H */