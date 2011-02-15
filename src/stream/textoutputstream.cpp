#include "textoutputstream.h"
#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <float.h>

TextOutputStream::TextOutputStream(IO::Writable* w)
{
    _w = w;
}

TextOutputStream::~TextOutputStream()
{
}

TextOutputStream& TextOutputStream::operator<<(const int8_t& data)
{
    char text[5] = {0};//-100
    int s = sprintf(text, "%d", data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const uint8_t& data)
{
    char text[4] = {0};//255
    int s = sprintf(text, "%u", data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const int16_t& data)
{
    char text[7] = {0};//-10000
    int s = sprintf(text, "%d", data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const uint16_t& data)
{
    char text[6] = {0};//65535
    int s = sprintf(text, "%u", data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const int32_t& data)
{
    char text[12] = {0};//-2000000000
    int s = sprintf(text, "%d", data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const uint32_t& data)
{
    char text[11] = {0};//4294967295
    int s = sprintf(text, "%u", data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const int64_t& data)
{
    char text[22] = {0};//-10000000000000000000 || -9000000000000000000 ?
    int s = sprintf(text, "%" PRId64, data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const uint64_t& data)
{
    char text[21] = {0};//18446744073709551615
    int s = sprintf(text, "%" PRIu64, data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const float& data)
{
    char text[FLT_MANT_DIG + 6] = {0}; // xxxxx.yyyy E-zz
    int s = sprintf(text, "%f", data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const double& data)
{
    char text[DBL_MANT_DIG + 6] = {0}; // xxxxx.yyyy E-zz
    int s = sprintf(text, "%f", data);
    if(s > 0) _w->write(text, s);
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const char* const data)
{
    return operator<<(reinterpret_cast<const unsigned char* const>(data));
}

TextOutputStream& TextOutputStream::operator<<(const unsigned char* const data)
{
    int i = 0;
    while(data[i] != '\0'/* || text[i] != '\n' || text[i] != '\r'*/) i++;
    //i++;// - w/o '\0' symbol
    _w->write(data, i);
    return *this;
}


