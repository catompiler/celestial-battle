#ifndef _WINDOWS_SETTIMER_H_ 
#define _WINDOWS_SETTIMER_H_

#include <stddef.h>

bool setTimer(size_t interval_secs_, size_t interval_usecs_, void(*timer_proc_)());

#endif  //_WINDOWS_SETTIMER_H_
