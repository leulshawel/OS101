#include "def.h"


#define MAXPROC 4
#define RUNNING 1
#define READY   2
#define EXITED 0


//main kernel process we will see if we ever need
//to have other kernel processes
struct Proc** processes = (struct Proc**) PROCDSADDR; //right below the ram
struct Proc proc101;

struct Proc{
    uint8 state; //running, ready, idle
    uint8 id;    //we dont expect more than 256 processes running at a time 
    struct CpuCtx* ctx;     //used in context switching
    struct Proc* parent;    //who started that process
};





