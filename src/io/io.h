#ifndef _IO_H
#define	_IO_H

#include <stddef.h>
#include <stdint.h>
#include "string/string.h"

namespace IO{

    typedef ::size_t datasize_t;
    typedef long int offset_t;

    struct SeekOrigin{
        enum value{Begin = 0, Current, End};
    };
    typedef SeekOrigin::value seekorigin_t;
    
    struct OpenMode{
        enum value{Read = 1, Write = 2, Append = 4, Truncate = 8, Binary = 16};
    };
    typedef unsigned int openmode_t;

    class Readable{
    public:
        virtual IO::datasize_t read(void* data, datasize_t s) = 0;
    };

    class Writable{
    public:
        virtual IO::datasize_t write(void* data, datasize_t s) = 0;
    };

    class RandomAccess{
    public:
        virtual bool seek(offset_t p, seekorigin_t o) = 0;
        virtual offset_t tell() = 0;
    };

    class ReadableWritable
        :virtual public Readable,
         virtual public Writable
    {
    };

    class RandomReadable
        :virtual public Readable,
         virtual public RandomAccess
    {
    };

    class RandomWritable
        :virtual public Writable,
         virtual public RandomAccess
    {
    };

    class RandomReadableWritable
        :virtual public ReadableWritable,
         virtual public RandomReadable,
         virtual public RandomWritable
    {
    };

    class File
        :virtual public RandomReadableWritable
    {
    public:
        
        virtual datasize_t size() = 0;

    protected:
        virtual bool open(const String& fn, openmode_t om) = 0;
        virtual bool close() = 0;
    };

    class InputStream{
    public:
        virtual InputStream& operator>>(int8_t& data) = 0;
        virtual InputStream& operator>>(uint8_t& data) = 0;
        virtual InputStream& operator>>(int16_t& data) = 0;
        virtual InputStream& operator>>(uint16_t& data) = 0;
        virtual InputStream& operator>>(int32_t& data) = 0;
        virtual InputStream& operator>>(uint32_t& data) = 0;
        virtual InputStream& operator>>(int64_t& data) = 0;
        virtual InputStream& operator>>(uint64_t& data) = 0;
        virtual InputStream& operator>>(float& data) = 0;
        virtual InputStream& operator>>(double& data) = 0;
        virtual InputStream& operator>>(char* const data) = 0;
        virtual InputStream& operator>>(unsigned char* const data) = 0;
    };
    
    class OutputStream{
    public:
    };
    
    class Stream
        :virtual public InputStream,
         virtual public OutputStream
    {
    };
    
}

#endif	/* _IO_H */

