#ifndef _GNULINUX_THREAD_H_
#define _GNULINUX_THREAD_H_

#include <pthread.h>
#include "delegate/delegate.h"

class Thread{
public:
    typedef UnaryDelegate<void*, void*> RoutineDelegate;

    Thread();
    Thread(RoutineDelegate d_);
    Thread(const Thread& thread_);
    ~Thread();
    
    void setRoutine(RoutineDelegate d_);
    void setArgument(void* arg_);
    
    bool start(void* arg_);
    bool start();
    bool join();
    bool kill();
    void* value() const;

private:
    
    typedef pthread_t threadid_t;

    struct ThreadCfg{
        RoutineDelegate _d;
        void* _arg;
        void* _ret_value;
    };

    ThreadCfg _thread_cfg;
    threadid_t _thread;

    static void* _threadMain(void* cfg_);

};

#endif  //_GNULINUX_THREAD_H_
