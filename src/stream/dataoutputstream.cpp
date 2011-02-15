#include "dataoutputstream.h"


DataOutputStream::DataOutputStream(IO::Writable* w)
{
    _w = w;
}

DataOutputStream::~DataOutputStream()
{
}

DataOutputStream& DataOutputStream::operator<<(const int8_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const uint8_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const int16_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const uint16_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const int32_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const uint32_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const int64_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const uint64_t& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const float& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const double& data)
{
    _w->write(&data, sizeof(data));
    return *this;
}

DataOutputStream& DataOutputStream::operator<<(const char* const data)
{
    return operator<<(reinterpret_cast<const unsigned char* const>(data));
}

DataOutputStream& DataOutputStream::operator<<(const unsigned char* const data)
{
    int i = 0;
    while(data[i] != '\0'/* || data[i] != '\n' || data[i] != '\r'*/) i++;
    i++;//with '\0' symbol
    _w->write(data, i);
    return *this;
}


