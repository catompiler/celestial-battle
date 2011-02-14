#include "datastream.h"


DataStream::DataStream(IO::ReadableWritable* rw)
    :DataInputStream(rw), DataOutputStream(rw)
{
    _rw = rw;
}

DataStream::~DataStream()
{
}

