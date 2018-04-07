#include "easytimer.h"

struct _Timer
{
    struct
    {
        bool enabled : 1;
        bool stopped : 1;
    };
    clock_t interval;
    clock_t start;
    clock_t stop;
};

#define MaxTimersCount 4

static Timer timers[MaxTimersCount] = {0};

Timer* installTimer(clock_t interval)
{
    Timer* timer = NULL;
    if(interval)
    {
        for(unsigned int i=0;i<MaxTimersCount;++i)
        {
            if(!timers[i].enabled)
            {
                timer = &timers[i];
                timer->interval = interval<0 ? 0 : interval;
                timer->enabled = true;
                timer->stopped = true;
                timer->stop = 0;
                timer->start = clock();
                break;
            }
        }
    }
    return timer;
}

void removeTimer(Timer* timer)
{
    timer->enabled = false;
    timer->stopped = true;
    timer->interval = 0;
    timer->start = 0;
    timer->stop = 0;
}

void startTimer(Timer* timer)
{
    if(enabledTimer(timer) && timer->stopped)
    {
        timer->stopped = false;
        timer->start = clock() + timer->stop;
    }
}

bool stopTimer(Timer* timer)
{
    bool stopped = false;
    if(timer->stopped)
    {
        stopped = true;
    }
    else if(enabledTimer(timer))
    {
        clock_t current = clock();
        timer->stop = current-timer->start < timer->interval
                     ? current - timer->start
                     : timer->interval;
        timer->stopped = stopped = true;
    }
    return stopped;
}

void resetTimer(Timer* timer)
{
    if(enabledTimer(timer))
    {
        timer->stop = 0;
        timer->start = clock();
    }
}

bool enabledTimer(const Timer* timer)
{
    if(timer==NULL) return false;
    else return timer->enabled;
}

bool stoppedTimer(const Timer* timer)
{
    if(enabledTimer(timer)) return timer->stopped;
    else return false;
}

void setInterval(Timer* timer, clock_t interval)
{
    if(enabledTimer(timer))
    {
        timer->interval = interval<0 ? 0 : interval;
    }
}

clock_t timerInterval(const Timer* timer)
{
    if(enabledTimer(timer)) return timer->interval;
    else return InvalidClockTime;
}

clock_t remainingTime(const Timer* timer)
{
    if(enabledTimer(timer))
    {
        if(timer->stopped)
        {
            return timer->interval - timer->stop;
        }
        else
        {
            clock_t current = clock();
            return current-timer->start < timer->interval
                  ? timer->interval + timer->start - current
                  : 0;
        }
    }
    else
    {
        return InvalidClockTime;
    }
}

bool timeout(Timer* timer)
{
    if(enabledTimer(timer)
      && !timer->stopped
      && clock()-timer->start >= timer->interval)
    {
        timer->start = clock();
        return true;
    }
    else
    {
        return false;
    }
}
