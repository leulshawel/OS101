#include "cpu.c"
#include "consol.c" 
#include "mem.c"



//Kernel entry point
int _101(int* stackBase, int* cpuid, void* gdtAddr, void* kerSegGDTAddr, void*usrSegGDTAddr){
    //this logical processor
    struct Core core;
    char id = (char) cpuid >> 24;  //id passed from entry code                     
    cpu.cores[id] = &core;          //add this core in to the cpu structure                     

    //initcialize the virtual console
    consolInit101();    
    //start the other Aps (intel MP specification) [ Not working:( ]                                
    startAps();                                         

    printf101("KERNEL101 initializing/");  
    
    //initialize the memory
    memInit101(gdtAddr, kerSegGDTAddr, usrSegGDTAddr, stackBase);

    //print the memory sections created so far
    //printf101("KERNEL Memory lay out/");
    //memLayout101();                                     
    
    //initialize file system
    //fsinit101();                                      
    while (true);
}














