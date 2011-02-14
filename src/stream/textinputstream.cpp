#include "textinputstream.h"


TextInputStream::TextInputStream(IO::Readable* r)
{
    _r = r;
}

TextInputStream::~TextInputStream()
{
}

TextInputStream::TextOutputStream& operator>>(int8_t& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(uint8_t& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(int16_t& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(uint16_t& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(int32_t& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(uint32_t& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(int64_t& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(uint64_t& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(float& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(double& text)
{
    _r->read(&text, sizeof(text));
    return *this;
}

TextInputStream& TextInputStream::operator>>(char* const text)
{
    return operator>>(static_cast<unsigned char* const>(text));
}

TextInputStream& TextInputStream::operator>>(unsigned char* const text)
{
    int i = 0;
    while((_r->read(&text[i], 1) == 1) &&
          (text[i] != '\0'/* || text[i] != '\n' || text[i] != '\r'*/)) i++;
    return *this;
}


