#include "timer/settimer.h"
#include <stddef.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>


static void (*timer_proc)() = NULL;


static void sigalarm_handler(int)
{
    if(timer_proc != NULL) timer_proc();
}

static bool setup_handler(bool enable_)
{
    struct sigaction action;

    memset(&action, 0x0, sizeof(struct sigaction));

    sigemptyset(&action.sa_mask);
    if(enable_){
        action.sa_handler = sigalarm_handler;
        action.sa_flags = SA_RESTART;
    }else{
        action.sa_handler = NULL;
        action.sa_flags = SA_RESETHAND;
    }

    return sigaction(SIGALRM,&action,NULL) == 0;
}

static bool setup_timer(size_t interval_secs_, size_t interval_usecs_)
{
    struct itimerval tv;

    int sec = interval_secs_;
    int usec = interval_usecs_;

    tv.it_interval.tv_sec = sec;
    tv.it_interval.tv_usec = usec;
    tv.it_value.tv_sec = sec;
    tv.it_value.tv_usec = usec;

    return setitimer(ITIMER_REAL,&tv,NULL) == 0;
}

bool setTimer(size_t interval_secs_, size_t interval_usecs_, void(*timer_proc_)())
{
    if(timer_proc_ != NULL){
        if(setup_handler(true) && setup_timer(interval_secs_, interval_usecs_)){
            timer_proc = timer_proc_;
            return true;
        }
    }else{
        if(setup_handler(false) && setup_timer(0, 0)){
            timer_proc = timer_proc_;
            return true;
        }
    }
    return false;
}
