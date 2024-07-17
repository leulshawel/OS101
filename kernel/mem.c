#include "def.h"
#include "mem.h"
#include "proc.c"

extern char* kend; //The end of kernel code provided by the linker but not working properly so far


void memInit101(void* gdtAddr, void*kerSegGDTAddr, void*usrSegGDTAddr, void* stackBase){
    //before building the memolry layout in layout section clear it first
    memset101((void*)ram, 0x0, 0x0fff);
    //add the two segments in the ram 
    ram[0] = &kernelSeg;
    ram[1] = &userSeg;

    //the kernel segment    defined in mem.h
    kernelSeg.secNum = 0;
    kernelSeg.owner = "101";
    kernelSeg.start = 0x0;
    kernelSeg.end =  KERSEGLIM;
    kernelSeg.gdtAddr =  kerSegGDTAddr;
    kernelSeg.access = ((char*)kerSegGDTAddr)[5];

    //the user segment
    userSeg.secNum = 0;
    userSeg.owner = "usr";
    userSeg.start = KERSEGLIM + 1;
    userSeg.end =  0xffffffff;
    userSeg.access = ((char*)usrSegGDTAddr)[5];

    //kernel stack section
    kernelStack.start = 0x0;
    kernelStack.end = stackBase;
    kernelStack.owner = "101";
    kernelStack.flags = (char) (RD | WR | EX);
    kernelStack.secId = 0;
    kernelStack.ownerProc = &proc101;   
    addSectoSeg(&kernelStack);

    //create a kernel section KERSTART -> kend
    kernelMem.start = KERSTART;
    kernelMem.end = kend;
    kernelMem.owner = "101";
    kernelMem.flags = (char) (RD | WR | EX);
    kernelMem.secId = 1;
    kernelMem.ownerProc = &proc101;
    addSectoSeg(&kernelMem);


    //create console section
    consolMem.start = VIDEOMEM;
    consolMem.end = VIDMEMEND;
    consolMem.owner = "cns";
    consolMem.flags = (char) (RD | WR);
    consolMem.secId = 2;
    addSectoSeg(&consolMem);

    //remaining sections in the kernel segment 
    //if the kernel ever needs memory it gets it from this section
    kernelFree.start = kend+1 ;
    kernelFree.end = KERSEGLIM;
    kernelFree.owner = "_";
    kernelFree.flags = (char) (RD | WR );
    kernelFree.secId = 3;
    addSectoSeg(&kernelStack);

    //i know this could have been a function but....
    //just on more section to create
    //Global desriptor table section
    gdt.start = gdtAddr;
    gdt.end = gdt.start + 8*SEGNUM;
    gdt.owner = "gdt";
    gdt.flags = (char) (RD);
    gdt.secId = 4;
    addSectoSeg(&gdt);

    
    //covers the entire user segment 
    //all user processes get memory from this section
    main.start = USRSEGSTART;
    main.end = 0xffffffff;
    main.owner = NULL;
    main.flags = (char) (RD | WR | EX);
    main.secId = 0;             //zero section in user segment
    addSectoSeg(&main);

    //clear every memory except mapped I/O and KERNEL segment
    //memset101(kend, 0x0, (KERSEGLIM - (int)kend));

}

//set a range of memory bytes to value
void memset101(void* start, char value, int size){
    char* index = start;
    for (; index < start + size; index++)
        *index = value;

}

//print the memory sections
void printMem101(){
    struct Segment** index = ram;
    struct Segment* seg;
    for(; *index || index < PROCDSADDR; index++){
        seg = *index;
        printf101("/Segment Owner: ");
        printf101(seg->owner);
        printf101("/starting Addr: ");
        printhex101(&(seg->start), 4);
        printf101("/end Addr: ");
        printhex101(&(seg->end), 4);
        printf101("/Access flags: ");
        printhex101(&(seg->access), 1);
        printf101("/number of sections: ");
        printhex101(&(seg->secNum), 1);
        printf101("/");
    }
}



//allocate p number of pages 
void kmalloc(uint8 p){

}

//add a section in to the right segment
void addSectoSeg(struct Section* sec){
    if (sec->start >= USRSEGSTART){
        sec->seg = &userSeg; 
        userSeg.sections[userSeg.secNum] = sec;
        userSeg.secNum++;
    }
    else{
        sec->seg = &kernelSeg; 
        kernelSeg.sections[kernelSeg.secNum] = sec;
        kernelSeg.secNum++;

    }

}