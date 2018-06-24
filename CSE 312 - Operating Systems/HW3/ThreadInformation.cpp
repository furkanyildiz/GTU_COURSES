//
// Created by yldzf on 14.04.2018.
//

#include "ThreadInformation.h"


void ThreadInformation::setRegisterPC(const uint16_t pc) {
    ThreadInformation::registers.pc = pc;
}

State8080  ThreadInformation::getRegisters() const {
    return registers;
}


void ThreadInformation::setRegisters(State8080 registers) {
    ThreadInformation::registers = registers;
}

uint8_t ThreadInformation::getThread_id() const {
    return thread_id;
}

void ThreadInformation::setThread_id(uint8_t thread_id) {
    ThreadInformation::thread_id = thread_id;
}

uint64_t ThreadInformation::getStarting_cycle() const {
    return starting_cycle;
}

void ThreadInformation::setStarting_cycle(uint64_t starting_cycle) {
    ThreadInformation::starting_cycle = starting_cycle;
}

uint64_t ThreadInformation::getCycle() const {
    return cycle;
}

void ThreadInformation::setCycle(uint64_t cycle) {
    ThreadInformation::cycle = cycle;
}

ProcessState ThreadInformation::getState() const {
    return state;
}

void ThreadInformation::setState(ProcessState state) {
    ThreadInformation::state = state;
}

uint32_t ThreadInformation::getAddress() const {
    return address;
}

void ThreadInformation::setAddress(uint32_t address) {
    ThreadInformation::address = address;
}

uint8_t ThreadInformation::getStack_space() const {
    return stack_space;
}

void ThreadInformation::setStack_space(uint8_t stack_space) {
    ThreadInformation::stack_space = stack_space;
}

uint8_t ThreadInformation::getAvailable() const {
    return available;
}

void ThreadInformation::setAvailable(uint8_t available) {
    ThreadInformation::available = available;
}

ThreadInformation::ThreadInformation()  {

    //registers = (State8080*) calloc(1,sizeof(State8080));

}

ThreadInformation::~ThreadInformation() {
    //free(registers);
}

uint16_t ThreadInformation::getOs_called_pc() const {
    return os_called_pc;
}

void ThreadInformation::setOs_called_pc(uint16_t os_called_pc) {
    ThreadInformation::os_called_pc = os_called_pc;
}

