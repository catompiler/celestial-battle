#ifndef _ENTITY_H
#define _ENTITY_H

#include "object/object.h"
//#include "glmath/glmath.h"
#include <string>


class Entity
    :public Object
{
public:
    Entity(const std::string& name_ = std::string(), Entity* parent_ = NULL);
    ~Entity();

    const std::string& name() const;

    Entity* parent();
    const Entity* parent() const;
    void setParent(Entity* parent_);

protected:
    Entity* _parent;
    std::string _name;
};

#endif  //_ENTITY_H
