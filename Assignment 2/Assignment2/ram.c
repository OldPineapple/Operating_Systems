//
//  ram.c
//  Assignment2
//
//  Created by OldPineapple on 2020-02-22.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#include "ram.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

char *ram[1000];
int count = 0;

void addToRAM (FILE *p, int *start, int *end) {
    *start = count;
    char line[1000];
    while (fgets(line, 999, p) != NULL) {
        ram[count] = strdup(line);
        count++;
    }
    fclose(p);
//    for (int i = 0; i < count; i++) {
//        printf("%s", ram[i]);
//    }
    *end =  count - 1;
}

//int nxtavai() {
//    int i = 0;
//    for (i = 0; i <999; i++) {
//        if (ram[i] == NULL)
//            return i;
//    }
//    return i;
//}

void clearAll() {
    for (int k = 0; k < 999; k++) {
        ram[k] = NULL;
    }
}

void clearPart(int start, int end) {
    for (int k = start; k < end; k++) {
        ram[k] = NULL;
    }
}
