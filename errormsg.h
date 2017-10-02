#ifndef ERRORMSG_H
#define ERRORMSG_H

#undef NDEBUG
#ifndef DEBUG
#   define NDEBUG
#endif //DEBUG

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

//assert
#include <assert.h>

//debug
#undef debug
#ifdef DEBUG
#   define debug(...) do{ \
        fprintf(stderr, "Debug: " __FILE__ ":" T(__LINE__) ": " __VA_ARGS__); \
        fputc('\n',stderr); \
    } while(0)
#else
#   define debug(...) ((void)0)
#endif

//warning
#undef warning
#define warning(...) do{ \
    fprintf(stderr, "Warning: "  __VA_ARGS__); \
    fputc('\n',stderr); \
} while(0)

//fatal
#undef fatal
#define fatal(...) do { \
    fprintf(stderr, "Fatal: " __FILE__ ":" T(__LINE__) ": " __VA_ARGS__); \
    fputc('\n',stderr); \
    abort(); \
} while(0)

#endif //ERRORMSG_H