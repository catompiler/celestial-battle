#ifndef NOTFOUNDEXCEPTION_H
#define	NOTFOUNDEXCEPTION_H

#include "exception.h"


class NotFoundException
    :Exception
{
public:
    NotFoundException();
    NotFoundException(const char* what_);
    ~NotFoundException() noexcept;
};

#endif	/* NOTFOUNDEXCEPTION_H */

