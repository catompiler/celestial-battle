#include "object.h"

Object::DestroyEvent::Base& Object::destroyEvent()
{
    return _destroyEvent;
}

Object::~Object()
{
    _destroyEvent(this);
}
