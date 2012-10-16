#ifndef _WINDOWS_MUTEX_H_
#define _WINDOWS_MUTEX_H_

#include <windows.h>

class Mutex{
public:
    Mutex();
    ~Mutex();

    void lock();
    bool trylock();
    void unlock();
    
private:
    typedef CRITICAL_SECTION mutex_t;
    mutex_t _mutex;
};


#endif  //_WINDOWS_MUTEX_H_
