#define RD 0x1  //read
#define WR 0x2  //write
#define EX 0x4  //execute


//a chunk of memory
//this is what we will use to keep 
//track of memory chuncks owner processes
//and also used to to buid a datastructure of the 
//user memory segment
struct Section{
    void* start;    //start addr of section
    void* end;      //end addr 
    char* owner;    //owner process of kernel (free sections are owned by _)
    struct Proc* ownerProc; //owner process
    char flags;     //the flags related to this section
    uint8 secId;    //id of this section (used as entry in to the sections array of a segment)
    struct Segment* seg;    //which segment this section is in 
};

//segment of memory
struct Segment{
    void* start;        //base of segment
    void* end;          //limit of this segment
    void* gdtAddr;      //segment index in gdt
    char* owner;        //kernel or user
    uint8 flags;        //pointer to the flags of the segment
    uint8 access;       //pointer to the access flags of this segment
    uint8 secNum;       //number of sections under this segment
    struct Secion** sections; //sections under this segment
};





//memory lay out stored at this address
struct Segment** ram = (struct Segment**)MEMDSADDR; 

//the two segments of memory
struct Segment kernelSeg;   //highest previlage kernel segment
struct Segment userSeg;     //low previlage user segment

//predefined sections of memory in kernel segment
struct Section kernelStack;  //the kernel stack section
struct Section kernelMem;    //kernel code
struct Section kernelFree;   //remainnig section of kernel segment after the kernel code to the end of kernel segment
struct Section consolMem;    //console is mapped at this memory at least in QEMU
struct Section gdt;          //gdt address for 101

//build a data strcuture for the sections 
//in useer segment (a linked list)


void memset101(void* start, char value, int size);