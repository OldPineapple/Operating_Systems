//
//  pcb.c
//  Assignment2
//
//  Created by OldPineapple on 2020-02-22.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#include "pcb.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

struct PCB *makePCB(int start, int end) {
    struct PCB *newPCB = malloc(sizeof(struct PCB));
    newPCB->PC = start;
    newPCB->start = start;
    newPCB->end = end;
    return newPCB;
}
