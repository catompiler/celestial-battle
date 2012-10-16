#ifndef _UTF8CHAR_H_
#define _UTF8CHAR_H_

#include <stddef.h>
#include <string>

class Utf8Char{
public:
    Utf8Char();
    explicit Utf8Char(const char* c_);
    explicit Utf8Char(unsigned int c_);
    Utf8Char(const Utf8Char& c_);
    ~Utf8Char();
    
    std::string toSrting() const;
    unsigned int toUInt() const;
    
    Utf8Char& operator=(const Utf8Char& c_);
    bool operator==(const Utf8Char& c_) const;
    bool operator<(const Utf8Char& c_) const;
    
    static size_t size(unsigned int c_);
    static size_t size(const char* c_);
    
    static unsigned int decode(const char* c_);
    static size_t encode(char* out_c_, unsigned int c_);
    static bool validate(const char* c_);
    
private:
    unsigned int _c;
};

#endif  //_UTF8CHAR_H_
