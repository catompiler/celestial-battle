#ifndef _EXCEPTION_H
#define	_EXCEPTION_H

#include <exception>
#include <string>

class Exception:
    public std::exception
{
public:
    Exception();
    Exception(const char* what_);
    virtual ~Exception() noexcept;

    virtual const char* what() const noexcept;

protected:
    std::string _what;
};

#endif	/* _EXCEPTION_H */

