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
    string getLine(int lineNumber)const{return instruction[lineNumber] ; }
    int size()const {return instruction.size() ; }
    void setOption(int optionVal){CPUProgramOption = optionVal ;}
    const string operator[](int index)const;
    string operator[](int index);
    void operator+=(const string& order);
    const CPUProgram operator--();
    const CPUProgram operator--(int ignorMe);
    bool operator==(CPUProgram& other){ return(size()==other.size());}
    bool operator!=(CPUProgram&other){ return(size()!=other.size());}
    bool operator<=(CPUProgram&other){ return(size()<=other.size());}
    bool operator<(CPUProgram&other){ return(size()<other.size());}
    bool operator>=(CPUProgram&other){ return(size()>=other.size());}
    bool operator>(CPUProgram&other){ return(size()>other.size());}
    CPUProgram operator()(int num1,int num2)const;
    const CPUProgram operator+(const string& order)const;
    const CPUProgram operator+(const CPUProgram& other);
    friend ostream& operator<<(ostream& outputStream,const CPUProgram& cpu);
private:
    vector<string> instruction;
    int CPUProgramOption;
    void addInstruction(const string& direction)
                                            {instruction.push_back(direction);}
    void dellInstruction(){instruction.pop_back();}
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