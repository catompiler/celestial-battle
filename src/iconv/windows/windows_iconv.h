#ifndef _WINDOWS_ICONV_H_
#define _WINDOWS_ICONV_H_

//MinGW's iconv release not work (
//#include <iconv.h>
#include <string>



class Iconv
{
public:
    static std::string fromLocal(const std::string& str_);
    static std::string toLocal(const std::string& str_);
};

#endif  //_WINDOWS_ICONV_H_
