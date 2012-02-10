#ifndef _READER_H
#define _READER_H

#include <string>
#include "engine/engine.h"

ENGINE_NAMESPACE_BEGIN

template <class R>
class Reader
{
public:
    
    typedef R ResourceType;
    
    Reader();
    virtual ~Reader();
    
    virtual R* read(const std::string& filename_) const = 0;
};

ENGINE_NAMESPACE_END

#endif  //_READER_H
