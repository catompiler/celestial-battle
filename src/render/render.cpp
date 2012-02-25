#include "render.h"

ENGINE_NAMESPACE_BEGIN


RenderComponent::RenderComponent(Render* creator_,
                                   const std::string& name_,
                                   Transformation* transformation_)
        :LocatedComponent(creator_, name_, transformation_)
{
}

RenderComponent::~RenderComponent()
{
}


Render::Render()
        :LocatedComponentFactoryTmpl<RenderComponent, Render>()
{
}

Render::~Render()
{
}


ENGINE_NAMESPACE_END
