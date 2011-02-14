#include "dataoutputstream.h"


DataOutputStream::DataOutputStream(IO::Writable* w)
{
    _w = w;
}

DataOutputStream::~DataOutputStream()
{
}

DataOutputStream::DataOutputStream& operator<<(int8_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(uint8_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(int16_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(uint16_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(int32_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(uint32_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(int64_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(uint64_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(float& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(double& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(char* const data)
{
    return operator<<(static_cast<unsigned char* const>(data));
}

DataOutputStream& DataOutputStream::operator<<(unsigned char* const data)
{
    int i = 1;
    while(data[i] != '\0'/* || data[i] != '\n' || data[i] != '\r'*/) i++;
    _w->write(data, i);
    return *this;
}


