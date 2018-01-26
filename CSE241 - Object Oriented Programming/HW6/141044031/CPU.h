/* 
 * File:   CPU.h
 * Author: furkan
 *
 * Created on October 28, 2016, 8:40 PM
 */

#ifndef CPU_H
#define CPU_H

#include <string>
#include "Memory.h"
using namespace std;

class CPU {
public:
    CPU();
    CPU(int optionVal);
    int getter(int regNumber)const{ return registers[regNumber - 1] ; }
    void setter(int regNumber, int value) { registers[regNumber - 1] = value; }
    int execute(string instruction, Memory &cMemory);
    void print();
    bool halted()const{return isItHlt;}
    int getPC()const{  return PC;}
    void setPC(int ProgC){PC = ProgC;}
    void setOption(int opVal){ option = opVal;}
    int getOption(){return option;}
private:
    int registers[5];
    int PC = 1;
    bool isItHlt = false;
    int option = 0;
    void isOptionValid(int progOption)const;
    void setHlt(bool value) { isItHlt = value;}
    int MOV(const string& stringA,const string& stringB,Memory &cMemory);
    int ADD(const string& stringA,const string& stringB,Memory &cMemory);
    int SUB(const string& stringA,const string& stringB,Memory &cMemory);
    int PRN(const string&stringA, const Memory& cMemory)const;
    int JMP(const string& stringA,const string& stringB);
    int JPN(const string& stringA,const string& stringB);
    string editInst(string &str)const;
    void divideInst(const string& currentLine, string& order,
                                string& firstString, string& secondString)const;
    void delSpaces(string& str)const;
    void ToMyUpper(string& word)const;
    bool isItRegister(const string& strRegister)const;
    bool isItConst(const string& StrRegister)const;
    bool isItAdress(const string& stringToCheck)const;
    int  strToInt(const string& strOfInt)const;
    int  turnIndex(const string& str)const;
    int  power(int num1, int num2)const;
};

#endif /* CPU_H */