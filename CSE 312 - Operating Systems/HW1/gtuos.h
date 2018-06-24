
#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"

#if defined __UINT32_MAX__ or UINT32_MAX
  #include <inttypes.h>
#else
  typedef unsigned char uint8_t;
  typedef unsigned short uint16_t;
  typedef unsigned long uint32_t;
  typedef unsigned long long uint64_t;
#endif

class GTUOS{
	public:
		uint64_t handleCall(const CPU8080 & cpu);
		void saveMemory(const CPU8080 & cpu, std::string filename)const;
	private:
		uint64_t handlePrintB(const uint8_t x)const;
		uint64_t handlePrintMem(const CPU8080& cpu)const;
		uint64_t handleReadB(uint8_t *x)const;
		uint64_t handleReadMem(const CPU8080& cpu)const;
		uint64_t handlePrintStr(const CPU8080& cpu)const;
		uint64_t handleReadStr(const CPU8080& cpu)const;
		uint64_t handleGetRnd(uint8_t *x)const;


        const uint64_t PRINT_B_CYCLE=10;
        const uint64_t PRINT_MEM_CYCLE=10;
        const uint64_t READ_B_CYCLE=10;
        const uint64_t READ_MEM_CYCLE=10;
        const uint64_t PRINT_STR_CYCLE=100;
        const uint64_t READ_STR_CYCLE=100;
        const uint64_t GET_RND_CYCLE=5;


        enum SYS_CALLS{
            PRINT_B = 1,
            PRINT_MEM = 2,
            READ_B = 3,
            READ_MEM = 4,
            PRINT_STR = 5,
            READ_STR = 6,
            GET_RND = 7
        };


};

#endif
