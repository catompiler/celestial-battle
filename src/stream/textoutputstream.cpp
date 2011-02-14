#include "textoutputstream.h"


TextOutputStream::TextOutputStream(IO::Writable* w)
{
    _w = w;
}

TextOutputStream::~TextOutputStream()
{
}

TextOutputStream::TextOutputStream& operator<<(int8_t& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(uint8_t& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(int16_t& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(uint16_t& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(int32_t& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(uint32_t& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(int64_t& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(uint64_t& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(float& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(double& text)
{
    _w->write(&text, sizeof(text));
    return *this;
}

TextOutputStream& TextOutputStream::operator<<(char* const text)
{
    return operator<<(static_cast<unsigned char* const>(text));
}

TextOutputStream& TextOutputStream::operator<<(unsigned char* const text)
{
    int i = 1;
    while(text[i] != '\0'/* || text[i] != '\n' || text[i] != '\r'*/) i++;
    _w->write(text, i);
    return *this;
}


