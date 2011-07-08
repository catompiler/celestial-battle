#include "timer/nanosleep.h"
#include <time.h>
#include <errno.h>


bool nanoSleep(size_t secs_, size_t nsecs_)
{
    struct timespec ts_req, ts_rem;
    ts_req.tv_sec = secs_;
    ts_req.tv_nsec = nsecs_;
    ts_rem.tv_sec = 0;
    ts_rem.tv_nsec = 0;
    
    while(nanosleep(&ts_req, &ts_rem) == -1){
        if(errno == EINTR){
            ts_req.tv_sec = ts_rem.tv_sec;
            ts_req.tv_nsec = ts_rem.tv_nsec;
            ts_rem.tv_sec = 0;
            ts_rem.tv_nsec = 0;
        }else{
            return false;
        }
    }
    
    return true;
}
