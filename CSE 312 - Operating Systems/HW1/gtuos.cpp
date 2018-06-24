#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <string>
#include <random>
#include <sstream>
#include <fstream>




uint64_t GTUOS::handleCall(const CPU8080 & cpu){

	switch(cpu.state->a){

		case PRINT_B: return handlePrintB(cpu.state->b); break;
		case PRINT_MEM: return handlePrintMem(cpu); break;
		case READ_B: return handleReadB(&(cpu.state->b)); break;
		case READ_MEM: return handleReadMem(cpu); break;
		case PRINT_STR:return  handlePrintStr(cpu); break;
		case READ_STR:return  handleReadStr(cpu); break;
		case GET_RND: return handleGetRnd(&(cpu.state->b)); break;
		default: std::cout<<"Invalid System Call!"<<(int)cpu.state->a<<std::endl; return 0;

	}

}

uint64_t GTUOS::handlePrintB(const uint8_t x)const{

	std::cout<<"System Call Handle: PRINT_B"<<std::endl;
	std::cout<<"Content of RegisterB:" <<(int)x<<std::endl;
	return PRINT_B_CYCLE;
}

uint64_t GTUOS::handlePrintMem(const CPU8080& cpu)const{

    std::cout<<"System Call Handle: PRINT_MEM"<<std::endl;

    uint32_t address;
    address = (cpu.state->b << 8) | cpu.state->c;

    std::cout<<"BC adress is:"<<(uint32_t)address<<std::endl;
    std::cout<<"BC content is:"<<(int)(cpu.memory->at(address))<<std::endl;

	return PRINT_MEM_CYCLE;
}
//Reads an integer from the keyboard and puts it in register B.
uint64_t GTUOS::handleReadB(uint8_t *x)const{
    std::cout<<"System Call Handle: READ_B"<<std::endl;

	int value;
	std::cout<<"Enter an integer between 0 to 255 for register B:";

    std::cin >> value;

	
	if (value <0 || value>255){
		std::cout<<"The number is not between 0 to 255. OS chose 0 for registerB.";
		*x = 0;
	}
	else
		*x = value;

	return READ_B_CYCLE;

}

uint64_t GTUOS::handleReadMem(const CPU8080& cpu)const{

    std::cout<<"System Call Handle: READ_MEM"<<std::endl;

    uint32_t address;
    address = (cpu.state->b << 8) | cpu.state->c;

	int value;
	std::cout<<"Enter an integer between 0 to 255 for memory address of BC:";
    std::cin >> value;

	if (value <0 || value>255){
		std::cout<<"The number is not between 0 to 255. OS chose 0.";
		cpu.memory->at(address) = 0;
		std::cout<<"The 0 is assigned to the memory address of:" << (unsigned)address<<std::endl;
		
	}
	else{
		cpu.memory->at(address) = value;
		std::cout<<"The "<<value<<" is assigned to the memory address of:" << (unsigned)address<<std::endl;
	}

	return READ_MEM_CYCLE;

}
// Prints the null terminated string at the memory location pointed by B and C ?????????
uint64_t GTUOS::handlePrintStr(const CPU8080& cpu)const{

    std::cout<<"System Call Handle: PRINT_STR"<<std::endl;

    uint32_t address;
    address = (cpu.state->b << 8) | cpu.state->c;
    std::cout<<"The address of "<<(int)address;

    bool Flag = true;
    std::string content = "";
	while (Flag)
    	if (cpu.memory->at(address) == '\0')
    		Flag = false;
    	else
    		content+= cpu.memory->at(address++);
	std::cout<<" content is :"<<content<<"\n";
    
    
	return PRINT_STR_CYCLE;
}
//Reads the null terminated string from the keyboard and puts the result at the memory location pointed by B and C
uint64_t GTUOS::handleReadStr(const CPU8080& cpu)const{

    std::cout<<"System Call Handle: READ_STR"<<std::endl;

    uint32_t address;
    address = (cpu.state->b << 8) | cpu.state->c;

    uint32_t input_writed_address = address;

    std::cout<<"Enter a string: ";
    std::string input = "";
    //std::cin.ignore();
    getline(std::cin,input);
    if (input == "\n" || input == "") //for buffer.
    	getline(std::cin,input);
    
    input += '\0';

    for (unsigned int i=0; i<input.length(); ++i)
    	cpu.memory->at(address++) = input[i];

    cpu.memory->at(address) = '\0';

    std::cout<<"The string:"<<input<<" writed to memory address is:"<<input_writed_address<<std::endl;

	return READ_STR_CYCLE;
}
//Produces a random byte and puts in register B
uint64_t GTUOS::handleGetRnd(uint8_t *x)const{

    std::cout<<"System Call Handle: GET_RND"<<std::endl;

    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed);

    std::uniform_int_distribution<> dist{0,256};
	int random_byte = dist(eng);

	*x = random_byte;

    std::cout<<"Random number:"<<random_byte<<" produced and saved to registerB"<<std::endl;


	return GET_RND_CYCLE;
}

void GTUOS::saveMemory(const CPU8080 & cpu, std::string filename)const{
    std::fstream myfile;
    myfile.open(filename,std::fstream::out);

    for (int i=0; i<0x1000; ++i){
        char str[10];
        sprintf(str,"0x%08x ",i*16);

        std::string temp(str);

    	for (int j=0; j<0x10; ++j){
    		sprintf(str,"0x%02x ",cpu.memory->at(i*16+j));
    		temp += str;
    	}

		myfile << temp <<"\n";

    }	

    myfile.close();

}