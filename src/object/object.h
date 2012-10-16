#ifndef _OBJECT_H
#define _OBJECT_H

#include "delegate/delegate.h"
#include "event/event.h"


class Object;

class ObjectEvent
{
public:
    ObjectEvent(Object* object_);
    virtual ~ObjectEvent();

    Object* object() const;

protected:
    Object* _object;
};

class Object
{
public:
    typedef ObjectEvent DestroyEvent;
    typedef UnaryEvent<DestroyEvent*> OnDestroyEvent;

    OnDestroyEvent::Base& onDestroy();

    virtual ~Object();

protected:
    OnDestroyEvent _onDestroy;
};

#endif	//_OBJECT_H
