//
//  pcb.h
//  Assignment2
//
//  Created by OldPineapple on 2020-02-22.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#ifndef pcb_h
#define pcb_h

#include <stdio.h>

struct PCB {int PC; int start; int end;};

struct PCB *makePCB(int start, int end);

#endif /* pcb_h */
