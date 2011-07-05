#include "utf8char.h"



Utf8Char::Utf8Char()
{
    _c = 0x0;
}

Utf8Char::Utf8Char(const char* c_)
{
    _c = decode(c_);
}

Utf8Char::Utf8Char(unsigned int c_)
{
    _c = c_;
}

Utf8Char::Utf8Char(const Utf8Char& c_)
{
    _c = c_._c;
}

Utf8Char::~Utf8Char()
{
}

std::string Utf8Char::toSrting() const
{
    #define CHAR_BUF_SIZE 5
    char buf[CHAR_BUF_SIZE];
    
    size_t s = encode(buf, _c);
    buf[s] = 0x0;
    
    return std::string(buf);
}

unsigned int Utf8Char::toUInt() const
{
    return _c;
}

Utf8Char& Utf8Char::operator=(const Utf8Char& c_)
{
    _c = c_._c;
}

bool Utf8Char::operator==(const Utf8Char& c_) const
{
    return _c == c_._c;
}

bool Utf8Char::operator<(const Utf8Char& c_) const
{
    return _c < c_._c;
}

size_t Utf8Char::size(const char* c_)
{
    size_t res = 0;
    unsigned char _c = c_[0];
    
    while(_c & 0x80){
        res ++;
        _c <<= 0x1;
    }
    
    return res == 0 ? 1 : res;
}

size_t Utf8Char::size(unsigned int c_)
{
    if(c_ > 0x001fffff) return 0;
    
    if(c_ >= 0x00010000) return 4;
    if(c_ >= 0x00000800) return 3;
    if(c_ >= 0x00000080) return 2;
    
    return 1;
}
/*
   0000 0000-0000 007F   0xxxxxxx
   0000 0080-0000 07FF   110xxxxx 10xxxxxx
   0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
   0001 0000-001F FFFF   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 */
unsigned int Utf8Char::decode(const char* c_)
{
    unsigned int res = 0;
    size_t s = size(c_);

    switch(s){
        case 1:
        default:
            res=static_cast<unsigned int>(*c_);
            break;
        case 2:
            res = (res | (c_[0] & 0x1f)) << 6;
            res = (res | (c_[1] & 0x3f));
            break;
        case 3:
            res = (res | (c_[0] & 0xf )) << 6;
            res = (res | (c_[1] & 0x3f)) << 6;
            res = (res | (c_[2] & 0x3f));
            break;
        case 4:
            res = (res | (c_[0] & 0x7 )) << 6;
            res = (res | (c_[1] & 0x3f)) << 6;
            res = (res | (c_[2] & 0x3f)) << 6;
            res = (res | (c_[3] & 0x3f));
            break;
    }
    
    return res;
}

size_t Utf8Char::encode(char* out_c_, unsigned int c_)
{
    size_t s = size(c_);
    
    switch(s){
        case 1:
        default:
            *out_c_ = static_cast<char>(c_);
            break;
        case 2://0x1f 0x3f <<6
            out_c_[0] = static_cast<char>(((c_ >> 6 )         | 0xc0));
            out_c_[1] = static_cast<char>(((c_      ) & 0x3f) | 0x80);
            break;
        case 3://0xf
            out_c_[0] = static_cast<char>(((c_ >> 12)         | 0xe0));
            out_c_[1] = static_cast<char>(((c_ >> 6 ) & 0x3f) | 0x80);
            out_c_[2] = static_cast<char>(((c_      ) & 0x3f) | 0x80);
            break;
        case 4://0x7
            out_c_[0] = static_cast<char>(((c_ >> 18)         | 0xf0));
            out_c_[1] = static_cast<char>(((c_ >> 12) & 0x3f) | 0x80);
            out_c_[2] = static_cast<char>(((c_ >> 6 ) & 0x3f) | 0x80);
            out_c_[3] = static_cast<char>(((c_      ) & 0x3f) | 0x80);
            break;
    }
    
    return s;
}

bool Utf8Char::validate(const char* c_)
{
    size_t s = size(c_);
    
    if(s > 4) return false;
    
    switch(s){
        case 1:
            if(c_[0] & 0x80) return false;
            break;
        case 2:
            if((c_[0] & 0xe0) != 0xc0) return false;
            if((c_[1] & 0xc0) != 0x80) return false;
            break;
        case 3:
            if((c_[0] & 0xf0) != 0xe0) return false;
            if((c_[1] & 0xc0) != 0x80) return false;
            if((c_[2] & 0xc0) != 0x80) return false;
            break;
        case 4:
            if((c_[0] & 0xf8) != 0xf0) return false;
            if((c_[1] & 0xc0) != 0x80) return false;
            if((c_[2] & 0xc0) != 0x80) return false;
            if((c_[3] & 0xc0) != 0x80) return false;
            break;
        default:
            return false;
    }
    
    return true;
}
