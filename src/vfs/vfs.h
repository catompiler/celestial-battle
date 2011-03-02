#ifndef _VFS_H
#define _VFS_H

#include "string/string.h"
#include "fsentrypoint.h"
#include <iostream>
#include <vector>


class VFS
    :public FSEntryPoint
{
public:

    VFS();
    ~VFS();
    
    std::iostream* open(const String& fn, std::ios_base::openmode om);
    bool close(std::iostream* iost);

    bool addEntryPoint(FSEntryPoint* entryPoint);
    bool delEntryPoint(FSEntryPoint* entryPoint);

private:
    typedef std::vector<FSEntryPoint*> FSEntryPoints;
    FSEntryPoints* _entryPoints;
};

#endif	/* _VFS_H */

