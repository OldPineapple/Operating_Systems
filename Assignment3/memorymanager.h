#include <stdio.h>
int countTotalPages (FILE *f);

void loadPage (int pageNumber, FILE *f, int frameNumber);

int findFrame();

int findVictim(PCB *p);

int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame);

int updateVictimTable(int victim);

int pageFault(PCB *p);

int launcher (FILE *p, char *filename);
