/* 
 * File:   Memory.h
 * Author: furkan
 *
 * Created on October 28, 2016, 8:16 PM
 */

#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
class Memory{
public:
    Memory();
    Memory(int option);
    int getMem(int index)const{ return memoryArr[index];}
    void setMem(unsigned int index, unsigned int value) { memoryArr[index] = value;}
    void printAll()const;
    void setOption(int optionVal){ option = optionVal;}
private:
    unsigned int memoryArr[50];
    int option = 0;
   	void isOptionValid(int progOption)const;

};

#endif /* MEMORY_H */