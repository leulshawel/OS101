#include "def.h"

char* cursor = (char*) VIDEOMEM;
int row = 1;
void consolInit101(){
    
    for (; cursor < VIDMEMEND; cursor++){
        *cursor = 0x0;
        cursor ++;
        *cursor = 0x0;
    }
    cursor = (char*) VIDEOMEM;
}

void printhex101(char* addr, int len){
    char* table = "0123456789ABCDEF";
    char byte;
    int i, row;
    for (i=0; i < len; i++){
        byte = addr[i];
        *cursor = table[(byte & 0x0f0) >> 4];
        cursor ++;
        *cursor = 0xf;
        cursor ++;
        *cursor = table[byte & 0x0f];
        cursor ++;
        *cursor = 0xf;
        cursor ++;

        *cursor = 0x0;
        cursor ++;
        *cursor = 0xf;
        cursor ++;


    }

}


void printf101(char* string){
    int i;
    char character;
    for(i=0; string[i] != NULL ;i++){
        character = string[i];
        if (character == '/'){
            cursor = (char*)VIDEOMEM + 160*row;
            row += 1;
            continue;
        }
        *cursor = character;
        cursor++;
        *cursor = 0x0f;
        cursor++;
    }

}







