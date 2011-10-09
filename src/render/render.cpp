#include "render.h"

ENGINE_NAMESPACE_BEGIN


RenderComponent::RenderComponent(const std::string& name_)
        :Component(name_)
{
}

RenderComponent::~RenderComponent()
{
}


Render::Render()
        :ComponentFactoryTmpl<RenderComponent>()
{
}

Render::~Render()
{
}


ENGINE_NAMESPACE_END
