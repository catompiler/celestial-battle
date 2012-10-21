#include "exception.h"



Exception::Exception()
    :std::exception()
{
}

Exception::Exception(const char* what_)
    :std::exception()
{
    _what = what_;
}

Exception::~Exception() noexcept
{
}

const char* Exception::what() const noexcept
{
    return _what.c_str();
}
