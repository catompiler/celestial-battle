#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "object/object.h"
#include "engine/engine.h"
#include <string>


ENGINE_NAMESPACE_BEGIN

class ComponentFactory;

class Component
        :public ::Object
{
public:
    Component(ComponentFactory* creator_,
              const std::string& name_);
    virtual ~Component();
    
    const std::string& name() const;//"entity" name
    
    virtual ComponentFactory* creator();
    virtual const ComponentFactory* creator() const;
    
protected:
    std::string _name;
    ComponentFactory* _creator;
};


ENGINE_NAMESPACE_END


#endif  //_COMPONENT_H_
