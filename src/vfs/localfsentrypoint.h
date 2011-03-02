#ifndef _LOCALFSENTRYPOINT_H_
#define _LOCALFSENTRYPOINT_H_

#include <iostream>
#include "fsentrypoint.h"
#include "string/string.h"

class LocalFSEntryPoint
    :public FSEntryPoint
{
public:
    LocalFSEntryPoint();
    ~LocalFSEntryPoint();

    std::iostream* open(const String& fn, std::ios_base::openmode om);
protected:
    String _path;
};

#endif	//_LOCALFSENTRYPOINT_H_
