
#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include <string>
#include <queue>          // std::queue
#include "ThreadInformation.h"

#if defined __UINT32_MAX__ or UINT32_MAX
#include <inttypes.h>
#else
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
#endif
#define THREAD_NUM 256
#define STACK_SPACE 255

class GTUOS{

class Scheduler {
public:
    friend class GTUOS;
    Scheduler(const CPU8080* cpu8080,uint64_t *cycle_count,const uint64_t quantum,int debug);
    Scheduler(){};
    uint64_t getQuantum_time() const;
    int getRunning_Thread_ID() const;
    void setRunning_Thread_ID(uint8_t Running_Thread_ID);
    bool schele(CPU8080 *CPU8080, int os_call);
    void update_pc(const uint16_t pc,const uint64_t cycle_count);

private:
    int DEBUG;
    ThreadInformation thread_table[THREAD_NUM];
    std::queue<ThreadInformation*> round_robin_queue;
    void save_called_os_pc(uint16_t os_called_pc);
    uint16_t get_called_os_pc();
    uint64_t quantum_time;
    uint8_t Running_Thread_ID;
    uint64_t last_time;
    uint64_t *cycle_count;
    int exit_thread();
    int add_new_thread(uint16_t pc, uint64_t cycle_count);
    void tjoin(const uint8_t waiting_tid);
    void interrupt_handler(uint8_t exit_thread_id);
    void copyRegisters(State8080 registers);
    void print_registers(State8080 registers);
    void update_thread_cycle(int tid, uint64_t c){thread_table[tid].cycle+=c;}
    void print_thread_information();

};




public:
    GTUOS(CPU8080* cpu8080,uint64_t* cycle_c,int debug);
    uint64_t handleCall(uint64_t *cycle, bool * context_switch);
    void saveMemory(const CPU8080 & cpu, std::string filename)const;
    void timer_interrupt(uint64_t *cycle);
    bool is_context_switch_happen() const{return context_switch_happen;}
    void calculatePC(int mode);
    void setContext_switch_happen(bool context_switch_happen);
    void saveStatus(){
        theCPU->state = returnState;

    }
private:
    Scheduler scheduler;
    CPU8080 *theCPU;
    uint64_t *cycle_count;
    bool context_switch_happen = false;
    uint64_t handlePrintB()const;
    uint64_t handlePrintMem()const;
    uint64_t handleReadB()const;
    uint64_t handleReadMem()const;
    uint64_t handlePrintStr()const;
    uint64_t handleReadStr()const;
    uint64_t handleGetRnd()const;
    uint64_t handleTCreate(uint64_t *cycle);
    uint64_t handleTExit(uint64_t *cycle);
    uint64_t handleTJoin(uint64_t *cycle);
    uint64_t handleTYield(uint64_t *cycle);
    uint16_t oscallpc;
    const uint64_t PRINT_B_CYCLE=10;
    const uint64_t PRINT_MEM_CYCLE=10;
    const uint64_t READ_B_CYCLE=10;
    const uint64_t READ_MEM_CYCLE=10;
    const uint64_t PRINT_STR_CYCLE=100;
    const uint64_t READ_STR_CYCLE=100;
    const uint64_t GET_RND_CYCLE=5;
    const uint64_t TEXIT_CYCLE=50;
    const uint64_t TJOIN_CYCLE=40;
    const uint64_t TYIELD_CYCLE=40;
    const uint64_t TCREATE_CYCLE=80;
    State8080* returnState;

    enum SYS_CALLS{
        PRINT_B = 1,
        PRINT_MEM = 2,
        READ_B = 3,
        READ_MEM = 4,
        PRINT_STR = 5,
        READ_STR = 6,
        GET_RND = 7,
        TEXIT = 8,
        TJOIN = 9,
        TYIELD = 10,
        TCREATE = 11

    };


};

#endif
