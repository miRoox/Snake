#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "errormsg.h"

//useful macro
#undef T
#undef _T
#define T(x) _T(x)
#define _T(x) #x

#endif //UTILS_H