#include "component.h"
#include "componentfactory.h"


ENGINE_NAMESPACE_BEGIN


Component::Component(ComponentFactory* creator_,
                     const std::string& name_)
        : ::Object()
{
    _creator = creator_;
    _name = name_;
}

Component::~Component()
{
}

const std::string& Component::name() const
{
    return _name;
}

ComponentFactory* Component::creator()
{
    return _creator;
}

const ComponentFactory* Component::creator() const
{
    return _creator;
}


ENGINE_NAMESPACE_END

