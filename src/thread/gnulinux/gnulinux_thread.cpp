#include "thread/thread.h" 



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
    _thread_cfg._arg = arg_;
}

bool Thread::start(void* arg_)
{
    setArgument(arg_);
    return start();
}

bool Thread::start()
{
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_create(&_thread, &attr,
                   reinterpret_cast<void* (*)(void*)>(_threadMain),
                   reinterpret_cast<void*>(&_thread_cfg));
    
    pthread_attr_destroy(&attr);
    
    return _thread != 0;
}

bool Thread::join()
{
    return pthread_join(_thread, NULL) == 0;
}

bool Thread::kill()
{
    return pthread_cancel(_thread) == 0;
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

