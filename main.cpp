#include <iostream>
#include <stdlib.h>

#include "8080emuCPP.h"
#include "gtuos.h"
#include "memory.h"

using namespace std;
	// This is just a sample main function, you should rewrite this file to handle problems 
	// with new multitasking and virtual memory additions.

int main (int argc, char**argv)
{
	if (argc != 3){
		std::cerr << "Usage: prog exeFile debugOption\n";
		exit(1); 
	}
	int DEBUG = atoi(argv[2]);
	memory mem;
	CPU8080 theCPU(&mem);
	GTUOS	theOS;
    int clockCycleCount=0;

	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);
 
	do	
	{
		theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall())
            clockCycleCount+=theOS.handleCall(theCPU);
        else
            clockCycleCount++;
        if(DEBUG==2) cin.get();
	}	while (!theCPU.isHalted());
    theOS.printMemFile(theCPU);
	cout<<endl<<"Total Number of cycles : "<<clockCycleCount<<endl;
	return 0;
}
