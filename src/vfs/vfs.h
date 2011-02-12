#ifndef _VFS_H
#define	_VFS_H

#include "io/io.h"

class VFS {
public:

    class File
        :public IO::File
    {
    public:
    private:
    };

    VFS();
    ~VFS();
private:

};

#endif	/* _VFS_H */

