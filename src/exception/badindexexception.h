#ifndef BADINDEXEXCEPTION_H
#define	BADINDEXEXCEPTION_H

#include "exception.h"

class BadIndexException
    :public Exception {
public:
    BadIndexException(const char* what_);
    ~BadIndexException() throw();
protected:
};

#endif	/* BADINDEXEXCEPTION_H */

