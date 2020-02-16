//
//  interpreter.c
//  ECSE427_assignment1
//
//  Created by OldPineapple on 2020-01-25.
//  Copyright © 2020 Go through the tunnel. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "shellmemory.h"

int help() {
    printf("help            Displays all the commands\n");
    printf("quit            Exits / terminates the shell with “Bye!”\n");
    printf("set VAR STRING  Assigns a value to shell memory\n");
    printf("print VAR       Displays the STRING assigned to VAR\n");
    printf("run SCRIPT.TXT  Executes the file SCRIPT.TXT\n");
    return 0;
}

int quit() {
    printf("Bye!\n");
    return 1;
}

int set(char *inputs[]) {
    char *input = NULL;
    for (int i = 2; i < 4; i++) {
        if (inputs[i] != NULL) {
            if (i == 2) {
                input = inputs[2];
            }
            else {
                strcat(input, " ");
                strcat(input, inputs[i]);
                inputs[i] = NULL;
            }
        }
        else {
            strcat(input, "\0");
            break;
        }
    }
    //printf("%s", inputs[2]);
    //printf("%s", inputs[3]);
    //printf("%s", inputs[4]);
    //printf("%s", input);
    return writeValue(inputs[1], input);
}


int print(char *inputs[]) {
    char *value = getValue(inputs[1]);
    if(strcmp(value, "Variable does not exist") == 0) {
        return 3;
    }
    else {
        printf("%s\n", value);
        return 0;
    }
        return 0;
}

int run(char *inputs[]) {
    char output[100];
    int length = 99;
    int errorCode = 0;
    char *input = strdup(inputs[1]);
    FILE *f = fopen(input, "r");
    if (f == NULL) {
        return 2;
    }
    
    while (fgets(output, length, f) != NULL) {
        char temp[100];
        int i = 0;
        temp[0] = '\0';
        for (i = 0; output[i] != '\n'; i++) {
            temp[i] = output[i];
        }
        temp[i] = '\0';
        errorCode = parse(temp);
        if (errorCode != 0) {
            fclose(f);
            break;
        }
    }
    fclose(f);
    return errorCode;
}

int interpreter (char *inputs[]) {
    int errorCode = 0;
    //printf("%s", inputs[0]);
    //int i = strcmp(inputs[0], "help");
    //printf("%d", i);
    if(strcmp(inputs[0], "help") == 0) {
        errorCode = help();
    }
    else if (strcmp(inputs[0], "quit") == 0) {
        errorCode = quit();
    }
    else if (strcmp(inputs[0], "set") == 0) {
        errorCode = set(inputs);
    }
    else if (strcmp(inputs[0], "print") == 0) {
        errorCode = print(inputs);
    }
    else if (strcmp(inputs[0], "run") == 0) {
        errorCode = run(inputs);
    }
    else if (strcmp(inputs[0], "") == 0) {
        return 4;
    }
    else {
        printf("Unknown command\n");
        return 4;
    }
    return errorCode;
}
