#ifndef _VFS_H
#define	_VFS_H

#include "io/io.h"
#include "string/string.h"
#include <cstdio>


class VFS {
public:

    class File
        :public IO::File
    {
    public:
        File();
        ~File();

        bool open(const String& fn, IO::openmode_t om);
        bool close();

        IO::datasize_t size();

        bool seek(IO::offset_t p, IO::seekorigin_t o);
        IO::offset_t tell();
        
        IO::datasize_t read(void* data, IO::datasize_t s);
        IO::datasize_t write(const void* data, IO::datasize_t s);
        
        bool ungetc(char c);

    private:
        FILE* _f;
    };

    VFS();
    ~VFS();
    
    IO::File* open(const String& fn, IO::openmode_t om);
    bool close(IO::File* f);
private:

};

#endif	/* _VFS_H */

