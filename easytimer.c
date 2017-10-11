#include "easytimer.h"

struct _Timer
{
    clock_t interval; //0 means disabled
    clock_t start;
};

#define MaxTimersCount 4

static Timer timers[MaxTimersCount];

Timer* installTimer(clock_t interval)
{
    Timer* timer = NULL;
    if(interval)
    {
        for(unsigned int i=0;i<MaxTimersCount;++i)
        {
            if(timers[i].interval == 0)
            {
                timer = &timers[i];
                timer->interval = interval;
                timer->start = clock();
                break;
            }
        }
    }
    return timer;
}

void removeTimer(Timer* timer)
{
    timer->interval = 0;
    timer->start = 0;
}

bool enabledTimer(const Timer* timer)
{
    if(timer==NULL) return false;
    else return timer->interval !=0 ;
}

void setInterval(Timer* timer, clock_t interval)
{
    if(enabledTimer(timer) && interval)
    {
        timer->interval = interval;
    }
}

clock_t timerInterval(const Timer* timer)
{
    return timer->interval;
}

clock_t remainingTime(const Timer* timer)
{
    clock_t current = clock();
    if(enabledTimer(timer) && current-timer->start < timer->interval)
    {
        return timer->interval + timer->start - current;
    }
    else
    {
        return 0;
    }
}

void resetTimer(Timer* timer)
{
    if(enabledTimer(timer))
    {
        timer->start = clock();
    }
}

bool timeout(Timer* timer)
{
    if(enabledTimer(timer) && clock()-timer->start >= timer->interval)
    {
        timer->start = clock();
        return true;
    }
    else
    {
        return false;
    }
}
