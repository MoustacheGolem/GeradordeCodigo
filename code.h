#include <stdbool.h> 
#include <string.h>

int ac = 111; // accumulator. general-purpose register
int mp = 222; // maxaddress. used to store the maximum address in memory. for checking that memory addresses are valid and for preventing segmentation faults
int gp = 333;
bool tracecode = true;

