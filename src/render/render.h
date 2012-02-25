#ifndef _RENDER_H_
#define _RENDER_H_

#include "engine/engine.h"
#include "component/locatedcomponent.h"
#include "component/componentfactory.h"
#include "transformstree/transformstree.h"
#include <string>


ENGINE_NAMESPACE_BEGIN


class Render;

class RenderComponent
        :public LocatedComponent
{
public:
    RenderComponent(Render* creator_,
                     const std::string& name_,
                     Transformation* transformation_);
    ~RenderComponent();
};


class Render
        :public LocatedComponentFactoryTmpl<RenderComponent, Render>
{
public:
    Render();
    ~Render();
private:
};


ENGINE_NAMESPACE_END

#endif  //_RENDER_H_
