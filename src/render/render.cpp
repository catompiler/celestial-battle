#include "render.h"

ENGINE_NAMESPACE_BEGIN


RenderComponent::RenderComponent(Render* creator_, const std::string& name_)
        :Component(creator_, name_)
{
}

RenderComponent::~RenderComponent()
{
}


Render::Render()
        :ComponentFactoryTmpl<RenderComponent, Render>()
{
}

Render::~Render()
{
}


ENGINE_NAMESPACE_END
