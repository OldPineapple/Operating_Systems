//
//  shellmemory.h
//  ECSE427_assignment1
//
//  Created by OldPineapple on 2020-01-25.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#ifndef shellmemory_h
#define shellmemory_h

struct MEM{
    char *var;
    char *value;
};

int clearMem (void);
int writeValue (char *words, char *content);
char *getValue (char *words);

#endif /* shellmemory_h */
