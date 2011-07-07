#include "thread/thread.h" 

Thread::Thread(ThreadDelegate d_)
{
    _thread_cfg._d = d_;
    _thread_cfg._arg = NULL;
    _thread_cfg._ret_value = NULL;
}

Thread::~Thread()
{
    if(_thread) kill();
}

bool Thread::start(void* arg_)
{
    _thread = CreateChread(NULL, 0, 
                           reinterpret_cast<void* (*)(void*)>(_threadMain), 
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

