#include "def.h"


#define MAXPROC 4
#define NEW   0
#define READY  1
#define WAITING   3
#define RUNNING 4
#define EXITED 5


//main kernel process we will see if we ever need
//to have other kernel processes
struct Proc** processes = (struct Proc**) PROCDSADDR; //right below the ram
struct Proc proc101;

struct Proc{
    uint8 state; //running, ready, idle
    uint8 id;    //we dont expect more than 256 processes running at a time
    void* ip;    //the instruction pointer (Entry for new and break point for intrupted  processes)
    struct CpuCtx* ctx;     //used in context switching
    struct Proc* parent;    //who started that process
};





