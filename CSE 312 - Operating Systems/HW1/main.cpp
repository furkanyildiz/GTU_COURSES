#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

	// This is just a sample main function, you should rewrite this file to handle problems 
	// with new multitasking and virtual memory additions.
int main (int argc, char**argv)
{
	if (argc != 3){
		std::cerr << "Usage: prog exeFile debugOption\n";
		exit(1); 
	}
	int DEBUG = atoi(argv[2]);

	memory mem;
	CPU8080 theCPU(&mem);
	GTUOS	theOS;

	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);	
 	uint64_t count = 0;
 	std::string temp;
	do	
	{
		theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall()){

			count+= theOS.handleCall(theCPU);

			if(DEBUG == 2){
				std::cout<<"To continue press any key: ";
    			getline(std::cin,temp);
			}

		}
	}	while (!theCPU.isHalted());

	std::cout<<"Totaly clock:"<<count<<std::endl;
	theOS.saveMemory(theCPU,"exe.mem");
	//SAVE THE MEMORY


	return 0;
}

