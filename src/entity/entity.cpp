#include "entity.h"

Entity::Entity(const std::string& name_, Entity* parent_)
    :Object()
{
    _name = name_;
    _parent = parent_;
}

Entity::~Entity()
{
}

const std::string& Entity::name() const
{
    return _name;
}

Entity* Entity::parent()
{
    return _parent;
}

const Entity* Entity::parent() const
{
    return _parent;
}

void Entity::setParent(Entity* parent_)
{
    _parent = parent_;
}
