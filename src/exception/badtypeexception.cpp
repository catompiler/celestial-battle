#include "badtypeexception.h"

BadTypeException::BadTypeException(const char* what_)
    :Exception(what_)
{
}

BadTypeException::~BadTypeException() throw()
{
}

