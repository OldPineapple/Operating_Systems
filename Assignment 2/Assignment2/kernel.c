//
//  kernel.c
//  Assignment2
//
//  Created by OldPineapple on 2020-02-22.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#include "kernel.h"
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

struct ReadyQueue{
    struct PCB *pcb;
    struct ReadyQueue *next;
};

struct ReadyQueue *head = NULL;
struct ReadyQueue *tail = NULL;

void addToReady(struct PCB *pcb) {
    struct ReadyQueue *newRQ = malloc(sizeof(struct ReadyQueue));
    newRQ->pcb = pcb;
    newRQ->next = NULL;
    if(head == NULL) {
        head = newRQ;
        tail = newRQ;
    }
    else {
        tail->next = newRQ;
        tail = newRQ;
    }
}

void myinit(char *filename) {
    int start = 0; int end = 999;
    FILE *p = fopen(filename, "r");
    addToRAM(p, &start, &end);
    struct PCB *pcb = makePCB(start, end);
    addToReady(pcb);
    fclose(p);
}

void removePCB() {
    if(head == tail) {
        head = NULL;
        tail = NULL;
    }
    else {
        head = head->next;
    }
}

//void scheduler() {
//    CPU *newCPU = init();
//    int quanta = 2;
//    struct PCB *pcb = malloc(sizeof(struct PCB));
//        while (1) {
//            pcb = head->pcb;
//            int i = pcb->PC;
//            newCPU->IP = i;
//            run(quanta);
//            pcb->PC = pcb->PC + quanta;
//            if (newCPU->IP <= pcb->end) {
//                head->pcb = pcb;
//                if (head->next == NULL){
//
//                } else {
//                    tail->next = head;
//                    tail = tail->next;
//                    tail->next = NULL;
//                    head = head->next;
//                }
//            }
//            else {
//                removePCB();
//                clearPart(start, end);
//            }
//            if(tail == NULL)
//                break;
//        }
//    free(pcb);
//}

void scheduler() {
    int quanta = 2;
    CPU *newCPU = init();
    struct PCB *pcb = malloc(sizeof(struct PCB));
    while (1) {
        pcb = head->pcb;
        newCPU->IP = pcb->PC;
        run(quanta);
        head->pcb->PC = pcb->PC + 2;
        if(pcb->end < newCPU->IP) {
            clearPart(pcb->start, pcb->end);
            head = head->next;
            //free(pcb);
        }
        else if(head->next == NULL);
        else{
            tail->next = head;
            tail = tail->next;
            tail->next = NULL;
            head = head->next;
        }
        if(head == NULL)
            break;
    }
}


int main(int argc, const char *argv[]) {
    init();
    clearAll();
    shellUI();
    return 0;
}
