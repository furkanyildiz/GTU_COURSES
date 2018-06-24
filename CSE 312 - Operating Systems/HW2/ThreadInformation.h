//
// Created by yldzf on 14.04.2018.
//

#ifndef OS_HW_2_THREADINFORMATION_H
#define OS_HW_2_THREADINFORMATION_H

#include "8080emuCPP.h"
#include <vector>

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

typedef enum {
    READY = 0,
    BLOCKED = 1,
    RUNNING = 2
} ProcessState;
class ThreadInformation{

//public:
//class Scheduler;

public:
    ThreadInformation();
    friend class GTUOS;
private:
    State8080 registers;		//The saved register set of 8080 chip
    uint8_t thread_id;			//The thread ID
    uint64_t starting_cycle;	//Starting time of the thread (the cycle number of the CPU)
    uint64_t cycle;     		//How many cycles the thread has used so far
    ProcessState state;         //The state of the thread (ready, blocked, running)
    uint32_t address;   		//The starting address of the memory location of the thread function
    uint8_t  stack_space;		//Available empty stack space
    uint8_t available;
    uint16_t os_called_pc;
    int16_t waiting_tid;       //devam etmek icin bitmesi beklenilen thread id. (from tjoin)
    //std::vector<uint8_t> waiting_tids;
public:
    uint16_t getOs_called_pc() const;

    void setOs_called_pc(uint16_t os_called_pc);



public:
    void setRegisterPC(const uint16_t pc);

    State8080  getRegisters() const;

    void setRegisters(State8080 registers);

    uint8_t getThread_id() const;

    void setThread_id(uint8_t thread_id);

    uint64_t getStarting_cycle() const;

    void setStarting_cycle(uint64_t starting_cycle);

    uint64_t getCycle() const;

    void setCycle(uint64_t cycle);

    ProcessState getState() const;

    void setState(ProcessState state);

    uint32_t getAddress() const;

    void setAddress(uint32_t address);

    uint8_t getStack_space() const;

    void setStack_space(uint8_t stack_space);

    uint8_t getAvailable() const;

    void setAvailable(uint8_t available);

    virtual ~ThreadInformation();




};


#endif //OS_HW_2_THREADINFORMATİON_H
