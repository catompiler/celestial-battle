#ifndef _DATAOUTPUTSTREAM_H_
#define _DATAOUTPUTSTREAM_H_

#include "io/io.h"

class DataOutputStream
    :public IO::OutputStream
{
public:
    DataOutputStream(IO::Writable* w);
    ~DataOutputStream();

    DataOutputStream& operator<<(const int8_t& data);
    DataOutputStream& operator<<(const uint8_t& data);
    DataOutputStream& operator<<(const int16_t& data);
    DataOutputStream& operator<<(const uint16_t& data);
    DataOutputStream& operator<<(const int32_t& data);
    DataOutputStream& operator<<(const uint32_t& data);
    DataOutputStream& operator<<(const int64_t& data);
    DataOutputStream& operator<<(const uint64_t& data);
    DataOutputStream& operator<<(const float& data);
    DataOutputStream& operator<<(const double& data);
    DataOutputStream& operator<<(const char* const data);
    DataOutputStream& operator<<(const unsigned char* const data);

protected:
    IO::Writable* _w;
};

#endif	//_DATAOUTPUTSTREAM_H_
