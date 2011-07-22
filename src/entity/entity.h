#ifndef _ENTITY_H
#define _ENTITY_H

#include "engine/engine.h"
#include "object/object.h"
#include "glmath/glmath.h"
#include <string>
#include <list>



ENGINE_NAMESPACE_BEGIN


class Entity
    :public Object
{
public:
    
    typedef std::list<Entity*> ChildList;
    typedef ChildList::iterator ChildsIterator;
    
    Entity(const std::string& name_ = std::string(),
           const std::string& parent_name_ = std::string());
    ~Entity();

    const std::string& name() const;
    void setName(const std::string& name_);
    
    const std::string& parentName() const;
    void setParentName(const std::string& name_);

    Entity* parent();
    const Entity* parent() const;
    void setParent(Entity* parent_);
    void addChild(Entity* child_);
    void removeChild(Entity* child_);
    bool hasChild(const Entity* child_) const;
    ChildsIterator childsBegin();
    ChildsIterator childsEnd();
    
protected:
    Entity* _parent;
    std::string _name;
    std::string _parent_name;
    
    ChildList _childs;
    
    void _addChild(Entity* child_, bool call_setParent);
    void _removeChild(Entity* child_, bool call_setParent);
};



ENGINE_NAMESPACE_END


#endif  //_ENTITY_H
