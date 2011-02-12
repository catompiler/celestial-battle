#ifndef _VFS_H
#define	_VFS_H

#include "io/io.h"
#include "string/string.h"

class VFS {
public:

    class File
        :public IO::File
    {
    public:
        File();
        ~File();

        bool open(const String& fn, IO::File::openmode_t om);
        bool close();
    private:
    };

    VFS();
    ~VFS();
private:

};

#endif	/* _VFS_H */

