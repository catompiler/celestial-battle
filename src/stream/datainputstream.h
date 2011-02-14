#ifndef _DATAINPUTSTREAM_H_
#define _DATAINPUTSTREAM_H_

#include "io/io.h"

class DataInputStream
    :public IO::InputStream
{
public:
    DataInputStream(IO::Readable* r);
    ~DataInputStream();

    DataInputStream& operator>>(int8_t& data);
    DataInputStream& operator>>(uint8_t& data);
    DataInputStream& operator>>(int16_t& data);
    DataInputStream& operator>>(uint16_t& data);
    DataInputStream& operator>>(int32_t& data);
    DataInputStream& operator>>(uint32_t& data);
    DataInputStream& operator>>(int64_t& data);
    DataInputStream& operator>>(uint64_t& data);
    DataInputStream& operator>>(float& data);
    DataInputStream& operator>>(double& data);
    DataInputStream& operator>>(char* const data);
    DataInputStream& operator>>(unsigned char* const data);

protected:
    IO::Readable* _r;
};

#endif	//_DATAINPUTSTREAM_H_
