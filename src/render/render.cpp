#include "render.h"

ENGINE_NAMESPACE_BEGIN


Graphics::Graphics(Render* creator_,
                                   const std::string& name_,
                                   Transformation* transformation_)
        :LocatedComponent(creator_, name_, transformation_)
{
}

Graphics::~Graphics()
{
}


Render::Render()
        :LocatedComponentFactoryTmpl<Graphics, Render>()
{
}

Render::~Render()
{
}


ENGINE_NAMESPACE_END
