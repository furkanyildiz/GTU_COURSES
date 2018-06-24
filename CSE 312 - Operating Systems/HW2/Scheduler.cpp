#include "Scheduler.h"
#include <algorithm>



Scheduler::Scheduler(const CPU8080* cpu8080,uint64_t *cycle_count,const uint64_t quantum, int debug) {
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


int Scheduler::add_new_thread(uint16_t pc, uint64_t cycle_count) {

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

int Scheduler::exit_thread() {

    if (thread_table[Running_Thread_ID].getAvailable() == 1 && thread_table[Running_Thread_ID].getState() == RUNNING){

        thread_table[Running_Thread_ID].setState(READY); //Running kalmamalı state
        thread_table[Running_Thread_ID].setAvailable(0); //threadi kullanılmıyor olarak işaretlemeliyiz
        interrupt_handler(Running_Thread_ID);
        return 1;
    } else
        return 0;

}

void Scheduler::interrupt_handler(uint8_t exit_thread_id){

    int i;
    for(i=0; i<THREAD_NUM; ++i){
        // eger ölen thread'i bekleyen birisi varsa block'ed den ready'e taşınmalı.
        // int16_t olan tipi -1 koyabilmek icin yapildi, -1 degilse karsılastırmak ıcın cast edılıyor.
        if( thread_table[i].waiting_tid != -1 and (uint8_t) thread_table[i].waiting_tid == exit_thread_id) {
            uint8_t den = (uint8_t) thread_table[i].waiting_tid;
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

void Scheduler::copyRegisters(State8080 registers){

    uint16_t copy_pc = thread_table[Running_Thread_ID].registers.pc;
    thread_table[Running_Thread_ID].registers = registers;
    thread_table[Running_Thread_ID].registers.pc = copy_pc;

}
//Schele ' e thread gelmeden önce PC'si ayarlanmalı!
bool Scheduler::schele(CPU8080 *CPU8080, int os_call) {

    uint8_t first_running_tid = Running_Thread_ID;
    uint64_t total_cycle_of_old_thread = thread_table[Running_Thread_ID].getCycle();

    //current thread blocklanmadıysa, runningden ready e getir.
    //thread_table[Running_Thread_ID].registers = *(CPU8080->state);

    if(thread_table[Running_Thread_ID].registers.pc == 7 || thread_table[Running_Thread_ID].registers.pc == 6 ){
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
    CPU8080->state = &(round_robin_queue.front()->registers);


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
void Scheduler::print_thread_information(){
    std::cout<<"TID \t StckCycle\t RunCycle \t State \t StckAdres \t StckSpace \tA   B   C   D   E   H   L    SP"<<std::endl;

    int i;
    for(i=0; i<THREAD_NUM ;  i++)
        if(thread_table[i].getAvailable() == 1){
            printf("%04d \t %04d \t\t %04d \t\t %04d \t %04d \t\t %04d \t\t", (int)thread_table[i].getThread_id(), (int)thread_table[i].getStarting_cycle(), (int)thread_table[i].getCycle(),
                   (int)thread_table[i].getState(), (int)thread_table[i].getAddress(),(int)thread_table[i].getStack_space());
            print_registers(thread_table[i].getRegisters());

        }
}

void Scheduler::print_registers(State8080 registers){
    printf("$%02x $%02x $%02x $%02x $%02x $%02x $%02x  %04x\n", registers.a, registers.b, registers.c,
           registers.d, registers.e,registers.h, registers.l, registers.sp);

}


void Scheduler::update_pc(const uint16_t pc,const uint64_t cycle_count) {

    thread_table[Running_Thread_ID].registers.pc = pc;
    uint64_t cycle_run= cycle_count - thread_table[Running_Thread_ID].getStarting_cycle();
    //thread_table[Running_Thread_ID].setCycle(cycle_run);

}


int Scheduler::getRunning_Thread_ID() const {
    return Running_Thread_ID;
}

void Scheduler::setRunning_Thread_ID(uint8_t Running_Thread_ID) {
    Scheduler::Running_Thread_ID = Running_Thread_ID;
}

uint64_t Scheduler::getQuantum_time() const {
    return quantum_time;
}

void Scheduler::save_called_os_pc(uint16_t os_called_pc) {
    thread_table[Running_Thread_ID].setOs_called_pc(os_called_pc);
}
uint16_t Scheduler::get_called_os_pc(){
    return thread_table[Running_Thread_ID].getOs_called_pc();
}
void Scheduler::tjoin(const uint8_t waiting_tid){

    //thread_table[Running_Thread_ID].waiting_tids.push_back(waiting_tid); //beklediği thread id yazılır

    //beklenimek istenen thread çoktan ölmüş olabilir.
    if (thread_table[waiting_tid].getAvailable() == 1){
        thread_table[Running_Thread_ID].waiting_tid = waiting_tid;          //Bekledigi thread id yazılır
        thread_table[Running_Thread_ID].setState(BLOCKED);                  //BLOCK the running thread.
    }

}
