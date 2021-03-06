#include "thread/thread.h" 
#include <iostream>


Thread::Thread()
{
    _thread = 0;
    _thread_cfg._arg = NULL;
    _thread_cfg._ret_value = NULL;
}

Thread::Thread(RoutineDelegate d_)
{
    _thread = 0;
    _thread_cfg._d = d_;
    _thread_cfg._arg = NULL;
    _thread_cfg._ret_value = NULL;
}

Thread::Thread(const Thread& thread_)
{
    _thread_cfg._d = thread_._thread_cfg._d;
    _thread_cfg._arg = thread_._thread_cfg._arg;
    _thread_cfg._ret_value = thread_._thread_cfg._ret_value;
    _thread = thread_._thread;
}

Thread::~Thread()
{
    if(_thread) kill();
}

void Thread::setRoutine(RoutineDelegate d_)
{
    _thread_cfg._d = d_;
}

void Thread::setArgument(void* arg_)
{
#ifdef WIN64
#warning cast void* to DWORD
#endif
    _thread_cfg._arg = arg_;
}

bool Thread::start(void* arg_)
{
    setArgument(arg_);
    return start();
}

bool Thread::start()
{
    _thread = CreateThread(NULL, 0, 
                           reinterpret_cast<LPTHREAD_START_ROUTINE>(_threadMain), 
                           reinterpret_cast<void*>(&_thread_cfg),
                           0, NULL);
    return _thread != 0;
}

bool Thread::join()
{
    return WaitForSingleObject(_thread, INFINITE) != static_cast<DWORD>(-1);
}

bool Thread::kill()
{
    return TerminateThread(_thread, 0) != 0;
}

void* Thread::value() const
{
    return _thread_cfg._ret_value;
}

void* Thread::_threadMain(void* cfg_)
{
    ThreadCfg* thread_cfg = reinterpret_cast<ThreadCfg*>(cfg_);
    if(thread_cfg->_d)
        thread_cfg->_ret_value = thread_cfg->_d(thread_cfg->_arg);
    return thread_cfg->_ret_value;
}

