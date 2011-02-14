#include "datastream.h"


DataStream::DataStream(IO::ReadableWritable* rw)
    :DataInputStream(rw), DataOutputStream(rw)
{
    _rw = rw;
}

DataStream::~DataStream()
{
}

DataStream& DataStream::operator>>(int8_t& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(uint8_t& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(int16_t& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(uint16_t& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(int32_t& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(uint32_t& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(int64_t& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(uint64_t& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(float& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(double& data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(char* const data)
{
    DataInputStream::operator>>(data);
    return *this;
}

DataStream& DataStream::operator>>(unsigned char* const data)
{
    DataInputStream::operator>>(data);
    return *this;
}


DataStream& DataStream::operator<<(int8_t& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(uint8_t& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(int16_t& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(uint16_t& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(int32_t& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(uint32_t& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(int64_t& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(uint64_t& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(float& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(double& data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(char* const data)
{
    DataOutputStream::operator<<(data);
    return *this;
}

DataStream& DataStream::operator<<(unsigned char* const data)
{
    DataOutputStream::operator<<(data);
    return *this;
}


