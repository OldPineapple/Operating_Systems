#include<stdio.h>
#include<string.h>
/*
Stores the index of the next available block of cell
*/
int nextFree = 0;

/*
Ram structure implemented as an array.
Size is 1000 strings
*/
char *ram[40];

/*
This function will delete the content in ram between the 2 indices parameters (inclusive)
start : pointer to variable which will store the index of first line of file in ram
end : pointer to variable which will store the index of last line of file in ram
*/
void removeFromRam (int pageTable[]){
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 4; j ++) {
            ram[4 * pageTable[i] + j] = NULL;
        }
    }
}
/*
Reset the pointer to the free cell back to index 0
*/
void resetRAM(){
    nextFree = 0;
}


