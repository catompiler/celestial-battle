#include "log.h"
#include <iostream>

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
    switch(_lvl){
        case information:
            _write("(II) ");
            break;
        case warning:
            _write("(WW) ");
            break;
        case error:
            _write("(EE) ");
            break;
        default:
            break;
    }
    _write(_ostrst.str());
}

void Log::_write(const std::string& str_) const
{
    std::cout <<str_;
}



Log log(Log::Level lvl_){
    return Log(lvl_);
}
