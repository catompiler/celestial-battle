#ifndef _TEXTINPUTSTREAM_H_
#define _TEXTINPUTSTREAM_H_

#include "io/io.h"

class TextInputStream
    :public IO::InputStream
{
public:
    TextInputStream(IO::Readable* r);
    ~TextInputStream();

    TextInputStream& operator>>(int8_t& data);
    TextInputStream& operator>>(uint8_t& data);
    TextInputStream& operator>>(int16_t& data);
    TextInputStream& operator>>(uint16_t& data);
    TextInputStream& operator>>(int32_t& data);
    TextInputStream& operator>>(uint32_t& data);
    TextInputStream& operator>>(int64_t& data);
    TextInputStream& operator>>(uint64_t& data);
    TextInputStream& operator>>(float& data);
    TextInputStream& operator>>(double& data);
    TextInputStream& operator>>(char* const data);
    TextInputStream& operator>>(unsigned char* const data);

protected:
    IO::Readable* _r;
};

#endif	//_TEXTINPUTSTREAM_H_
