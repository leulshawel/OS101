#include "def.h"
#include "proc.h"



void procInit101(){
    //add the kernel main process in to the process data structure
    processes[0] = &proc101;
    proc101.id = 0; //first process
    proc101.state = RUNNING;
    proc101.parent = &proc101;
}


//print the process data structure
void procPrint101(){
    struct Proc** index = processes;
    for (; *index || index < 0x1008 + MAXPROC; index++){
        printf101("/PID: ");
        printhex101(&(index[0]->id), 1);

        printf101("/State: ");
        if (! index[0]->state)
            printf101("Exited");
        else if (index[0]->state == 1)
            printf101("Running");
        else if (index[0]->state == 2)
            printf101("Ready");
        else
            printf101("Invalid");

        printf101("/Parent: ");
        printhex101(&(index[0]->parent->id), 1);
    }

}