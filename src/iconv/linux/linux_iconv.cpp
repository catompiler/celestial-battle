#include "iconv.h"
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <locale.h>


int Iconv::_counter = 0;
iconv_t Iconv::_iconv_id_from = reinterpret_cast<iconv_t>(-1);
iconv_t Iconv::_iconv_id_to = reinterpret_cast<iconv_t>(-1);


Iconv::Iconv()
{
    //_iconv_id = reinterpret_cast<iconv_t>(-1);
    
    if(_counter ++ == 0){
        _init();
    }
}

Iconv::~Iconv()
{
    if(_counter){
        if(-- _counter == 0){
            _clean();
        }
    }
}

std::string Iconv::fromLocal(const std::string& str_)
{
    if(_iconv_id_from == reinterpret_cast<iconv_t>(-1)) return std::string();
    return _iconv(_iconv_id_from, str_);
}

std::string Iconv::toLocal(const std::string& str_)
{
    if(_iconv_id_to == reinterpret_cast<iconv_t>(-1)) return std::string();
    return _iconv(_iconv_id_to, str_);
}

std::string Iconv::_iconv(iconv_t iconv_id_, const std::string& str_)
{
    #define BUF_SIZE 64
    size_t buf_size = BUF_SIZE;
    char buf[buf_size + 1]; //buffer
    char* pbuf = buf;

    size_t len = str_.length(); //length
    size_t res = 0; //result of iconv

    std::string res_str; //result string

    char* pstr = const_cast<char*>(str_.c_str()); //pointer to string

    iconv(iconv_id_, NULL, NULL, NULL, NULL);

    do{
        pbuf = buf;
        buf_size = BUF_SIZE;
        memset(buf, 0x0, buf_size + 1);

        res = iconv(iconv_id_,
#ifdef _LIBICONV_VERSION
                //MinGW iconv recieves const char**
                (const char**)
#endif
                &pstr,
                &len, &pbuf, &buf_size);
        //std::cout << (long)res << std::endl;

        if(res == static_cast<size_t>(-1)){
            if(errno != E2BIG) break;
        }

        res_str += buf;
    } while(res == static_cast<size_t>(-1));

    return res_str;
}

void Iconv::_init()
{
    const char* main_codepage = "utf8";
    const char* local_codepage = "";
    
    setlocale(LC_ALL, "");
    
    _iconv_id_from = iconv_open(main_codepage, local_codepage);
    _iconv_id_to = iconv_open(local_codepage, main_codepage);
}

void Iconv::_clean()
{
    if(_iconv_id_from != reinterpret_cast<iconv_t>(-1)) iconv_close(_iconv_id_from);
    if(_iconv_id_to != reinterpret_cast<iconv_t>(-1)) iconv_close(_iconv_id_to);
}
