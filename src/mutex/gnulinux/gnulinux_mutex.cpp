#include "mutex/mutex.h" 

Mutex::Mutex()
{
    pthread_mutex_init(&_mutex,NULL);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&_mutex);
}

void Mutex::lock()
{
    pthread_mutex_lock(&_mutex);
}

bool Mutex::trylock()
{
    return pthread_mutex_trylock(&_mutex) == 0;
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&_mutex);
}
