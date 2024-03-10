#define RD 0x1  //read
#define WR 0x2  //write
#define EX 0x4  //execute

// a section of memory
struct Section{
    void* start;
    void* end;
    char* owner;
    char flags;
    uint8 secId;
    struct Segment* seg;
};

struct Segment{
    void* start;        //base of segment
    void* end;          //limit of this segment
    void* gdtAddr;        //segment index in gdt
    char* owner;        //kernel or user
    uint8 flags;        //pointer to the flags of the segment
    uint8 access;       //pointer to the access flags of this segment
    uint8 secNum;       //number of sections under this segment
    struct Secion** sections; //sections under this segment
};

//the two segments of memory
struct Segment kernelSeg;   //highest previlage kernel segment
struct Segment userSeg;     //low previlage user segment

//memory lay out stored at this address
struct Segment** ram = (struct Segment**)0x1000; 



struct Section kernelMem;    //kernel code
struct Section kernelMem2;   //remainnig section of kernel segment after the kernel code to the end of kernel segment
struct Section consolMem;    //console is mapped at this memory at least in QEMU
struct Section gdt;          //gdt address for 101


void memset101(void* start, char value, int size);