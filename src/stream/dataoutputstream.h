#ifndef _DATAOUTPUTSTREAM_H_
#define _DATAOUTPUTSTREAM_H_

#include "io/io.h"

class DataOutputStream
    :public IO::OutputStream
{
public:
    DataOutputStream(IO::Writable* w);
    ~DataOutputStream();

    DataOutputStream& operator<<(int8_t& data);
    DataOutputStream& operator<<(uint8_t& data);
    DataOutputStream& operator<<(int16_t& data);
    DataOutputStream& operator<<(uint16_t& data);
    DataOutputStream& operator<<(int32_t& data);
    DataOutputStream& operator<<(uint32_t& data);
    DataOutputStream& operator<<(int64_t& data);
    DataOutputStream& operator<<(uint64_t& data);
    DataOutputStream& operator<<(float& data);
    DataOutputStream& operator<<(double& data);
    DataOutputStream& operator<<(char* const data);
    DataOutputStream& operator<<(unsigned char* const data);

protected:
    IO::Writable* _w;
};

#endif	//_DATAOUTPUTSTREAM_H_
