#ifndef _LOCALFSENTRYPOINT_H_
#define _LOCALFSENTRYPOINT_H_

#include <iostream>
#include "fsentrypoint.h"
#include <string>
#include "engine/engine.h"


ENGINE_NAMESPACE_BEGIN


class LocalFSEntryPoint
    :public FSEntryPoint
{
public:

    LocalFSEntryPoint();
    LocalFSEntryPoint(const std::string& path_);
    ~LocalFSEntryPoint();

    std::iostream* open(const std::string& fn, std::ios_base::openmode om) const;

    void setPath(const std::string& path_);
    const std::string& path() const;

protected:

    std::string _path;

    void _setPath(const std::string& path_);
    std::string _addToPath(const std::string& fn) const;

};


ENGINE_NAMESPACE_END


#endif	//_LOCALFSENTRYPOINT_H_
