#ifndef _RENDER_H_
#define _RENDER_H_

#include "engine/engine.h"
#include "component/locatedcomponent.h"
#include "component/componentfactory.h"
#include "transformstree/transformstree.h"
#include "resources/resources.h"
#include <string>


ENGINE_NAMESPACE_BEGIN


class Render;

class Graphics
        :public LocatedComponent
{
public:
    Graphics(Render* creator_,
                     const std::string& name_,
                     Transformation* transformation_);
    ~Graphics();
    
    void setMaterial(material_ptr material_);
    material_ptr material();
    
    void setMesh(mesh_ptr mesh_);
    mesh_ptr mesh();
    
};


class Render
        :public LocatedComponentFactoryTmpl<Graphics, Render>
{
public:
    Render();
    ~Render();
private:
};


ENGINE_NAMESPACE_END

#endif  //_RENDER_H_
