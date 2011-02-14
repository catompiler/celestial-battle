#include "datainputstream.h"


DataInputStream::DataInputStream(IO::Readable* r)
{
    _r = r;
}

DataInputStream::~DataInputStream()
{
}

DataInputStream::DataOutputStream& operator>>(int8_t& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(uint8_t& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(int16_t& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(uint16_t& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(int32_t& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(uint32_t& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(int64_t& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(uint64_t& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(float& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(double& data)
{
    _r->read(&data, sizeof(data));
    return *this;
}

DataInputStream& DataInputStream::operator>>(char* const data)
{
    return operator>>(static_cast<unsigned char* const>(data));
}

DataInputStream& DataInputStream::operator>>(unsigned char* const data)
{
    int i = 0;
    while((_r->read(&data[i], 1) == 1) &&
          (data[i] != '\0'/* || data[i] != '\n' || data[i] != '\r'*/)) i++;
    return *this;
}


