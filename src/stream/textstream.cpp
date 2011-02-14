#include "textstream.h"


TextStream::TextStream(IO::ReadableWritable* rw)
    :TextInputStream(rw), TextOutputStream(rw)
{
    _rw = rw;
}

TextStream::~TextStream()
{
}

TextStream& TextStream::operator>>(int8_t& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(uint8_t& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(int16_t& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(uint16_t& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(int32_t& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(uint32_t& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(int64_t& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(uint64_t& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(float& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(double& text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(char* const text)
{
    TextInputStream::operator>>(text);
    return *this;
}

TextStream& TextStream::operator>>(unsigned char* const text)
{
    TextInputStream::operator>>(text);
    return *this;
}


TextStream& TextStream::operator<<(int8_t& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(uint8_t& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(int16_t& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(uint16_t& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(int32_t& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(uint32_t& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(int64_t& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(uint64_t& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(float& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(double& text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(char* const text)
{
    TextOutputStream::operator<<(text);
    return *this;
}

TextStream& TextStream::operator<<(unsigned char* const text)
{
    TextOutputStream::operator<<(text);
    return *this;
}


