#include "vfs.h"
#include <fstream>
#include "fileinfilebuf.h"

/*
 * VFS
 */

VFS::VFS() {
}

VFS::~VFS() {
}

std::iostream* VFS::open(const String& fn, std::ios_base::openmode om)
{
    std::fstream* res = new std::fstream(fn.c_str(), om);
    return res;
}

bool close(std::iostream* iost)
{
    delete iost;
    return true;
}
