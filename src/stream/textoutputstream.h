#ifndef _TEXTOUTPUTSTREAM_H_
#define _TEXTOUTPUTSTREAM_H_

#include "io/io.h"

class TextOutputStream
    :public IO::OutputStream
{
public:
    TextOutputStream(IO::Writable* w);
    ~TextOutputStream();

    TextOutputStream& operator<<(int8_t& data);
    TextOutputStream& operator<<(uint8_t& data);
    TextOutputStream& operator<<(int16_t& data);
    TextOutputStream& operator<<(uint16_t& data);
    TextOutputStream& operator<<(int32_t& data);
    TextOutputStream& operator<<(uint32_t& data);
    TextOutputStream& operator<<(int64_t& data);
    TextOutputStream& operator<<(uint64_t& data);
    TextOutputStream& operator<<(float& data);
    TextOutputStream& operator<<(double& data);
    TextOutputStream& operator<<(char* const data);
    TextOutputStream& operator<<(unsigned char* const data);

protected:
    IO::Writable* _w;
};

#endif	//_TEXTOUTPUTSTREAM_H_
