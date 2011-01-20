#include "exception.h"

Exception::Exception(const char* str)
    :std::exception()
{
    _what = str;
}

Exception::~Exception() throw()
{
}

const char* Exception::what() const throw()
{
    return _what.c_str();
}
