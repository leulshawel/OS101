#define NULL 0                      //NULL definition
#define true 0x1                    //boolian true definition

#define CORENUM 8                   //max number of cores running
#define VIDEOMEM 0x0b8000           //mem mapped screen address
#define VIDMEMEND VIDEOMEM+160*25   //console memory end
#define PROCNUM 4                   //process numner 
#define KERSEGLIM 0xffffffff        //kernel segment limit
#define GDTSTART  0x7d2b            //address of gdt
#define SEGNUM      0x5              //number of memory segments defined in the gdt  NULL, KERNEL, USER
#define KERSTART  0x2000            //kernel code starts here


typedef char uint8;
void* stack;




