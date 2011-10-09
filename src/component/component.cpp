#include "component.h"


ENGINE_NAMESPACE_BEGIN


Component::Component(const std::string& name_)
        : ::Object()
{
    _name = name_;
}

Component::~Component()
{
}

const std::string& Component::name() const
{
    return _name;
}


ENGINE_NAMESPACE_END

