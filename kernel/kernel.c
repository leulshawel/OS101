#include "cpu.c"
#include "consol.c" 
#include "mem.c"



//Kernel entry point
int _101(int* stackBase, int* cpuid, void* gdtAddr, void* kerSegGDTAddr, void*usrSegGDTAddr){
    //this logical processor
    struct Core core;
    char id = (char) cpuid >> 24;   //id passed from entry code                     
    cpu.cores[id] = &core;          //add this core in to the cpu structure                     

    //initcialize the virtual console
    consolInit101();    
    //start the other Aps (intel MP specification) [ TODO: Not working:( ]                                
    startAps();                                         

    printf101("KERNEL101 initializing/");  
    
    //initialize the memory
    memInit101(gdtAddr, kerSegGDTAddr, usrSegGDTAddr, stackBase);

    //initialize process management and data structure
    procInit101();
    
    //print process and memory tables
    procPrint101();
    printMem101();

    //for (int i=0; i < 10; i++);
    printhex101(&kend, 4);                        
    
    //initialize file system
    //fsinit101();                                      
    while (true);
}














