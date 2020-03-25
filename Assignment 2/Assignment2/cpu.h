//
//  cpu.h
//  Assignment2
//
//  Created by OldPineapple on 2020-02-22.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#ifndef cpu_h
#define cpu_h

#include <stdio.h>

typedef struct CPU {int IP; char IR[1000]; int quanta;}CPU;
void run(int quanta);
CPU *init();
int getIP();
void setIP(int i);

#endif /* cpu_h */
