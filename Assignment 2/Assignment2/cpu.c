//
//  cpu.c
//  Assignment2
//
//  Created by OldPineapple on 2020-02-22.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#include "ram.h"
#include "cpu.h"
#include "pcb.h"
#include "interpreter.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

CPU *newCPU;

CPU *init() {
    newCPU = malloc(sizeof(struct CPU));
    newCPU->quanta = 0;
    newCPU->IP = 0;
    newCPU->IR[0] = '\0';
    return newCPU;
}

//int getIP() {
//    int i = newCPU->IP;
//    return i;
//}
//
//void setIP(int i) {
//    newCPU->IP = i;
//}

void run(int quanta) {
    newCPU->quanta = quanta;
    while (newCPU->quanta > 0) {
        if (ram[newCPU->IP] == NULL)
            break;
        char line[333];
        strcpy(line, ram[newCPU->IP]);
        strcpy(newCPU->IR, line);
        interpret(newCPU->IR);
        newCPU->IP ++;
        newCPU->quanta --;
    }
}
