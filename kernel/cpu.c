#include "cpu.h"
extern void initSipiSipi();

struct  Cpu cpu;

void moveApCode(){
    char* startaddr = (char*)0x2026;
    char* dest = (char*)0x1000;
    for (; startaddr < (char*)0x205b; startaddr++){
        *dest = *startaddr;
        *startaddr = 0x0;
        dest++;
    }
}

void startAps(){
    moveApCode();

    //send INIT
    asm volatile ("mov $4276093696, %esi;"
                "mov $804096, %eax;"
                "mov %eax, (%esi);");
    //wait for 10ms
    for(int i=100; i; i--); //just an idea
    //send SIPI
    asm volatile ("mov $4276093696, %esi;"
                "mov $804353, %eax;"
                "mov %eax, (%esi);");
    //wait for 200us
    for(int i=10; i; i--);
    //send SIPI
    asm volatile ("mov $4276093696, %esi;"
                "mov $804353, %eax;"
                "mov %eax, (%esi);");
}