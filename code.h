#include <stdbool.h> 
#include <string.h>

int ac = 111; // accumulator. general-purpose register
int mp = 222; // maxaddress. used to store the maximum address in memory. for checking that memory addresses are valid and for preventing segmentation faults
int gp = 333; // global pointer
int tmp = 444;
bool tracecode = true;

void emitRO( char *op, int r, int s, int t, char *c);
void emitRM( char * op, int r, int d, int s, char *c);

int recuperaLocMemId(char *nomeSimb);
int constaTabSimb(char *nomeSimb);

