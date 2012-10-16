#ifndef _TIMER_H_ 
#define _TIMER_H_

#include <stdint.h>
#include <stddef.h>
#include "event/event.h"
#include "delegate/delegate.h"


class Timer{
public:
    
    typedef Event<> OnTimerEvent;
    
    Timer();
    ~Timer();
    
    static uint64_t getTime();
    
    static bool sleep(size_t secs_);
    
    static bool msleep(size_t msecs_);
    static bool msleep(size_t secs_, size_t msecs_);
    
    static bool usleep(size_t usecs_);
    static bool usleep(size_t secs_, size_t usecs_);
    
    static bool nsleep(size_t nsecs_);
    static bool nsleep(size_t secs_, size_t nsecs_);
    
    void start(uint64_t secs);
    void mstart(uint64_t msecs);
    void ustart(uint64_t usecs);
    bool elapsed() const;
    
    
    static bool startTimer(size_t secs_, size_t usecs_);
    static bool stopTimer();
    
    static OnTimerEvent::Base& onTimer(){
        return _onTimer;
    }
    
private:
    uint64_t _endtime;
    static OnTimerEvent _onTimer;
    
    static bool _nanosleep(size_t secs_, size_t nsecs_);
    static void _timer_proc();
};

#endif  //_TIMER_H_
