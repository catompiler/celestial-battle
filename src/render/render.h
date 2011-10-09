#ifndef _RENDER_H_
#define _RENDER_H_

#include "engine/engine.h"
#include "component/component.h"
#include "component/componentfactory.h"
#include <string>


ENGINE_NAMESPACE_BEGIN


class RenderComponent
        :public Component
{
public:
    RenderComponent(const std::string& name_ = std::string());
    ~RenderComponent();
};


class Render
        :public ComponentFactoryTmpl<RenderComponent>
{
public:
    Render();
    ~Render();
private:
};


ENGINE_NAMESPACE_END

#endif  //_RENDER_H_
