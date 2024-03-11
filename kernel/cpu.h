#include "def.h"

struct Core
{
    uint8 apicid;
    uint8 state;
};


struct Cpu
{
    struct Core* cores[CORENUM];
};

//core context (state of registers basically)
struct CoreCtx
{
    
};



