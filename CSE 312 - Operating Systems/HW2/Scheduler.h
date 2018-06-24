//
// Created by yldzf on 13.04.2018.
//
#include <queue>          // std::queue

#ifndef OS_HW_2_SCHEDULER_H
#define OS_HW_2_SCHEDULER_H

#if defined __UINT32_MAX__ or UINT32_MAX
#include <inttypes.h>
#else
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
#endif
#include <iostream>
#include "ThreadInformation.h"
#define THREAD_NUM 256
#define STACK_SPACE 255

//class Scheduler;

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
    //    std::queue<std::reference_wrapper<ThreadInformation>> round_robin_queue;
    //std::queue<ThreadInformation> round_robin_queue;
//    std::queue<std::shared_ptr<ThreadInformation>> round_robin_queue;
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


#endif //OS_HW_2_SCHEDULER_H
