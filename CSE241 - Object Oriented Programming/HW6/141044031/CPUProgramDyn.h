/* 
 * File:   CPUProgramDyn.h
 * Author: furkan
 *
 * Created on November 26, 2016, 8:59 AM
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H
#include <iostream>

using namespace std;

namespace FurkanCPUProgDyn{
    class CPUProgramDyn {
    public:
        CPUProgramDyn();
        CPUProgramDyn(int cap);
        CPUProgramDyn(const CPUProgramDyn& orig);
        void ReadFile(const string& fileName);
        const string getLine(int lineNumber)const;
        int size()const;
        void setOption(int optionVal){ dynOption = optionVal ;}
        int getOption()const{return dynOption;}
        int getCap()const{return capacity;}
        int getUsed()const{return used;}
        bool full()const;
        const string& operator[](int index)const;
        string& operator[](int index);
        void operator+=(const string& order);
        const CPUProgramDyn& operator--();
        const CPUProgramDyn operator--(int ignorMe);
        bool operator==(const CPUProgramDyn& other)const;
        bool operator!=(const CPUProgramDyn& other)const;
        bool operator<=(const CPUProgramDyn& other)const;
        bool operator<(const CPUProgramDyn& other)const;
        bool operator>=(const CPUProgramDyn& other)const;
        bool operator>(const CPUProgramDyn& other)const;
		CPUProgramDyn& operator =(const CPUProgramDyn& rightSide);
        const CPUProgramDyn operator()(int num1,int num2)const;
        const CPUProgramDyn operator+(const string& order)const;
       	const CPUProgramDyn operator+(const CPUProgramDyn& other)const;
        friend ostream& operator<<(ostream& outputStream,
        											const CPUProgramDyn& cpu);
        ~CPUProgramDyn();
    private:
        string *order;
        int capacity;
        int used;
        int dynOption=0;
        void addInstruction(const string& direction);
        void dellInstruction();
        void extendCap();
        void setCap(int val){capacity=val;}
        void setUsed(int val){used= val;}

    };
}
#endif /* CPUPROGRAMDYN_H */