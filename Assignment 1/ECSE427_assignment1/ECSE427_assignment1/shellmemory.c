//
//  shellmemory.c
//  ECSE427_assignment1
//
//  Created by OldPineapple on 2020-01-25.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"

struct MEM *mem[1000];
int length = 0;

int clearMem () {
    for (int i = 0; i < 999; i++) {
        mem[i] = NULL;
    }
    return 0;
}

int find (char *vari) {
    for (int i = 0; i < 999; i++) {
        if(mem[i] == NULL || strcmp(mem[i]->var, vari) == 0) {
            return i;
        }
    }
    return 0;
}

int writeValue (char *vari, char *value) {
    int i = find(vari);
    if (mem[i] == NULL) {
        struct MEM *newMem = (struct MEM *)malloc(sizeof(struct MEM));
        newMem->var = strdup(vari);
        newMem->value = strdup(value);
        mem[i] = newMem;
    }
    else {
        struct MEM *oldMem = mem[i];
        oldMem->value = strdup("\0");
        oldMem->value = strdup(value);
    }
    return 0;
}

char *getValue (char *vari) {
    char *error = NULL;
    int i = find(vari);
    if(mem[i] != NULL) {
        struct MEM *oldMem = mem[i];
        error = strdup(oldMem->value);
    }
    else {
        error = "Variable does not exist";
    }
    return error;
}
