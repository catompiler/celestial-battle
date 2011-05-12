#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <sstream>


class Log
{
public:

    enum Level{
        nothing, information, warning, error
    };

    Log(Level lvl_ = nothing);
    Log(const Log& log_);
    ~Log();

    template <class T> std::ostream& operator << (const T& value);

private:
    std::ostringstream _ostrst;
    Level _lvl;

    void _write_log() const;
    void _write(const std::string& str_) const;
};

template <class T>
std::ostream& Log::operator << (const T& value)
{
    return _ostrst << value;
}

Log log(Log::Level lvl_ = Log::nothing);

#endif	//_LOG_H
