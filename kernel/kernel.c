#include "cpu.c"
#include "consol.c" 
#include "mem.c"
#include "../usr/initd.c"



//Kernel entry point
int _101(int* stackBase, int* cpuid, void* gdtAddr, void* kerSegGDTAddr, void*usrSegGDTAddr){
    //this logical processor
    Core core;
    char id = (char) cpuid >> 24;  //id passed from entry code                     
    cpu.cores[id] = core;          //add this core in to the cpu structure                     

    //initcialize the virtual console
    consolInit101();    
    //start the other Aps (intel MP specification) [ Not working:( ]                                
    startAps();                                         

    printf101("KERNEL101 initializing/");  
    printf101("KERNEL Memory lay out/");
    //initialize the memory
    meminit101(gdtAddr, kerSegGDTAddr, usrSegGDTAddr);

    //print the memory sections created so far
    memLayout101();                                     
    
    //initialize file system
    //fsinit101();                                      
    while (true);
}












