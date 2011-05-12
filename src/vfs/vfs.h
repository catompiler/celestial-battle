#ifndef _VFS_H
#define _VFS_H

#include "fsentrypoint.h"
#include <iostream>
#include <list>
#include <string>


class VFS
    :public FSEntryPoint
{
public:

    VFS();
    ~VFS();
    
    std::iostream* open(const std::string& fn, std::ios_base::openmode om) const;
    bool close(std::iostream* iost) const;

    bool addEntryPoint(FSEntryPoint* entryPoint);
    bool delEntryPoint(FSEntryPoint* entryPoint);

private:
    typedef std::list<FSEntryPoint*> FSEntryPoints;
    FSEntryPoints* _entryPoints;
};

#endif	/* _VFS_H */

