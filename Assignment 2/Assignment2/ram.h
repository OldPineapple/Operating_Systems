//
//  ram.h
//  Assignment2
//
//  Created by OldPineapple on 2020-02-22.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#ifndef ram_h
#define ram_h

#include <stdio.h>
char *ram[1000];
void addToRAM (FILE *p, int *start, int *end);
void clearPart(int start, int end);
int nxtavai();
void clearAll();

#endif /* ram_h */
