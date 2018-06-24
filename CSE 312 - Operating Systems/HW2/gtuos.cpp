#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <string>
#include <random>
#include <sstream>
#include <fstream>
#include <algorithm>


GTUOS::GTUOS(CPU8080* cpu8080,uint64_t* cycle_c,int debug) {
    theCPU = cpu8080;
    cycle_count = cycle_c;
    uint64_t  quantum_t = 100;
    scheduler = Scheduler(theCPU,cycle_c,quantum_t,debug);
    returnState = theCPU->state;
}


uint64_t GTUOS::handleCall(uint64_t *cycle, bool * context_switch){

    setContext_switch_happen(false);
    uint64_t  calling_pc = scheduler.get_called_os_pc();

    //update runnig thread with the calling pc
    scheduler.update_pc(calling_pc+3,*cycle_count);

    uint64_t cycle_of_call;

    switch(theCPU->state->a){

        case PRINT_B: cycle_of_call = handlePrintB(); break;
        case PRINT_MEM: cycle_of_call = handlePrintMem(); break;
        case READ_B: cycle_of_call = handleReadB(); break;
        case READ_MEM: cycle_of_call = handleReadMem(); break;
        case PRINT_STR:cycle_of_call =  handlePrintStr(); break;
        case READ_STR:cycle_of_call =  handleReadStr(); break;
        case GET_RND: cycle_of_call = handleGetRnd(); break;
        case TEXIT: cycle_of_call = handleTExit(cycle); break;
        case TJOIN: cycle_of_call = handleTJoin(cycle); break;
        case TYIELD: cycle_of_call = handleTYield(cycle); break;
        case TCREATE: cycle_of_call = handleTCreate(cycle); break;
        default: std::cout<<"Invalid System Call!"<<(int)theCPU->state->a<<std::endl; cycle_of_call = 0;

    }

    *context_switch = is_context_switch_happen();
    return cycle_of_call;
}


uint64_t GTUOS::handleTCreate(uint64_t *cycle){

    //thread tablenın boş olan elemanına atamalar yapılır, ready ve address ataması.
    //schedular queue ya ko


    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: TCREATE"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    int created_thread_tid = scheduler.add_new_thread((uint16_t) address,*cycle_count);
    if (created_thread_tid != -1){
        theCPU->state->b = (uint8_t ) created_thread_tid;
        context_switch_happen = scheduler.schele(theCPU,1);
        *cycle = 0; //context switch oldu cycle = 0

    }
    else
        theCPU->state->b = 0;


    return TCREATE_CYCLE;
}
uint64_t GTUOS::handleTExit(uint64_t *cycle){
    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: TExit"<<std::endl;

    int exit_status = scheduler.exit_thread();
    theCPU->state->b = (uint8_t ) exit_status;

    if (exit_status == 1){ //if exit is successed.
        context_switch_happen = scheduler.schele(theCPU,1);
        *cycle = 0; //context switch oldu cycle = 0
    }

    return TEXIT_CYCLE;
}
/* Register B holds the thread ID of the thread to wait for.*/
uint64_t GTUOS::handleTJoin(uint64_t *cycle){

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: TJoin"<<std::endl;

    uint8_t waiting_tid = theCPU->state->b;

    scheduler.tjoin(waiting_tid);
    context_switch_happen = scheduler.schele(theCPU,1);
    *cycle = 0; //context switch oldu cycle = 0


    return TJOIN_CYCLE;
}
uint64_t GTUOS::handleTYield(uint64_t *cycle){

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: TYield"<<std::endl;

    context_switch_happen = scheduler.schele(theCPU,1);
    *cycle = 0; //context switch oldu cycle = 0

    return TYIELD_CYCLE;
}

void GTUOS::timer_interrupt(uint64_t *cycle){

    if (*cycle / scheduler.quantum_time > 0) {
        *cycle = 0;
        //std::cout<<"Timer interrupt"<<std::endl;

        context_switch_happen = scheduler.schele(theCPU,0);

    }

}



uint64_t GTUOS::handlePrintB()const{

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: PRINT_B"<<std::endl;
    std::cout<<"Content of RegisterB:" <<(int)theCPU->state->b<<std::endl;
    return PRINT_B_CYCLE;
}

uint64_t GTUOS::handlePrintMem()const{
    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: PRINT_MEM"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    std::cout<<"BC adress is:"<<(uint32_t)address<<std::endl;
    std::cout<<"BC content is:"<<(int)(theCPU->memory->at(address))<<std::endl;

    return PRINT_MEM_CYCLE;
}
//Reads an integer from the keyboard and puts it in register B.
uint64_t GTUOS::handleReadB()const{
    std::cout<<"System Call Handle: READ_B"<<std::endl;

    int value;
    std::cout<<"Enter an integer between 0 to 255 for register B:";

    std::cin >> value;


    if (value <0 || value>255){
        std::cout<<"The number is not between 0 to 255. OS chose 0 for registerB.";
        theCPU->state->b = 0;
    }
    else
        theCPU->state->b = (uint8_t) value;

    return READ_B_CYCLE;

}

uint64_t GTUOS::handleReadMem()const{

    std::cout<<"System Call Handle: READ_MEM"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    int value;
    std::cout<<"Enter an integer between 0 to 255 for memory address of BC:";
    std::cin >> value;

    if (value <0 || value>255){
        std::cout<<"The number is not between 0 to 255. OS chose 0.";
        theCPU->memory->at(address) = 0;
        std::cout<<"The 0 is assigned to the memory address of:" << (unsigned)address<<std::endl;

    }
    else{
        theCPU->memory->at(address) = (uint8_t )  value;
        std::cout<<"The "<<value<<" is assigned to the memory address of:" << (unsigned)address<<std::endl;
    }

    return READ_MEM_CYCLE;

}
// Prints the null terminated string at the memory location pointed by B and C ?????????
uint64_t GTUOS::handlePrintStr()const{

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: PRINT_STR"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;
    std::cout<<"The address of "<<(int)address;

    bool Flag = true;
    std::string content = "";
    while (Flag)
        if (theCPU->memory->at(address) == '\0')
            Flag = false;
        else
            content+= theCPU->memory->at(address++);
    std::cout<<" content is :"<<content<<"\n";


    return PRINT_STR_CYCLE;
}
//Reads the null terminated string from the keyboard and puts the result at the memory location pointed by B and C
uint64_t GTUOS::handleReadStr()const{

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: READ_STR"<<std::endl;

    uint32_t address;
    address = (theCPU->state->b << 8) | theCPU->state->c;

    uint32_t input_writed_address = address;

    std::cout<<"Enter a string: ";
    std::string input = "";
    //std::cin.ignore();
    getline(std::cin,input);
    if (input == "\n" || input == "") //for buffer.
        getline(std::cin,input);

    input += "\0";

    for (unsigned int i=0; i<input.length(); ++i)
        theCPU->memory->at(address++) = input[i];

    theCPU->memory->at(address) = '\0';

    std::cout<<"The string:"<<input<<" writed to memory address is:"<<input_writed_address<<std::endl;

    return READ_STR_CYCLE;
}
//Produces a random byte and puts in register B
uint64_t GTUOS::handleGetRnd()const{

    std::cout<<"In TID:"<<scheduler.getRunning_Thread_ID()<<" system call handle: GET_RND"<<std::endl;

    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed);

    std::uniform_int_distribution<> dist{0,256};
    int random_byte = dist(eng);

    theCPU->state->b = random_byte;

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

void GTUOS::calculatePC(int mode) {
    
    if(mode == 0){
        oscallpc = theCPU->state->pc;
    }
    else{
        if (theCPU->state->pc == 3){
            //running threade kaydet os_called_from yi
            scheduler.save_called_os_pc(oscallpc);

        }
    }

}

void GTUOS::setContext_switch_happen(bool context_switch_happen) {
    GTUOS::context_switch_happen = context_switch_happen;
}


GTUOS::Scheduler::Scheduler(const CPU8080* cpu8080,uint64_t *cycle_count,const uint64_t quantum, int debug) {
    quantum_time = quantum;
    Scheduler::DEBUG = debug;
    Scheduler::cycle_count = cycle_count;
    for(int i=0; i<THREAD_NUM; ++i){
        thread_table[i].setThread_id(i);
        thread_table[i].setAvailable(0);
        thread_table[i].setCycle(0);
        thread_table[i].waiting_tid = -1;

        //bzero(&thread_table[i].registers, sizeof(State8080));
    }
    thread_table[0].setState(RUNNING);
    thread_table[0].setAddress(0x0000);
    thread_table[0].setStarting_cycle(*cycle_count);
    thread_table[0].setStack_space(STACK_SPACE);
    thread_table[0].setAvailable(1);
    thread_table[0].setRegisters(*(cpu8080->state));


    Running_Thread_ID = 0;
    round_robin_queue.push(&(thread_table[0]));
//    round_robin_queue.push(std::make_shared<ThreadInformation>(thread_table[0]));

    last_time = 0;
}


int GTUOS::Scheduler::add_new_thread(uint16_t pc, uint64_t cycle_count) {

    bool find_avaible_thread = false;
    int i;
    for(i=0; (i<THREAD_NUM && !find_avaible_thread);  i+=1)
        if(thread_table[i].getAvailable() == 0)
            find_avaible_thread = true;

    i-=1;
    //bzero(&(thread_table[i].registers), sizeof(State8080));


    thread_table[i].setState(READY);
    thread_table[i].setRegisterPC(pc);
    thread_table[i].setAddress(pc);
    thread_table[i].setStarting_cycle(cycle_count);
    thread_table[i].setStack_space(STACK_SPACE);  ///////////
    thread_table[i].setAvailable(1);

    round_robin_queue.push(&(thread_table[i]));
//    round_robin_queue.push(std::make_shared<ThreadInformation>(thread_table[i]));

    if (find_avaible_thread)
        return i;
    else
        return -1;

}

int GTUOS::Scheduler::exit_thread() {

    if (thread_table[Running_Thread_ID].getAvailable() == 1 && thread_table[Running_Thread_ID].getState() == RUNNING){

        thread_table[Running_Thread_ID].setState(READY); //Running kalmamalı state
        thread_table[Running_Thread_ID].setAvailable(0); //threadi kullanılmıyor olarak işaretlemeliyiz
        interrupt_handler(Running_Thread_ID);
        return 1;
    } else
        return 0;

}

void GTUOS::Scheduler::interrupt_handler(uint8_t exit_thread_id){

    int i;
    for(i=0; i<THREAD_NUM; ++i){
        // eger ölen thread'i bekleyen birisi varsa block'ed den ready'e taşınmalı.
        // int16_t olan tipi -1 koyabilmek icin yapildi, -1 degilse karsılastırmak ıcın cast edılıyor.
        if( thread_table[i].waiting_tid != -1 and (uint8_t) thread_table[i].waiting_tid == exit_thread_id) {
            thread_table[i].waiting_tid = -1;
            thread_table[i].setState(READY);

        }
    }

    /*
    for(i=0; i<THREAD_NUM; ++i){
        // eger ölen thread'i bekleyen birisi varsa block'ed den ready'e taşınmalı.
        if(std::find(thread_table[i].waiting_tids.begin(), thread_table[i].waiting_tids.end(), exit_thread_id) != thread_table[i].waiting_tids.end() )
            thread_table[i].waiting_tids.erase(std::remove(thread_table[i].waiting_tids.begin(),thread_table[i].waiting_tids.end(),exit_thread_id)); //remove

        if(thread_table[i].waiting_tids.empty())
            thread_table[i].setState(READY);

    }*/
}

void GTUOS::Scheduler::copyRegisters(State8080 registers){

    uint16_t copy_pc = thread_table[Running_Thread_ID].registers.pc;
    thread_table[Running_Thread_ID].registers = registers;
    thread_table[Running_Thread_ID].registers.pc = copy_pc;

}
//Schele ' e thread gelmeden önce PC'si ayarlanmalı!
bool GTUOS::Scheduler::schele(CPU8080 *CPU8080, int os_call) {

    uint8_t first_running_tid = Running_Thread_ID;
    uint64_t total_cycle_of_old_thread = thread_table[Running_Thread_ID].getCycle();

    //current thread blocklanmadıysa, runningden ready e getir.
    //thread_table[Running_Thread_ID].registers = *(CPU8080->state);

    if(thread_table[Running_Thread_ID].registers.pc == 12 ){
      std::cout<<(int)Running_Thread_ID<<" aaaaaa:"<<thread_table[Running_Thread_ID].getOs_called_pc()<<std::endl;

        thread_table[Running_Thread_ID].registers.pc = thread_table[Running_Thread_ID].getOs_called_pc();
    }
    else if (os_call == 1)
        copyRegisters( *(CPU8080->state));
    else //timer interrupt
        thread_table[Running_Thread_ID].registers = *(CPU8080->state);


    if ( thread_table[Running_Thread_ID].getState() !=BLOCKED )
        thread_table[Running_Thread_ID].setState(READY);
    //Running threaddeki degerleri güncelle.

    if(thread_table[Running_Thread_ID].getAvailable() == 1) { //Running thread isini bitirmediyse tekrar queue ye eklenemi
        round_robin_queue.push(&(thread_table[Running_Thread_ID]));

    }

    update_thread_cycle(Running_Thread_ID,*cycle_count - last_time);
    last_time = *cycle_count;


    round_robin_queue.pop(); //Running thread queueden çıkartılır.


    while( round_robin_queue.front()->getState() == BLOCKED || round_robin_queue.front()->getAvailable()==0 ){     // QUEUEDEN CIKAN THREAD BLOCKED ISE
        round_robin_queue.push(round_robin_queue.front());
        round_robin_queue.pop(); //Running thread queueden çıkartılır.
//        std::cout<<"OS CRASH, ALL THREADS ARE BLOCKED"<<std::endl;

    }
    round_robin_queue.front()->setState(RUNNING);
    Running_Thread_ID = round_robin_queue.front()->getThread_id();
    //*(CPU8080->state) = round_robin_queue.front()->registers;
    //CPU8080->state = (State8080*) calloc(1,sizeof(State8080));
    
    CPU8080->state = &(round_robin_queue.front()->registers);
    //*(CPU8080->state) = round_robin_queue.front()->registers;


    if (first_running_tid != Running_Thread_ID) { //threat switch happened.
        if (DEBUG == 2){
            std::cout<<"threat switch happened, TID: "<<(int)first_running_tid<<" to TID: "<<(int)Running_Thread_ID<<std::endl;
            std::cout<<"The total cycles spent for the blocked thread: "<<total_cycle_of_old_thread<<std::endl;
        }
        else if(DEBUG == 3){
            print_thread_information();
        }
        return true;
    }
    else
        return false;
}
void GTUOS::Scheduler::print_thread_information(){
    std::cout<<"TID \t StckCycle\t RunCycle \t State \t StckAdres \t StckSpace \tA   B   C   D   E   H   L    SP"<<std::endl;

    int i;
    for(i=0; i<THREAD_NUM ;  i++)
        if(thread_table[i].getAvailable() == 1){
            printf("%04d \t %04d \t\t %04d \t\t %04d \t %04d \t\t %04d \t\t", (int)thread_table[i].getThread_id(), (int)thread_table[i].getStarting_cycle(), (int)thread_table[i].getCycle(),
                   (int)thread_table[i].getState(), (int)thread_table[i].getAddress(),(int)thread_table[i].getStack_space());
            print_registers(thread_table[i].getRegisters());

        }
}

void GTUOS::Scheduler::print_registers(State8080 registers){
    printf("$%02x $%02x $%02x $%02x $%02x $%02x $%02x  %04x\n", registers.a, registers.b, registers.c,
           registers.d, registers.e,registers.h, registers.l, registers.sp);

}


void GTUOS::Scheduler::update_pc(const uint16_t pc,const uint64_t cycle_count) {

    thread_table[Running_Thread_ID].registers.pc = pc;
    uint64_t cycle_run= cycle_count - thread_table[Running_Thread_ID].getStarting_cycle();
    //thread_table[Running_Thread_ID].setCycle(cycle_run);

}


int GTUOS::Scheduler::getRunning_Thread_ID() const {
    return Running_Thread_ID;
}

void GTUOS::Scheduler::setRunning_Thread_ID(uint8_t Running_Thread_ID) {
    Scheduler::Running_Thread_ID = Running_Thread_ID;
}

uint64_t GTUOS::Scheduler::getQuantum_time() const {
    return quantum_time;
}

void GTUOS::Scheduler::save_called_os_pc(uint16_t os_called_pc) {
    thread_table[Running_Thread_ID].setOs_called_pc(os_called_pc);
}
uint16_t GTUOS::Scheduler::get_called_os_pc(){
    return thread_table[Running_Thread_ID].getOs_called_pc();
}
void GTUOS::Scheduler::tjoin(const uint8_t waiting_tid){

    //thread_table[Running_Thread_ID].waiting_tids.push_back(waiting_tid); //beklediği thread id yazılır

    //beklenimek istenen thread çoktan ölmüş olabilir.
    if (thread_table[waiting_tid].getAvailable() == 1){
        thread_table[Running_Thread_ID].waiting_tid = waiting_tid;          //Bekledigi thread id yazılır
        thread_table[Running_Thread_ID].setState(BLOCKED);                  //BLOCK the running thread.
    }

}
