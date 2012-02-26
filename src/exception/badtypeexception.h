#ifndef BADTYPEEXCEPTION_H
#define	BADTYPEEXCEPTION_H

#include "exception.h"

class BadTypeException
    :public Exception {
public:
    BadTypeException(const char* what_);
    ~BadTypeException() throw();
protected:
};

#endif	/* BADTYPEEXCEPTION_H */

