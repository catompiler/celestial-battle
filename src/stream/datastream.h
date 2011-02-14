#ifndef _DATASTREAM_H_
#define _DATASTREAM_H_

#include "stream/datainputstream.h"
#include "stream/dataoutputstream.h"
#include "io/io.h"

class DataStream
    :public DataInputStream
     public DataOutputStream
{
public:
    DataStream(IO::ReadableWritable* rw);
    ~DataStream();

    DataStream& operator>>(int8_t& data);
    DataStream& operator>>(uint8_t& data);
    DataStream& operator>>(int16_t& data);
    DataStream& operator>>(uint16_t& data);
    DataStream& operator>>(int32_t& data);
    DataStream& operator>>(uint32_t& data);
    DataStream& operator>>(int64_t& data);
    DataStream& operator>>(uint64_t& data);
    DataStream& operator>>(float& data);
    DataStream& operator>>(double& data);
    DataStream& operator>>(char* const data);
    DataStream& operator>>(unsigned char* const data);

    DataStream& operator<<(int8_t& data);
    DataStream& operator<<(uint8_t& data);
    DataStream& operator<<(int16_t& data);
    DataStream& operator<<(uint16_t& data);
    DataStream& operator<<(int32_t& data);
    DataStream& operator<<(uint32_t& data);
    DataStream& operator<<(int64_t& data);
    DataStream& operator<<(uint64_t& data);
    DataStream& operator<<(float& data);
    DataStream& operator<<(double& data);
    DataStream& operator<<(char* const data);
    DataStream& operator<<(unsigned char* const data);

private:
    IO::ReadableWritable* _rw;
};

#endif	//_DATASTREAM_H_
