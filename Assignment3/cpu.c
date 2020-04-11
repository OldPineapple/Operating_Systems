#include<string.h>
#include"ram.h"
#include"interpreter.h"
#include"shell.h"

#define DEFAULT_QUANTA 2

struct CPU {
    int IP;
    char IR[1000];
    int quanta;
    int offset;
} CPU;

/*
This method passes a quanta.
It will then executes quanta number of lines in RAM as from the address
pointed by the CPU IP.
Returns an errorCode.
*/
int run(int quanta){
    // If a quanta greater than the default quanta of 2 is passed,
    // run will instead execute only default quanta of lines.
    if (quanta > DEFAULT_QUANTA ){
        quanta = DEFAULT_QUANTA;
    }

    for (int i = 0; i < quanta; i++)
    {
        if (CPU.offset >= 4) {
            return -1;
        }
        int address = CPU.IP + CPU.offset;
        strcpy(CPU.IR,ram[address]);
        if(ram[address] == NULL)
            return 1;
        int errorCode = parse(CPU.IR);
        // Do error checking and if error, return error
        if (errorCode != 0){
            // Display error message if fatal
            if (errorCode < 0){
                ram[CPU.IP][strlen(ram[CPU.IP])-2]='\0';
                displayCode(errorCode,ram[address]);
            }
            return errorCode;
        }
        CPU.offset ++;
    }
    return 0;
}
