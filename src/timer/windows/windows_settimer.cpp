#include "timer/settimer.h"
#include <stddef.h>
#include <windows.h>


static void (*timer_proc)() = NULL;
static unsigned int timer_id = 0;


static void timer_handler(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
    if(timer_proc != NULL) timer_proc();
}

bool setTimer(size_t interval_secs_, size_t interval_usecs_, void(*timer_proc_)())
{
    if(timer_proc_ != NULL){
        unsigned int timer_interval = interval_secs_ * 1000 + interval_usecs_ / 1000;
        unsigned int res = SetTimer(NULL, timer_id, timer_interval,
                            reinterpret_cast<TIMERPROC>(timer_handler));
        if(res != 0){
            timer_proc = timer_proc_;
            timer_id = res;
            return true;
        }
    }else{
        if(KillTimer(NULL, timer_id)){
            timer_proc = timer_proc_;
            timer_id = 0;
            return true;
        }
    }
    return false;
}

