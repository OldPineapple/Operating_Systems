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

PCB *makePCB(int totalPageNumber, int frame, FILE *p);
