#include "locatedcomponent.h"

ENGINE_NAMESPACE_BEGIN



LocatedComponent::LocatedComponent(ComponentFactory* creator_,
                                    const std::string& name_,
                                    TransformComponent* transform_component_)
                            :Component(creator_, name_)
{
    _transform_component = transform_component_;
}

LocatedComponent::~LocatedComponent() {
}

TransformComponent* LocatedComponent::transformComponent()
{
    return _transform_component;
}



ENGINE_NAMESPACE_END

