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
private:
    IO::ReadableWritable* _rw;
};

#endif	//_DATASTREAM_H_
