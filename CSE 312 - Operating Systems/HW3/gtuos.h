
#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include <string>
#include <queue>          // std::queue
#include "ThreadInformation.h"
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
#define BLOCK_CAP 4096
#define BLOCK_SIZE 256
#define TEST_DEBUG 0//this is my debug to see what is happening when i was programming.


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
    GTUOS(CPU8080* cpu8080,uint64_t* cycle_c,int debug,const char* file_system_file_name_);
    ~GTUOS();
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
    int DEBUG;
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
    uint64_t handleFileCreate();
    uint64_t handleFileClose();
    uint64_t handleFileOpen();
    uint64_t handleFileRead();
    uint64_t handleFileWrite();
    uint64_t handleFileSeek();
    uint64_t handleDirRead();

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

    const uint64_t FCREATE_CYCLE=0;
    const uint64_t FCLOSE_CYCLE=0;
    const uint64_t FOPEN_CYCLE=0;
    const uint64_t FREAD_CYCLE=0;
    const uint64_t FWRITE_CYCLE=0;
    const uint64_t FSEEK_CYCLE=0;
    const uint64_t DIRREAD_CYCLE=0;

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
        TCREATE = 11,
        FileCreate = 12,
        FileClose = 13,
        FileOpen = 14,
        FileRead = 15,
        FileWrite = 16,
        FileSeek = 17,
        DirRead = 18
    };

    struct Block
    {
        int data[256];
        int is_in_use;
        int size; // how many bytes are filled from 256 bytes
        int block_num;
        int owner; //who is owner the block
    };
    Block blocks[4096];

    struct File_informations
    {
        char filename[100];
        int file_pointer;
        int size;           //size of file as bytes
//        uint64_t creation_time;
//        uint64_t last_modification_time;
//        uint64_t last_access_time;
        char creation_time[30];
        char last_modification_time[30];
        char last_access_time[30];

        int alloc_blocks[50];
        int alloc_block_num;
        int fileID;

    };
    File_informations files[4096];
    std::vector<File_informations*> open_files_table;
    time_t current_time;
    int file_count;
    int is_there_free_block;
    int compaction(int block_num);
    int alloc_new_block(int file_num);
    const char* file_system_file_name;
};

#endif
