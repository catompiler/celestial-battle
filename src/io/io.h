#ifndef _IO_H
#define	_IO_H

#include <stddef.h>
#include "string/string.h"

namespace IO{

    typedef ::size_t datasize_t;
    typedef long int offset_t;

    struct SeekOrigin{
        enum value{Begin = 0, Current, End};
    };
    typedef SeekOrigin::value seekorigin_t;

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
        struct OpenMode{
            enum value{Read = 1, Write = 2, Append = 4, Truncate = 8, Binary = 16};
        };
        typedef unsigned int openmode_t;
        
        virtual datasize_t size() = 0;

    protected:
        virtual bool open(const String& fn, openmode_t om) = 0;
        virtual bool close() = 0;
    };

}

#endif	/* _IO_H */

