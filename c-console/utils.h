#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "errormsg.h"

//useful macro

#undef T
#undef _T
#define T(x) _T(x)
#define _T(x) #x

#undef forever
#define forever for(;;)

//useful functions
extern void delay(clock_t t);
extern void pause(const char* msg);

#endif //UTILS_H