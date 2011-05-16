#ifndef _OBJECT_H
#define _OBJECT_H

#include "delegate/delegate.h"
#include "event/event.h"

class Object
{
public:
    typedef UnaryEvent<Object*> DestroyEvent;

    DestroyEvent::Base& destroyEvent();

    virtual ~Object();

protected:
    DestroyEvent _destroyEvent;
};

#endif	//_OBJECT_H
