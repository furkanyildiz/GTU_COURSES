/* 
 * File:   CPUProgram.h
 * Author: furkan
 *
 * Created on October 29, 2016, 9:52 PM
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <string>
#include <vector>
using namespace std;

class CPUProgram{
public:
    CPUProgram(int optionValue);
    CPUProgram();
    CPUProgram(const string& fileName);
    void ReadFile(const string& fileName);
    /*
    Programin mantigina gore getLine PC counter ile calismali program ve PC 
    counterde dogal olarak ( ve hocanin istegine gore) 1 ile basliyacagindan 
    getLine(0) veya getLine(myCPUProgram.size-1) gibi seyler programin ve Yusuf
    hocanin mantigina gore calismamali.
    */
    string getLine(int lineNumber)const{return instruction[lineNumber -1 ] ; }
    int size()const {return instruction.size() ; }
    void setOption(int optionVal){CPUProgramOption = optionVal ;}
private:
    vector<string> instruction;
    int CPUProgramOption = 0;
    void isOptionValid(int progOption)const;
    void addInstruction(const string& direction)
                                            {instruction.push_back(direction);}
    bool canFileOpen(const ifstream& fileStream)const;
    int  fillOrder(const string& line, string& cmd)const;
    bool  fillStrings(string& line,const string& command, string& firstString,
                      string& secondString)const;
    int separateStrings(const string& lineOfFile, string& order, 
                     string& firstString, string& secondString)const;
    bool  fillSecondString(const string& line, string& secondString)const;
    bool checkCommends(const string& line, int index )const;
    bool checkOrders(string& order)const;
    void upperString (string& word)const;
    int  findIndexComma(const string str, int size)const;
};

#endif /* CPUPROGRAM_H */