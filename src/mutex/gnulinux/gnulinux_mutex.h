#ifndef _GNULINUX_MUTEX_H_
#define _GNULINUX_MUTEX_H_

#include <pthread.h>

class Mutex{
public:
    Mutex();
    ~Mutex();

    void lock();
    bool trylock();
    void unlock();
    
private:
    typedef pthread_mutex_t mutex_t;
    mutex_t _mutex;
};

#endif  //_GNULINUX_MUTEX_H_
