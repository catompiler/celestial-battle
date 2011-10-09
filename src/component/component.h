#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "object/object.h"
#include "engine/engine.h"
#include <string>


ENGINE_NAMESPACE_BEGIN


class Component
        :public ::Object
{
public:
    Component(const std::string& name_ = std::string());
    virtual ~Component();
    
    const std::string& name() const;//"entity" name
    
protected:
    std::string _name;
};


ENGINE_NAMESPACE_END


#endif  //_COMPONENT_H_
