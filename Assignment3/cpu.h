#define DEFAULT_QUANTA 2

struct CPU {
    int IP;
    char IR[1000];
    int quanta;
    int offset;
} extern CPU;

int run(int);
