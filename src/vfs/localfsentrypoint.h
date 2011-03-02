#ifndef _LOCALFSENTRYPOINT_H_
#define _LOCALFSENTRYPOINT_H_

#include <iostream>
#include "fsentrypoint.h"
#include "string/string.h"

class LocalFSEntryPoint
    :public FSEntryPoint
{
public:

    static String separator();

    LocalFSEntryPoint();
    LocalFSEntryPoint(const String& path_);
    ~LocalFSEntryPoint();

    std::iostream* open(const String& fn, std::ios_base::openmode om);

    void setPath(const String& path_);
    const String& path();

protected:

    String _path;

    void _setPath(const String& path_);
    String _getSumPath(const String& path1_, const String& path2_);

};

#endif	//_LOCALFSENTRYPOINT_H_
