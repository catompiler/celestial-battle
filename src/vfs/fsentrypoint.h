#ifndef _FS_ENTRYPOINT_H_
#define _FS_ENTRYPOINT_H_

#include <iostream>
#include "string/string.h"

class FSEntryPoint
{
public:
    virtual ~FSEntryPoint();
    
    virtual std::iostream* open(const String& fn, std::ios_base::openmode om) = 0;
    //virtual bool close(std::iostream* iost);
};

#endif	//_FS_ENTRYPOINT_
