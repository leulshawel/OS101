#include "def.h"
#include "mem.h"

extern char* kend; //The end of kernel code provided by the linker but not working properly so far

void meminit101(void* gdtAddr, void*kerSegGDTAddr, void*usrSegGDTAddr){
    //the kernel segment    defined in mem.h
    kernelSeg.start = 0x0;
    kernelSeg.end =  KERSEGLIM;

    //the user segment
    userSeg.start = KERSEGLIM + 1;
    userSeg.end =  0xffffffff;

    //create a kernel section KERSTART -> kend
    kernelMem.start = KERSTART;
    kernelMem.end = kend;
    kernelMem.owner = "101";
    kernelMem.flags = (char) (RD | WR | EX);
    kernelMem.seg = &kernelSeg;


    //create console section
    consolMem.start = VIDEOMEM;
    consolMem.end = VIDMEMEND;
    consolMem.owner = "cns";
    consolMem.flags = (char) (RD | WR);
    consolMem.seg = &kernelSeg;

    //remaining sections in the kernel segment 
    //if the kernel ever needs memory it gets it from this chunck
    kernelMem2.start = kend+1 ;
    kernelMem2.end = KERSEGLIM;
    kernelMem2.owner = "_";
    kernelMem2.flags = (char) (RD | WR );
    kernelMem2.seg = &kernelSeg;


    //Global desriptor table section
    gdt.start = gdtAddr;
    gdt.end = gdt.start + 8*SEGNUM;
    gdt.owner = "gdt";
    gdt.flags = (char) (RD);
    gdt.seg = &kernelSeg;



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
    struct Section** index = ram;
    struct Section* mem;
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



//allocate p number of pages 
void kmalloc(uint8 p){

}

//add a section in to the right segment
void addSectoSeg(struct Section* sec){
    if (sec->start >= USRSEGSTART)
        *(userSeg.sections + userSeg.secNum) = sec;
    else
        *(kernelSeg.sections + kernelSeg.secNum) = sec;

    
}