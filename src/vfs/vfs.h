#ifndef _VFS_H
#define _VFS_H

#include "fsentrypoint.h"
#include <iostream>
#include <list>
#include <string>
#include "engine/engine.h"



ENGINE_NAMESPACE_BEGIN


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


ENGINE_NAMESPACE_END


#endif	/* _VFS_H */

