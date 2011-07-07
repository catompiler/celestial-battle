#ifndef _GNULINUX_THREAD_H_
#define _GNULINUX_THREAD_H_

#include <pthread.h>
#include "delegate/delegate.h"

class Thread{
public:
    typedef UnaryDelegate<void*, void*> ThreadDelegate;

    Thread();
    Thread(ThreadDelegate d_);
    ~Thread();
    
    void setRoutine(ThreadDelegate d_);
    
    bool start(void* arg_);
    bool join();
    bool kill();
    void* value() const;

private:
    
    typedef pthread_t threadid_t;

    struct ThreadCfg{
        ThreadDelegate _d;
        void* _arg;
        void* _ret_value;
    };

    ThreadCfg _thread_cfg;
    threadid_t _thread;

    static void* _threadMain(void* cfg_);

};

#endif  //_GNULINUX_THREAD_H_
