#include <iostream>
#include <time.h>
#include "8080emuCPP.h"
#include "gtuos.h"

GTUOS::GTUOS()
{
    srand(time(0));
}

uint64_t GTUOS::handleCall(const CPU8080 & cpu){
    /* TEST AREA */
    uint8_t b = (cpu.state->b);
    uint8_t c = (cpu.state->c);
    uint32_t memStartAddr=b*256+c;
/*
    cout<<"A:"<<unsigned(cpu.state->a)<<endl;
    cout<<"B:"<<unsigned(cpu.state->b)<<endl;
    cout<<"C:"<<unsigned(cpu.state->c)<<endl;
*/
    switch(unsigned(cpu.state->a))
    {
        case 1:/* Print_B */
            return printB(cpu);
        case 2:/* Print_Mem */
            return printMem(cpu);
        case 3:/* Read_B */
            return readB(cpu);
        case 4:/* Read_Mem */
            return readMem(cpu);
        case 5:/* Print_Str */
            return printStr(cpu);
        case 6:/* Read_Str */
            return readStr(cpu);
        case 7:/* Get_RND */
            return getRND(cpu);
        default:
            cerr<<"Error : Unimplemented OS call"<<endl;
            throw -1;
    }
}
uint64_t GTUOS::printB(const CPU8080 & cpu){
    cout<<(unsigned)(cpu.state->b);
    return 10;
}
uint64_t GTUOS::printMem(const CPU8080 & cpu){
    uint8_t b = (cpu.state->b);
    uint8_t c = (cpu.state->c);
    uint32_t memStartAddr=b*256+c;
    cout<<(unsigned)(cpu.memory->physicalAt(memStartAddr));
    return 10;
}
uint64_t GTUOS::readB(const CPU8080 & cpu){
    int readB;
    //cout<<("Write a uint8_t for RegB:");
    cin>>readB;
    cpu.state->b=(uint8_t)readB;
    return 10;
}
uint64_t GTUOS::readMem(const CPU8080 & cpu){
    uint8_t b = (cpu.state->b);
    uint8_t c = (cpu.state->c);
    uint32_t memStartAddr=b*256+c;
    int readMem;
    //1cout<<("Write a uint8_t for MemBC:");
    cin>>readMem;
    cpu.memory->physicalAt(memStartAddr)=(unsigned)readMem;
    return 100;
}
uint64_t GTUOS::printStr(const CPU8080 & cpu){
    uint8_t b = (cpu.state->b);
    uint8_t c = (cpu.state->c);
    uint32_t memStartAddr=b*256+c;

    for (uint32_t i = memStartAddr;  cpu.memory->physicalAt(i) != 0; ++i) {

        cout<<(cpu.memory->physicalAt(i));
    }
    return 100;
}
uint64_t GTUOS::readStr(const CPU8080 & cpu){
    uint8_t b = (cpu.state->b);
    uint8_t c = (cpu.state->c);
    uint32_t memStartAddr=b*256+c;

    //cout<<("Read String :");
    string readStr="";

    getline(cin, readStr);
    cin>>readStr;
    cout<<readStr<<endl;
    for (uint32_t i = memStartAddr,j = 0; j <= readStr.length(); ++memStartAddr,++j) {
        if (j!=readStr.length())
            cpu.memory->physicalAt(i)=readStr[j];
        else
            cpu.memory->physicalAt(i)=(unsigned)0;
    }
    return 100;
}

uint64_t GTUOS::getRND(const CPU8080 & cpu){
    uint8_t randNumber;
    cpu.state->b = randNumber = (uint8_t)(unsigned)(rand()%256);
    //cout<<(unsigned)randNumber<<"-";
    return 5;
}


/* PUBLIC AREA */

void GTUOS::printMemFile(const CPU8080 & cpu)
{
    string fileName="exe.mem";

    ofstream outfile;
    outfile.open(fileName.c_str());

    for (int i = 0; i < 4096; ++i) {
        outfile<<hex<<i*16<<": ";
        for (int j = 0; j < 16; ++j) {
            uint32_t addr=i*16+j;
            outfile<<hex<<(unsigned)cpu.memory->physicalAt(addr)<<" ";
        }
        outfile<<endl;
    }

    outfile.close();
}