#ifndef _LOG_H
#define _LOG_H

#include <iostream>
#include <sstream>
#include <fstream>

class Log
{
public:

    enum Level{
        Normal, Debug, Information, Warning, Error
    };

    Log(Level lvl_ = Normal);
    Log(const Log& log_);
    ~Log();

    template <class T> std::ostream& operator << (const T& value);
    
    static void setFile();
    static void setFile(const std::string& filename_, bool append_ = false);
    static void setStream(std::ostream* ost_ = NULL);
    
    static void setEchoToStdio(bool echo_to_stdio_ = false);

private:
    static std::ofstream _ofst;
    static std::ostream* _ost;
    static bool _echo_to_stdio;

    std::ostringstream _ostrst;
    Level _lvl;

    void _write_log() const;
    void _write_time() const;
    void _write_level() const;
    void _write(const std::string& str_) const;
};

template <class T>
std::ostream& Log::operator << (const T& value)
{
    return _ostrst << value;
}

Log log(Log::Level lvl_ = Log::Normal);

#endif	//_LOG_H
