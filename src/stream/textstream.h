#ifndef _TEXTSTREAM_H_
#define _TEXTSTREAM_H_

#include "textinputstream.h"
#include "textoutputstream.h"
#include "io/io.h"

class TextStream
    :public TextInputStream,
     public TextOutputStream
{
public:
    TextStream(IO::ReadableWritable* rw);
    ~TextStream();

    TextStream& operator>>(int8_t& text);
    TextStream& operator>>(uint8_t& text);
    TextStream& operator>>(int16_t& text);
    TextStream& operator>>(uint16_t& text);
    TextStream& operator>>(int32_t& text);
    TextStream& operator>>(uint32_t& text);
    TextStream& operator>>(int64_t& text);
    TextStream& operator>>(uint64_t& text);
    TextStream& operator>>(float& text);
    TextStream& operator>>(double& text);
    TextStream& operator>>(char* const text);
    TextStream& operator>>(unsigned char* const text);

    TextStream& operator<<(const int8_t& text);
    TextStream& operator<<(const uint8_t& text);
    TextStream& operator<<(const int16_t& text);
    TextStream& operator<<(const uint16_t& text);
    TextStream& operator<<(const int32_t& text);
    TextStream& operator<<(const uint32_t& text);
    TextStream& operator<<(const int64_t& text);
    TextStream& operator<<(const uint64_t& text);
    TextStream& operator<<(const float& text);
    TextStream& operator<<(const double& text);
    TextStream& operator<<(const char* const text);
    TextStream& operator<<(const unsigned char* const text);

private:
    IO::ReadableWritable* _rw;
};

#endif	//_TEXTSTREAM_H_
