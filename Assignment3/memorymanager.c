#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cpu.h"
#include "ram.h"
#include "kernel.h"


int countTotalPages (FILE *f) {
    fseek(f, 0, SEEK_SET);
    int count = 0;
    char c;
    for (c = getc(f); c != EOF; c = getc(f))
    {
        if (c == '\n')
            count = count + 1;
    }
    int number = 0;
    if (count % 4 == 0) {
        number = count / 4;
    }
    else
        number = count / 4 + 1;
    return number;
}

void loadPage (int pageNumber, FILE *f, int frameNumber) {
    fseek(f, 0, SEEK_SET);
    int i = frameNumber;
    int j = 0;
    int pageIndex = pageNumber * 4;
    int count = 0;
    char buffer[1000];
    while(fgets(buffer,999,f) != NULL && count < 40) {
        if (count == pageIndex) {
            ram[4 * i + j]= strdup(buffer); // store a page into a frame in RAM
            j++;
            if (j == 4)
                break;
        }
        else
            count++;
    }
}

int findFrame() {
    int i;
    for(i = 0; i < 10; i ++) {
        if (ram[4 * i] == NULL)
            return i;
    }
    return -1;
}

int findVictim(PCB *p) {
    int r = rand() % 10; // frame number
    int i;
    int length = 0;
    for(i = 0; i < 10; i ++) {
        if (r != p->pageTable[i]) {
            length += 1;
            if (length == 10) {
                return r;
            }
        } // not in page table
        else {
            while(1) {
                i = 0;
                length = 0;
                r = (r + 1) % 10;
                for (i = 0; i < 10; i ++) {
                    if (r != p->pageTable[i]) {
                        length += 1;
                        if (length == 10) {
                            return r;
                        }
                    }
                    else
                        continue;
                }
            }
        }
    }
    return r;
}

int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame) {
    if (frameNumber == -1) {
        p->pageTable[pageNumber] = victimFrame;
    }
    else
        p->pageTable[pageNumber] = frameNumber;
    return 0;
}

int updateVictimTable(int victim) {
    struct ReadyQueueNode *head = getHead();
    while(head != NULL) {
        PCB *p = head->PCB;
        for (int i = 0; i < sizeof(p->pageTable); i ++) {
            if (p->pageTable[i] == victim) {
                p->pageTable[i] = 0;
                return i;
            }
        }
        head = head->next;
    }
    return -1;
}

int pageFault(PCB *p) {
    int next = p->PC_page + 1;
    if(next > p->pages_max) {
        return 0;
    }
    if (p->pageTable[next] != 0) {
        int frameNumber = p->pageTable[next];
        CPU.IP = frameNumber * 4;
    }
    else {
        FILE *fp = p->p;
        int frame = findFrame();
        int victim = findVictim(p);
        if (frame == -1) {
            updateVictimTable(victim);
        }
        int page = updatePageTable(p, next, frame, victim);
        loadPage(next, fp, frame);
        CPU.IP = page * 4;
    }
    p->PC_page++;
    p->PC_offset = 0;
    p->PC = p->PC_page * 4;
    return 1;
}


int launcher (FILE *p, char *filename) {
    int output;
    char command[50] = "cp ";
    // Copy the entire file into the backing store.
    strcat(command, filename);
    strcat(command, " ./BackingStore");
    //printf("command: %s\n", command);
    system(command);
    // Close the file pointer pointing to the original file.
    fclose(p);
    // Open the file in the backing store.
    char path[40] = "./BackingStore/";
    strcat(path, filename);
    //printf("path: %s\n", path);
    output = myinit(path);
    //printf("errorcode: %d\n", output);
    if (output != 0)
        return 0;
    return 1;
}
