#include "timer/nanosleep.h"
#include "windows_gettime.h"
#include "timer/gettime.h"
#include <windows.h>


bool nanoSleep(size_t secs_, size_t nsecs_)
{
    size_t msecs_rem = secs_ * 1000 + nsecs_ / 1000000;
    size_t usecs_rem = nsecs_ % 1000000 / 1000;
    
    Sleep(msecs_rem);
    for(uint64_t t1 = getTime(); getTime() - t1 < usecs_rem;);
    
    return true;
}
