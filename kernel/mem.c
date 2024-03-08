#include "def.h"
#include "mem.h"

extern char* kend; //The end of kernel code provided by the linker but not working properly so far
void meminit101(){
    //create a kernel memory KERSTART -> kend
    kernelMem.start = KERSTART;
    kernelMem.end = kend;
    kernelMem.owner = "101";
    kernelMem.flags = (char) (RD | WR | EX);

    //create console memory
    consolMem.start = VIDEOMEM;
    consolMem.end = VIDMEMEND;
    consolMem.owner = "cns";
    consolMem.flags = (char) (RD | WR);

    //the rest of memory in kernel segment 
    kernelMem2.start = kend+1 ;
    kernelMem2.end = KERSEGLIM;
    kernelMem2.owner = "_";
    kernelMem2.flags = (char) (RD | WR );

    //the rest of memory in kernel segment 
    gdt.start = GDTSTART;
    gdt.end = GDTSTART + 8*SEGNUM;
    gdt.owner = "gdt";
    gdt.flags = (char) (RD);

    //zero out the memory layout address before building the layout
    memset101((char*)ram, 0x0, 0x0fff);
    

    ram[0] = &kernelMem;    //add to layout
    ram[1] = &consolMem;    //add to layout
    ram[2] = &kernelMem2;   //add to layout
    ram[3] = &gdt;          //add to layout

    //clear every memory except mapped I/O and KERNEL segment
    //memset101(kend, 0x0, (KERSEGLIM - (int)kend));
    //build a memory data structuret starting at kend

}

//set a range of memory bytes to value
void memset101(void* start, char value, int size){
    char* index = start;
    for (; index < start + size; index++)
        *index = value;

}

//print the memory sections
void memLayout101(){
    struct Memory** index = ram;
    struct Memory* mem;
    for(; *index; index++){
        mem = *index;
        printf101("/Owner: ");
        printf101(mem->owner);
        printf101("/starting: ");
        printhex101(&(mem->start), 4);
        printf101("/ends at: ");
        printhex101(&(mem->end), 4);
    }
}