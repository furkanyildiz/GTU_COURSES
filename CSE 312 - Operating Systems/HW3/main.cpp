#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

// This is just a sample main function, you should rewrite this file to handle problems
// with new multitasking and virtual memory additions.
int main (int argc, char**argv)
{
    if (argc != 4){
        std::cerr << "Usage: prog exeFile fileSystemFile debugOption\n";
        exit(1);
    }
    bool is_context_swich_happen = false;

    int DEBUG = atoi(argv[3]);
    uint64_t cycle = 0;
    uint64_t c_count = 0;
    uint64_t timer_cycle = 0;

    uint16_t call_os_pc;
    uint16_t tempp;

    uint64_t *cycle_count = &c_count;

    memory mem;
    CPU8080 theCPU(&mem);
    GTUOS	theOS(&theCPU,cycle_count,DEBUG,argv[2]);
    theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);
    std::string temp;

    do
    {
        cycle = theCPU.Emulate8080p(DEBUG);
        c_count+=cycle;
        timer_cycle+=cycle;

        theOS.calculatePC(1);

        theOS.timer_interrupt(&timer_cycle); //running process can change

        if(theCPU.isSystemCall()){

            cycle = theOS.handleCall(&timer_cycle,&is_context_swich_happen); //running process can change
            //eğer üstte running prcess değişti ise timer ı sıfırla
            c_count+=cycle;

            //eger running thread degismediyse
            if (!is_context_swich_happen )
                timer_cycle+=cycle;

            theOS.timer_interrupt(&timer_cycle); //running process can change


        }
        theOS.calculatePC(0);

    }	while (!theCPU.isHalted());
    theOS.saveStatus();
    std::cout<<"Totaly clock:"<<c_count<<std::endl;
    if (DEBUG==0 || DEBUG==1)
        theOS.saveMemory(theCPU,"exe.mem");
    //SAVE THE MEMORY


    return 0;
}