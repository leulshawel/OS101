#define NULL        0                   //NULL definition
#define true        0x1                 //boolian true definition

#define CORENUM     8                   //max number of cores running
#define VIDEOMEM    0x0b8000            //mem mapped screen address
#define VIDMEMEND   VIDEOMEM+160*25     //console memory end
#define PROCNUM     4                   //process numner 
#define KERSEGLIM   0x3ffff000          //kernel segment limit
#define SEGNUM      0x3                 //number of memory segments defined in the gdt  NULL, KERNEL, USER
#define KERSTART    0x2000              //kernel code starts here
#define USRSEGSTART 0x3ffff001          //the user segment should start at the kernel limit + 1
#define MEMDSADDR   0x1000              //memory data structure address
#define PROCDSADDR  MEMDSADDR+4*(SEGNUM-1)  //the process data structure begins at the end of memory layout 



typedef char uint8;




