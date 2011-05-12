#include "log.h"
#include <iostream>
#include <time.h>


std::ofstream Log::_ofst;
std::ostream* Log::_ost = NULL;
bool Log::_echo_to_stdio = true;

Log::Log(Level lvl_)
{
    _lvl = lvl_;
}

Log::Log(const Log& log_)
{
    _ostrst.str(log_._ostrst.str());
    _lvl = log_._lvl;
}

Log::~Log()
{
    _write_log();
}

void Log::_write_log() const
{
    _write_time();
    _write_level();
    _write(_ostrst.str());
}

void Log::_write_time() const
{
    #define TIME_SIZE 32
    char time_str[TIME_SIZE + 1];

    time_t t;
    time(&t);

    int timelen = strftime(time_str, TIME_SIZE, "[%d.%m.%Y %X]", localtime(&t));
    time_str[timelen] = 0x0;
    
    _write(time_str);
}

void Log::_write_level() const
{
    switch(_lvl){
        case Debug:
            _write("(DD) ");
            break;
        case Information:
            _write("(II) ");
            break;
        case Warning:
            _write("(WW) ");
            break;
        case Error:
            _write("(EE) ");
            break;
        default:
            break;
    }
}

void Log::_write(const std::string& str_) const
{
    if(_echo_to_stdio) std::cout << str_;
    if(_ost != NULL) (*_ost) << str_;
    if(_ofst.is_open()) _ofst << str_;
}

void Log::setFile()
{
    if(_ofst.is_open()) _ofst.close();
}

void Log::setFile(const std::string& filename_, bool append_)
{
    if(_ofst.is_open()) _ofst.close();
    _ofst.open(filename_.c_str(), append_ ? std::ios::out | std::ios::app : std::ios::out);
}

void Log::setStream(std::ostream* ost_)
{
    _ost = ost_;
}

void Log::setEchoToStdio(bool echo_to_stdio_)
{
    _echo_to_stdio = echo_to_stdio_;
}



Log log(Log::Level lvl_){
    return Log(lvl_);
}
