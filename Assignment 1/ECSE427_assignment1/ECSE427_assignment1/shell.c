#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"

int parse(char ui[]) {
    char tmp[200];
    char *words[100];
    int a,b;
    int w = 0;
    
    for (a = 0; ui[a] == ' ' && a < 1000; a++);         // skip first white spaces
    
    while (ui[a] != '\0' && a < 1000) {         // read input
        for(b = 0; ui[a] != '\0' && ui[a] != ' ' && ui[a] != '\n' && a < 1000; a++, b++) {
            tmp[b] = ui[a];         // extract word
        }
        tmp[b] = '\0';          // now b is the last digit in a word and needs \0 to end it
        words[w] = strdup(tmp);
        a++;            // skip the space
        w++;            // move to store next input word
    }
    //printf("%s", words[0]);
    return interpreter(words);
}

int main (int argc, char *argv[]) {
    printf("Welcome to the Hanwen shell!\n");
    printf("Version 1.0 Created January 2020\n");
    char prompt[1000] = {'$', '\0'};
    char command[1000];
    int errorCode = clearMem();
    
    while (1) {
        printf("%s", prompt);
        fgets(command, 999, stdin);
        errorCode = parse(command);
        if (errorCode == 0) {
            continue;
        }
        else if (errorCode == 1) {
            exit(99);
        }
        else if (errorCode == 2) {
            printf("Script not found\n");
            continue;
        }
        else if (errorCode == 3) {
            printf("Variable does not exist\n");
            continue;
        }
        else if (errorCode == 4) {
            continue;
        }
    }
    return 0;
}
