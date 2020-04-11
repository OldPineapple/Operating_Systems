#include <stdio.h>
#include <stdlib.h>
/*
PCB has 3 fields
PC : Points to the the current line reached for that program
start: Points to first line of that program
end: Points to last line of that program
*/
typedef struct PCB
{
    int PC;
    int pageTable[10];
    int PC_page;
    int PC_offset;
    int pages_max;
    FILE *p;
}PCB;


/*
Passes 2 parameters (start , end)
This method creates a PCB with fields set as this:
PC = start
start = start
end = end
*/
PCB* makePCB(int totalPageNumber, int frame, FILE *p){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->PC = frame * 4;
    pcb->pages_max = totalPageNumber;
    for (int i = 0; i < 10; i ++) {
        if (i == 0)
            pcb->pageTable[i] = frame;
        else
            pcb->pageTable[i] = 0;
    }
    pcb->p = p;
    pcb->PC_offset = 0;
    pcb->PC_page = 0;
    return pcb;
}


