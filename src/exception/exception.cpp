#include "exception.h"

Exception::Exception(const char* what_)
    :std::exception()
{
    _what = what_;
}

Exception::~Exception() throw()
{
}

const char* Exception::what() const throw()
{
    return _what.c_str();
}
