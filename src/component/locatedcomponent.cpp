#include "locatedcomponent.h"

ENGINE_NAMESPACE_BEGIN



LocatedComponent::LocatedComponent(ComponentFactory* creator_,
                                    const std::string& name_,
                                    Transformation* transformation_)
                            :Component(creator_, name_)
{
    _transformation = transformation_;
}

LocatedComponent::~LocatedComponent() {
}

Transformation* LocatedComponent::transformation()
{
    return _transformation;
}



ENGINE_NAMESPACE_END

