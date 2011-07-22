#ifndef _FS_ENTRYPOINT_H_
#define _FS_ENTRYPOINT_H_

#include <iostream>
#include <string>
#include "engine/engine.h"


ENGINE_NAMESPACE_BEGIN


class FSEntryPoint
{
public:

    virtual ~FSEntryPoint();
    
    virtual std::iostream* open(const std::string& fn, std::ios_base::openmode om) const = 0;
    //virtual bool close(std::iostream* iost);
};


ENGINE_NAMESPACE_END


#endif	//_FS_ENTRYPOINT_
