/* 
 * File:   CPU.h
 * Author: FURKAN YILDIZ
 *
 * Created on October 18, 2016, 8:15 PM
 */

#ifndef CPU_H
#define CPU_H

#include <string>

using namespace std;


class CPU{
public:
    CPU(int Reg1,int Reg2,int Reg3,int Reg4,int Reg5,int ProgC);
    CPU();
    void setR1(int Reg1){registers[0] = Reg1;}
    void setR2(int Reg2){registers[1] = Reg2;}
    void setR3(int Reg3){registers[2] = Reg3;}
    void setR4(int Reg4){registers[3] = Reg4;}
    void setR5(int Reg5){registers[4] = Reg5;}
    void setPC(int ProgC){PC = ProgC;}
    int  getR1()const{  return registers[0];}
    int  getR2()const{  return registers[1];}
    int  getR3()const{  return registers[2];}
    int  getR4()const{  return registers[3];}
    int  getR5()const{  return registers[4];}
    int  getPC()const{  return PC;}
    void print()const;
    bool halted()const{return isItHlt;}
    int  execute(string& instructionLine);
private:
    int registers[5];
    static int PC;
    bool isItHlt = false;
    void setHlt(bool value) { isItHlt = value;}
    int MOV(const string& registerA,const string& registerB);
    int ADD(const string& registerA,const string& registerB);
    int SUB(const string& registerA,const string& registerB);
    int PRN(const string& registerA)const;
    int JMP(const string& registerA,const string& registerB);
    void ToMyUpper(string& word)const;
    bool isItRegister(const string& strRegister)const;
    bool isItConst(const string& StrRegister)const;
    int  strToInt(const string strOfInt)const;
    int  power(int num1, int num2)const;
    void divideInst(const string& currentLine, string& order, 
                         string& firstString, string& secondString)const;
    int  getter(const string& strRegstr)const;//Assembly islemleri icin
    void setter(int setVal,const string& strRegstr);//Assembly islemleri icin
};
#endif /* CPU_H */
