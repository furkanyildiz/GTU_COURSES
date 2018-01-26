/* 
 * File:   main.cpp
 * Author: FURKAN YILDIZ
 *
 * Created on October 18, 2016, 8:14 PM
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

#include "CPU.h"
#include "CPUProgram.h"

using namespace std;
int CPU :: PC = 1; // PC is a static value
int main(int argc, char** argv) {

    const char *FILENAME = argv[1]; // OKUNACAK DOSYANIN ISMI,CONSOLDAN GIRILIR
    const string OPTION = argv[2]; // PROGRAMIN CALISTIRILMA OPTIONU

    if(OPTION != "0" && OPTION != "1"){
        cerr << "OPTION MUST BE 0 OR 1"<< endl;
        return -1;
    }
    CPUProgram myProg(FILENAME);
    CPU myCPU;
    int returnValueOfFunc = 0 ;
    while(!myCPU.halted()){
    	//Atlanmak istenen satir, file'ın satirindan buyukse
    	//Ornegin file 16 satirken iceriden "jmp 67" komutu girilememeli.
        if(myCPU.getPC() > myProg.size()){ 
        	cerr<<"Jump's value can not be greather than file size."<<endl;
        	return -1;
        }
        string instruction = myProg.getLine(myCPU.getPC());
        if(OPTION == "1")
            cout << instruction <<" ";
        
        returnValueOfFunc = myCPU.execute(instruction);
        
        if (returnValueOfFunc == -1)
            return -1;
        
        if(OPTION == "1" || instruction=="HLT")
            myCPU.print();
    }
    return 0;
}
