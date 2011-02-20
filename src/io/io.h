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
        virtual ~Readable(){}
        virtual IO::datasize_t read(void* data, datasize_t s) = 0;
        virtual bool ungetc(char c) = 0;
    };

    class Writable{
    public:
        virtual ~Writable(){}
        virtual IO::datasize_t write(const void* data, datasize_t s) = 0;
    };

    class RandomAccess{
    public:
        virtual ~RandomAccess(){}
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
        virtual OutputStream& operator<<(const int8_t& data) = 0;
        virtual OutputStream& operator<<(const uint8_t& data) = 0;
        virtual OutputStream& operator<<(const int16_t& data) = 0;
        virtual OutputStream& operator<<(const uint16_t& data) = 0;
        virtual OutputStream& operator<<(const int32_t& data) = 0;
        virtual OutputStream& operator<<(const uint32_t& data) = 0;
        virtual OutputStream& operator<<(const int64_t& data) = 0;
        virtual OutputStream& operator<<(const uint64_t& data) = 0;
        virtual OutputStream& operator<<(const float& data) = 0;
        virtual OutputStream& operator<<(const double& data) = 0;
        virtual OutputStream& operator<<(const char* const data) = 0;
        virtual OutputStream& operator<<(const unsigned char* const data) = 0;
    };
}

#endif	/* _IO_H */

