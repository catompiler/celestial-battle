#ifndef LOCATEDCOMPONENT_H
#define	LOCATEDCOMPONENT_H

#include "engine/engine.h"
#include "component/component.h"
#include "transformstree/transformstree.h"
#include <string>


ENGINE_NAMESPACE_BEGIN


class LocatedComponent
    :public Component{
public:
    LocatedComponent(ComponentFactory* creator_,
                     const std::string& name_,
                     TransformComponent* transform_component_);
    ~LocatedComponent();
    
    TransformComponent* transformComponent();
    
protected:
    TransformComponent* _transform_component;
};


ENGINE_NAMESPACE_END


#endif	/* LOCATEDCOMPONENT_H */

