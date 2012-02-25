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
                     Transformation* transformation_);
    ~LocatedComponent();
    
    Transformation* transformation();
    
protected:
    Transformation* _transformation;
};


ENGINE_NAMESPACE_END


#endif	/* LOCATEDCOMPONENT_H */

