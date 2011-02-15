#include "textoutputstream.h"
#include <stdio.h>


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
    sprintf(text, "%d", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const uint8_t& data)
{
    char text[4] = {0};//255
    sprintf(text, "%u", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const int16_t& data)
{
    char text[7] = {0};//-10000
    sprintf(text, "%d", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const uint16_t& data)
{
    char text[6] = {0};//65535
    sprintf(text, "%u", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const int32_t& data)
{
    char text[12] = {0};//-2000000000
    sprintf(text, "%d", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const uint32_t& data)
{
    char text[11] = {0};//4294967295
    sprintf(text, "%u", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const int64_t& data)
{
    char text[22] = {0};//-10000000000000000000
    sprintf(text, "%lld", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const uint64_t& data)
{
    char text[21] = {0};//18446744073709551615
    sprintf(text, "%llu", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const float& data)
{
    char text[4] = {0};
    sprintf(text, "%f", data);
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(const double& data)
{
    _w->write(&text, sizeof(text));
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


