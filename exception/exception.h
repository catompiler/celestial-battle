#ifndef _EXCEPTION_H
#define	_EXCEPTION_H

#include <exception>
#include <string>

class Exception:
    public std::exception
{
public:
    Exception(const char* str);
    virtual ~Exception() throw();

    virtual const char* what() const throw();

protected:
    std::string _what;
};

#endif	/* _EXCEPTION_H */

