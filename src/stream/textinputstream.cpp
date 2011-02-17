#include "textinputstream.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <float.h>

TextInputStream::TextInputStream(IO::Readable* r)
{
    _r = r;
}

TextInputStream::~TextInputStream()
{
}

TextInputStream& TextInputStream::operator>>(int8_t& data)
{
    const int n_size = 4;
    char text[n_size + 1] = {0};
    
    int n = _readStrNum(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%" SCNi8, &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(uint8_t& data)
{
    const int n_size = 3;
    char text[n_size + 1] = {0};
    
    int n = _readStrNum(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%" SCNu8, &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(int16_t& data)
{
    const int n_size = 6;
    char text[n_size + 1] = {0};
    
    int n = _readStrNum(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%" SCNi16, &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(uint16_t& data)
{
    const int n_size = 5;
    char text[n_size + 1] = {0};
    
    int n = _readStrNum(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%" SCNu16, &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(int32_t& data)
{
    const int n_size = 11;
    char text[n_size + 1] = {0};
    
    int n = _readStrNum(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%d", &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(uint32_t& data)
{
    const int n_size = 10;
    char text[n_size + 1] = {0};
    
    int n = _readStrNum(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%u", &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(int64_t& data)
{
    const int n_size = 21;
    char text[n_size + 1] = {0};
    
    int n = _readStrNum(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%" SCNi64, &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(uint64_t& data)
{
    const int n_size = 20;
    char text[n_size + 1] = {0};
    
    int n = _readStrNum(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%" SCNu64, &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(float& data)
{
    const int n_size = FLT_MANT_DIG + 5;
    char text[n_size + 1] = {0};
    
    int n = _readStrNumFp(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else sscanf(text, "%g", &data);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(double& data)
{
    const int n_size = FLT_MANT_DIG + 5;
    char text[n_size + 1] = {0};
    
    int n = _readStrNumFp(text, n_size);
    
    if(n == 0) data = 0;
    else if(n > n_size) data = -1;
    else data = strtod(text, NULL);
    
    return *this;
}

TextInputStream& TextInputStream::operator>>(char* const text)
{
    return operator>>(reinterpret_cast<unsigned char* const>(text));
}

TextInputStream& TextInputStream::operator>>(unsigned char* const text)
{
    int i = 0;
    while(_r->read(&text[i], 1) == 1){
          if(text[i] == '\0') break;
          if(isspace(text[i])){
              _r->ungetc(text[i]);
              break;
          }
          i++;
    }
    text[i] = '\0';
    return *this;
}

int TextInputStream::_readStrNum(char* buf, int max_len)
{
    int i = 0;
    char c;
    
    while(_r->read(&c, 1) == 1){
        if(isspace(c)){
            _r->ungetc(c);
            break;
        }
        if(!isdigit(c)){
            if(!((c == '-' || c == '+') && i == 0)){
                _r->ungetc(c);
                break;
            }
        }
        if(i < max_len){
            buf[i] = c;
        }
        i++;
    }
    return i;
}

int TextInputStream::_readStrNumFp(char* buf, int max_len)
{
    int i = 0;
    char c;
    bool has_e = false;
    bool has_dot = false;
    
    while(_r->read(&c, 1) == 1){
        if(isspace(c)){
            _r->ungetc(c);
            break;
        }
        if(!isdigit(c)){
            if(c == '.' && has_dot == false){
                has_dot = true;
            }else if((c == 'e' || c == 'E') && has_e == false){
                has_e = true;
            }else{
                if(!(
                    (c == '-' || c == '+') &&
                    (i == 0 || buf[i - 1] == 'e' || buf[i - 1] == 'E')
                   )){
                    _r->ungetc(c);
                    break;
                }
            }
        }
        if(i < max_len){
            buf[i] = c;
        }
        i++;
    }
    return i;
}

