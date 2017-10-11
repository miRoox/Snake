#ifndef EASY_TIMER_H
#define EASY_TIMER_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct _Timer;
typedef struct _Timer Timer;

extern Timer* installTimer(clock_t interval);
extern void removeTimer(Timer* timer);
extern bool enabledTimer(const Timer* timer);
extern void setInterval(Timer* timer, clock_t interval);
extern clock_t timerInterval(const Timer* timer);
extern clock_t remainingTime(const Timer* timer);
extern void resetTimer(Timer* timer);
extern bool timeout(Timer* timer);

#endif //EASY_TIMER_H