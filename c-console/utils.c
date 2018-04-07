#include "utils.h"

void delay(clock_t t)
{
    clock_t start = clock();
    while(clock()-start < t);
}

void pause(const char* msg)
{
    puts(msg);
    system("pause > nul");
}
