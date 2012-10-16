#include "timer/gettime.h"
#include <stddef.h>
#include <sys/time.h>

uint64_t getTime()
{
    uint64_t res;
    struct timeval tv;
    
    //get time
    gettimeofday(&tv, NULL);
    res = tv.tv_sec * 1000000 + tv.tv_usec;
    
    return res;
}
