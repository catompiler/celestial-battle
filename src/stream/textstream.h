#ifndef _TEXTSTREAM_H_
#define _TEXTSTREAM_H_

#include "textinputstream.h"
#include "textoutputstream.h"
#include "io/io.h"

class TextStream
    :public TextInputStream
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

    TextStream& operator<<(int8_t& text);
    TextStream& operator<<(uint8_t& text);
    TextStream& operator<<(int16_t& text);
    TextStream& operator<<(uint16_t& text);
    TextStream& operator<<(int32_t& text);
    TextStream& operator<<(uint32_t& text);
    TextStream& operator<<(int64_t& text);
    TextStream& operator<<(uint64_t& text);
    TextStream& operator<<(float& text);
    TextStream& operator<<(double& text);
    TextStream& operator<<(char* const text);
    TextStream& operator<<(unsigned char* const text);

private:
    IO::ReadableWritable* _rw;
};

#endif	//_TEXTSTREAM_H_
