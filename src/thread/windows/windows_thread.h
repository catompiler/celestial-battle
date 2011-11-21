#ifndef _WINDOWS_THREAD_H_
#define _WINDOWS_THREAD_H_

#include <windows.h>
#include "delegate/delegate.h"

class Thread{
public:
    typedef UnaryDelegate<void*, void*> RoutineDelegate;

    Thread();
    Thread(RoutineDelegate d_);
    ~Thread();
    
    void setRoutine(RoutineDelegate d_);
    
    bool start(void* arg_);
    bool join();
    bool kill();
    void* value() const;

private:
    
    typedef HANDLE threadid_t;

    struct ThreadCfg{
        RoutineDelegate _d;
        void* _arg;
        void* _ret_value;
    };

    ThreadCfg _thread_cfg;
    threadid_t _thread;

    static void* _threadMain(void* cfg_);

};


#endif  //_WINDOWS_THREAD_H_
