#include "timer.h" 
#include "gettime.h"
#include "nanosleep.h"
#include "settimer.h"



Timer::OnTimerEvent Timer::_onTimer;


Timer::Timer()
{
    _endtime = 0ULL;
}

Timer::~Timer()
{
}

uint64_t Timer::getTime()
{
    return ::getTime();
}

bool Timer::sleep(size_t secs_)
{
    return _nanosleep(secs_, 0);
}

bool Timer::msleep(size_t msecs_)
{
    return _nanosleep(0, msecs_ * 1000000);
}

bool Timer::msleep(size_t secs_, size_t msecs_)
{
    return _nanosleep(secs_, msecs_ * 1000000);
}

bool Timer::usleep(size_t usecs_)
{
    return _nanosleep(0, usecs_ * 1000);
}

bool Timer::usleep(size_t secs_, size_t usecs_)
{
    return _nanosleep(secs_, usecs_ * 1000);
}

bool Timer::nsleep(size_t nsecs_)
{
    return _nanosleep(0, nsecs_);
}

bool Timer::nsleep(size_t secs_, size_t nsecs_)
{
    return _nanosleep(secs_, nsecs_);
}

void Timer::start(uint64_t secs)
{
    _endtime = getTime() + secs * 1000000;
}

void Timer::mstart(uint64_t msecs)
{
    _endtime = getTime() + msecs * 1000;
}
void Timer::ustart(uint64_t usecs)
{
    _endtime = getTime() + usecs;
}

bool Timer::elapsed() const
{
    return getTime() >= _endtime;
}

bool Timer::startTimer(size_t secs_, size_t usecs_)
{
    return ::setTimer(secs_, usecs_, _timer_proc);
}

bool Timer::stopTimer()
{
    return ::setTimer(0, 0, NULL);
}

bool Timer::_nanosleep(size_t secs_, size_t nsecs_)
{
    size_t secs = 0;
    size_t nsecs = 0;
    
    secs = secs_;
    nsecs = nsecs_;
    
    if(nsecs >= 1000000000){
        secs += nsecs / 1000000000;
        nsecs %= 1000000000;
    }
    
    return nanoSleep(secs, nsecs);
}

void Timer::_timer_proc()
{
    _onTimer();
}
