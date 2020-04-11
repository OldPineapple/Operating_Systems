#include "pcb.h"
typedef struct ReadyQueueNode {
    PCB*  PCB;
    struct ReadyQueueNode* next;
} ReadyQueueNode;
/*
Adds a pcb to the tail of the linked list
*/
void addToReady(struct PCB*);

/*
Returns the size of the queue
*/
int size();
void boot();
int kernel();

/*
Pops the pcb at the head of the linked list.
pop will cause an error if linkedlist is empty.
Always check size of queue using size()
*/
struct PCB* pop();

/*
Passes a filename
Opens the file, copies the content in the RAM.
Creates a PCB for that program.
Adds the PCB on the ready queue.
Return an errorCode:
ERRORCODE 0 : NO ERROR
ERRORCODE -3 : SCRIPT NOT FOUND
ERRORCODE -5 : NOT ENOUGH RAM (EXEC)
*/
int myinit(char*);

int scheduler();

/*
Flushes every pcb off the ready queue in the case of a load error
*/
void emptyReadyQueue();

struct ReadyQueueNode *getHead();
