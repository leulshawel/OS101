#include "cpu.c"
#include "consol.c" 
#include "mem.c"
#include "../usr/initd.c"



//Kernel entry point
int _101(int* stackBase, int* cpuid, void* gdtAddr, void* kerSegGDTAddr, void*usrSegGDTAddr){
    //this logical processor
    Core core;
    char id = (char) cpuid >> 24;                       //id passed from entry code
    cpu.cores[id] = core;                               //add this core in to the cpu structure
    consolInit101();                                    //initcialize the virtual console
    startAps();                                         //start the other Aps (intel MP specification) [ Not working:( ]
    printf101("KERNEL101 initializing/");  
    printf101("KERNEL Memory lay out/");
    meminit101(gdtAddr, kerSegGDTAddr, usrSegGDTAddr);  //initialize the memory

    
    memLayout101();                                     //print the memory sections created so far
    
    //fsinit101();                                      //initialize file system
    while (true);
}












