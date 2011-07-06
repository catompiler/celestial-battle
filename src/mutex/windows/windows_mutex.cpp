#include "mutex/mutex.h" 

Mutex::Mutex()
{
    InitializeCriticalSection(&_mutex);
}

Mutex::~Mutex()
{
    DeleteCriticalSection(&_mutex);
}

void Mutex::lock()
{
    EnterCriticalSection(&_mutex);
}

bool Mutex::trylock()
{
    return TryEnterCriticalSection(&_mutex) != 0;
}

void Mutex::unlock()
{
    LeaveCriticalSection(&_mutex);
}
