#include "timer/gettime.h"
#include <stddef.h>

/*
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
 */

#include <windows.h>

uint64_t getTime()
{
    uint64_t res = 0ULL;
    #define EPOCHFILETIME (116444736000000000ULL)
    FILETIME ft;
    LARGE_INTEGER li;
    static LARGE_INTEGER lf = {0};

    if(QueryPerformanceCounter(&li)){
        if(lf.QuadPart == 0ULL){
            QueryPerformanceFrequency(&lf);
            lf.QuadPart /= 1000000;
        }
        if(lf.QuadPart != 0ULL){
            res = li.QuadPart / lf.QuadPart;

            return res;
        }
    }

    GetSystemTimeAsFileTime(&ft);
    res |= ft.dwHighDateTime;
    res <<= 32;
    res |= ft.dwLowDateTime;
    res -= EPOCHFILETIME;
    res /= 10;

    return res;
}
