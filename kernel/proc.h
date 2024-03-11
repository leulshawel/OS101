#include "def.h"


#define RUNNING 1
#define READY   2
#define EXITED 3


//main kernel process we will see if we ever need
//to have other kernel processes
struct Proc proc101;

struct Proc{
    uint8 state; //running, ready, idle
    uint8 id;    //we dont expect more than 256 processes running at a time 
    struct CpuCtx* ctx;
};





