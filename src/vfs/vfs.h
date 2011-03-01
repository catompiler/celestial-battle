#ifndef _VFS_H
#define	_VFS_H

#include "string/string.h"
#include <iostream>


class VFS {
public:

    VFS();
    ~VFS();
    
    std::iostream* open(const String& fn, std::ios_base::openmode om);
    bool close(std::iostream* iost);
private:

};

#endif	/* _VFS_H */

