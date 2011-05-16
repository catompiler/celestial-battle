#include "object.h"



ObjectEvent::ObjectEvent(Object* object_)
    :_object(object_)
{
}

ObjectEvent::~ObjectEvent()
{
}

Object* ObjectEvent::object() const
{
    return _object;
}



Object::OnDestroyEvent::Base& Object::onDestroy()
{
    return _onDestroy;
}

Object::~Object()
{
    DestroyEvent e(this);
    _onDestroy(&e);
}
