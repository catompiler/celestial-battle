#include "notfoundexception.h"

NotFoundException::NotFoundException()
    :Exception()
{
}

NotFoundException::NotFoundException(const char* what_)
    :Exception(what_)
{
}

NotFoundException::~NotFoundException() noexcept
{
}

