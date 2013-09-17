#ifndef _READER_H
#define _READER_H

#include <string>
#include "engine/engine.h"

ENGINE_NAMESPACE_BEGIN

class Resources;

template <class R>
class Reader
{
public:
    
    typedef R ResourceType;
    
    Reader();
    virtual ~Reader();
    
    virtual R* read(Resources* resources_, const std::string& filename_) const = 0;
};



template<class R>
Reader<R>::Reader()
{
}

template<class R>
Reader<R>::~Reader()
{
}


ENGINE_NAMESPACE_END

#endif  //_READER_H
