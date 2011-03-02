#include "vfs.h"
#include <algorithm>

/*
 * VFS
 */

VFS::VFS() {
    _entryPoints = new FSEntryPoints;
}

VFS::~VFS() {
    delete _entryPoints;
}

std::iostream* VFS::open(const String& fn, std::ios_base::openmode om)
{
    std::iostream* res = NULL;
    for(FSEntryPoints::iterator it = _entryPoints->begin();
                                it != _entryPoints->end(); ++it){
        res = (*it)->open(fn, om);
        if(res) break;
    }
    return res;
}

bool VFS::close(std::iostream* iost)
{
    delete iost;
    return true;
}

bool VFS::addEntryPoint(FSEntryPoint* entryPoint)
{
    if(entryPoint == this) return false;
    
    FSEntryPoints::iterator it = std::find(_entryPoints->begin(),
                                           _entryPoints->end(), entryPoint);
    if(it == _entryPoints->end()){
        _entryPoints->push_back(entryPoint);
        return true;
    }
    return false;
}

bool VFS::delEntryPoint(FSEntryPoint* entryPoint)
{
    FSEntryPoints::iterator it = std::find(_entryPoints->begin(),
                                           _entryPoints->end(), entryPoint);
    if(it != _entryPoints->end()){
        _entryPoints->erase(it);
        return true;
    }
    return false;
}
