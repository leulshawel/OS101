#include "cpu.c"
#include "consol.c" 
#include "mem.c"
#include "../usr/initd.c"



//Kernel entry point
int _101(int* stackBase, int* cpuid){
    Core core;
    char id = (char) cpuid >> 24;
    cpu.cores[id] = core;

    consolInit101();                        //initcialize the virtual console
    startAps();                             //start the other Aps (intel MP specification)
    printf101("KERNEL101 initializing/");  
    printf101("KERNEL Memory lay out/");
    meminit101();                           //initialize the memory

    
    memLayout101();                       //print the memory sections created so far
    
    //fsinit101();                          //initialize file system
    while (true);
}












