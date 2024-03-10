#include "def.h"
#include "mem.h"

extern char* kend; //The end of kernel code provided by the linker but not working properly so far

void meminit101(void* gdtAddr, void*kerSegGDTAddr, void*usrSegGDTAddr){
    //before building the memolry layout in layout section clear it first
    memset101((void*)ram, 0x0, 0x0fff);
    //add the two segments in the ram 
    ram[0] = &kernelSeg;
    ram[1] = &userSeg;

    //the kernel segment    defined in mem.h
    kernelSeg.owner = "101";
    kernelSeg.start = 0x0;
    kernelSeg.end =  KERSEGLIM;
    kernelSeg.gdtAddr =  kerSegGDTAddr;
    kernelSeg.access = ((char*)kerSegGDTAddr)[5];

    //the user segment
    userSeg.owner = "usr";
    userSeg.start = KERSEGLIM + 1;
    userSeg.end =  0xffffffff;
    userSeg.access = ((char*)usrSegGDTAddr)[5];


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
    //if the kernel ever needs memory it gets it from this section
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
    struct Segment** index = ram;
    struct Segment* seg;
    for(; *index; index++){
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
        userSeg.sections[userSeg.secNum] = sec;
        userSeg.secNum++;
    }
    else{
        kernelSeg.sections[kernelSeg.secNum] = sec;
        kernelSeg.secNum++;

    }

}