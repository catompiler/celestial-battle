#include "entity.h"
#include "config/config.h"
#include <algorithm>



ENGINE_NAMESPACE_BEGIN


Entity::Entity(const std::string& name_, const std::string& parent_name_)
    :Object()
{
    _name = name_;
    _parent_name = parent_name_;
}

Entity::~Entity()
{
}

const std::string& Entity::name() const
{
    return _name;
}

void Entity::setName(const std::string& name_)
{
    _name = name_;
}

const std::string& Entity::parentName() const
{
    return _parent_name;
}

void Entity::setParentName(const std::string& name_)
{
    _parent_name = name_;
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
    if(parent_ == this || parent_ == _parent) return;
    
    if(_parent != NULL){
        _parent->_removeChild(this, false);
    }
    
    _parent = parent_;
    
    if(parent_ != NULL){
        parent_->_addChild(this, false);
    }
}

void Entity::addChild(Entity* child_)
{
    _addChild(child_, true);
}

void Entity::removeChild(Entity* child_)
{
    _removeChild(child_, true);
}

void Entity::_addChild(Entity* child_, bool call_setParent)
{
    if(child_ == this || child_ == NULL) return;
    
    ChildList::iterator childit = std::find(_childs.begin(), _childs.end(), child_);
    if(childit == _childs.end()){
        _childs.push_back(child_);
        if(call_setParent) child_->setParent(this);
    }
}

void Entity::_removeChild(Entity* child_, bool call_setParent)
{
    ChildList::iterator childit = std::find(_childs.begin(), _childs.end(), child_);
    if(childit != _childs.end()){
        _childs.erase(childit);
        if(call_setParent) child_->setParent(NULL);
    }
}

bool Entity::hasChild(const Entity* child_) const
{
    return std::find(_childs.begin(), _childs.end(), child_) != _childs.end();
}

Entity::ChildsIterator Entity::childsBegin()
{
    return _childs.begin();
}

Entity::ChildsIterator Entity::childsEnd()
{
    return _childs.end();
}


ENGINE_NAMESPACE_END

