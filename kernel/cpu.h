#include "def.h"

typedef struct
{
    uint8 apicid;
    uint8 state;
} Core;


struct Cpu
{
    Core cores[CORENUM];
};



