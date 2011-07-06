#ifndef _LINUX_ICONV_H_
#define _LINUX_ICONV_H_

#include <iconv.h>
#include <string>



class Iconv
{
public:
    Iconv();
    ~Iconv();
    
    static std::string fromLocal(const std::string& str_);
    static std::string toLocal(const std::string& str_);
    
private:
    static int _counter;
    static iconv_t _iconv_id_from;
    static iconv_t _iconv_id_to;
    
    static std::string _iconv(iconv_t iconv_id_, const std::string& str_);
    
    void _init();
    void _clean();
    
    //iconv_t _iconv_id;
};

static Iconv __init_iconv;

#endif  //_ICONV_ICONV_H_
