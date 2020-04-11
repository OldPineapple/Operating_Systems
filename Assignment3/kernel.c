#include<stdio.h>
#include<stdlib.h>
#include"shell.h"
#include"ram.h"
#include"cpu.h"
#include"interpreter.h"
#include"pcb.h"
#include"memorymanager.h"

/*
This is a node in the Ready Queue implemented as
a linked list.
A node holds a PCB pointer and a pointer to the next node.
PCB: PCB
next: next node
*/
typedef struct ReadyQueueNode {
    PCB*  PCB;
    struct ReadyQueueNode* next;
} ReadyQueueNode;

ReadyQueueNode* head = NULL;
ReadyQueueNode* tail = NULL;
int sizeOfQueue = 0;

int kernel()
{
   return shellUI();
}

void boot() {
    for(int i = 0; i < 40; i ++) {
        ram[i] = NULL;
    }
    system("rm -rf BackingStore");
    system("mkdir BackingStore");
}

/*
Adds a pcb to the tail of the linked list
*/
void addToReady(PCB* pcb) {
    ReadyQueueNode* newNode = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
    newNode->PCB = pcb;
    newNode->next = NULL;
    if (head == NULL){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    sizeOfQueue++;
}

struct ReadyQueueNode *getHead() {
    return head;
}

/*
Returns the size of the queue
*/
int size(){
    return sizeOfQueue;
}

/*
Pops the pcb at the head of the linked list.
pop will cause an error if linkedlist is empty.
Always check size of queue using size()
*/
struct PCB* pop(){
    PCB* topNode = head->PCB;
    ReadyQueueNode * temp = head;
    if (head == tail){
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
    }
    free(temp);
    sizeOfQueue--;
    return topNode;
}

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
int myinit(char* filename){
    FILE * fp = fopen(filename,"r");
    if (fp == NULL) return -3;
    int frame = findFrame();
    int page = countTotalPages(fp);
    rewind(fp);
    loadPage(0, fp, frame);
    PCB *pcb = makePCB(page, frame, fp);
    if (page < 2) {
        addToReady(pcb);
    }
    else {
        loadPage(1, fp, frame);
        updatePageTable(pcb, 1, frame, findVictim(pcb));
        addToReady(pcb);
    }
    fclose(fp);
    return 0;
}

int scheduler(){
    // set CPU quanta to default, IP to -1, IR = NULL
    CPU.quanta = DEFAULT_QUANTA;
    CPU.offset = 0;
    CPU.IP = -1;
    while (size() != 0){
        PCB* pcb = pop();
        int page = pcb->PC_page;
        CPU.IP = pcb->pageTable[page] * 4;
        CPU.offset = pcb->PC_offset;
        
        int isOver = FALSE;
        int remaining = (pcb->pages_max) - (pcb->PC_page) + 1;
        int quanta = DEFAULT_QUANTA;

        if (remaining == 1) {
            isOver = TRUE;
        }
        
        int errorCode = run(quanta);

        if (errorCode == -1){
            int fault = pageFault(pcb);
            if (fault == 0) {
                removeFromRam(pcb->pageTable);
                free(pcb);
            }
            else {
                addToReady(pcb);
            }
        }
        else if (errorCode == 1) {
            removeFromRam(pcb->pageTable);
            free(pcb);
        }
        else {
            pcb->PC_offset = CPU.offset;
            CPU.offset = 0;
            addToReady(pcb);
        }
    }
    // reset RAM
    resetRAM();
    return 0;
}

/*
Flushes every pcb off the ready queue in the case of a load error
*/
void emptyReadyQueue(){
    while (head!=NULL){
        ReadyQueueNode * temp = head;
        head = head->next;
        free(temp->PCB);
        free(temp);
    }
    sizeOfQueue =0;
}

