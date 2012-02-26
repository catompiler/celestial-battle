#include "badindexexception.h"

BadIndexException::BadIndexException(const char* what_)
    :Exception(what_)
{
}

BadIndexException::~BadIndexException() throw()
{
}

