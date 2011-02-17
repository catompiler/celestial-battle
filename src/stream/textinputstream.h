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
    TextInputStream& operator>>(char* const text);
    TextInputStream& operator>>(unsigned char* const text);

protected:
    IO::Readable* _r;
    int _readStrNum(char* buf, int max_len);
    int _readStrNumFp(char* buf, int max_len);
};

#endif	//_TEXTINPUTSTREAM_H_
