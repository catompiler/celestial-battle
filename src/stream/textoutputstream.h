#ifndef _TEXTOUTPUTSTREAM_H_
#define _TEXTOUTPUTSTREAM_H_

#include "io/io.h"

class TextOutputStream
    :public IO::OutputStream
{
public:
    TextOutputStream(IO::Writable* w);
    ~TextOutputStream();

    TextOutputStream& operator<<(const int8_t& data);
    TextOutputStream& operator<<(const uint8_t& data);
    TextOutputStream& operator<<(const int16_t& data);
    TextOutputStream& operator<<(const uint16_t& data);
    TextOutputStream& operator<<(const int32_t& data);
    TextOutputStream& operator<<(const uint32_t& data);
    TextOutputStream& operator<<(const int64_t& data);
    TextOutputStream& operator<<(const uint64_t& data);
    TextOutputStream& operator<<(const float& data);
    TextOutputStream& operator<<(const double& data);
    TextOutputStream& operator<<(const char* const data);
    TextOutputStream& operator<<(const unsigned char* const data);

protected:
    IO::Writable* _w;
};

#endif	//_TEXTOUTPUTSTREAM_H_
