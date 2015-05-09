#include "render.h"
#include "log/log.h"
#include "settings/settings.h"
#include "window/window.h"
#include "glcontext/glcontext.h"



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


Render::Render(Engine* engine_)
        :LocatedComponentFactoryTmpl<Graphics, Render>()
{
    _engine = engine_;
}

Render::~Render()
{
}


ENGINE_NAMESPACE_END
