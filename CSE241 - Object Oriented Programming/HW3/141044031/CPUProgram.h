/* 
 * File:   CPUProgram.h
 * Author: FURKAN YILDIZ
 *
 * Created on October 21, 2016, 9:17 PM
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <string>
#include <vector>
using namespace std;


class CPUProgram{
public:
    CPUProgram(const string& fileName);
    int ReadFile(const string& fileName);
    string getLine(int lineNumber)const{return instruction[lineNumber -1 ]; }
    int size()const {return instruction.size(); }

private:
    vector<string> instruction;
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