#define RD 0x1  //read
#define WR 0x2  //write
#define EX 0x4  //execute

// a section of memory
struct Memory{
    void* start;
    void* end;
    char* owner;
    char flags;
};

struct Memory** ram = 0x1000; //memory lay out stored at this address

struct Memory kernelMem;    //kernel code
struct Memory kernelMem2;   //remainnig section of kernel segment after the kernel code to the end of kernel segment
struct Memory consolMem;    //console is mapped at this memory at least in QEMU
struct Memory gdt;          //gdt address for 101


void memset101(void* start, char value, int size);