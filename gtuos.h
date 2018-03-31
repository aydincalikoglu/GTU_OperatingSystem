#ifndef H_GTUOS
#define H_GTUOS

#include "8080emuCPP.h"
#include <fstream>
#include <stdlib.h>
using namespace std;


class GTUOS{
	public:
        GTUOS();
		uint64_t handleCall(const CPU8080 & cpu);
		void printMemFile(const CPU8080 & cpu);
	private:
		uint64_t printB(const CPU8080 & cpu);
		uint64_t printMem(const CPU8080 & cpu);
		uint64_t readB(const CPU8080 & cpu);
		uint64_t readMem(const CPU8080 & cpu);
		uint64_t printStr(const CPU8080 & cpu);
		uint64_t readStr(const CPU8080 & cpu);
		uint64_t getRND(const CPU8080 & cpu);



};

#endif
