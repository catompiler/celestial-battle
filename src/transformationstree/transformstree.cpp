#include "transformstree.h"
#include <algorithm>
#include <utility>
#include "utils/utils.h"

ENGINE_NAMESPACE_BEGIN


/*
TransformComponent::TransformComponent(const std::string& name_)
        : Component(name_)
{
}

TransformComponent::~TransformComponent()
{
}

const Transform& TransformComponent::localTransform() const
{
    return _local_transform;
}

void TransformComponent::setLocalTransform(const Transform& local_transform_)
{
    _local_transform = local_transform_;
}

const Transform& TransformComponent::worldTransform() const
{
    return _world_transform;
}

void TransformComponent::setWorldTransform(const Transform& world_transform_)
{
    _world_transform = world_transform_;
}




TransformsTree::TransformNode::TransformNode(const std::string& name_)
        :TransformComponent(name_), ::Node<TransformNode>()
{
}

TransformsTree::TransformNode::~TransformNode()
{
    if(_parent) _parent->_removeChild(this, false);
    for(Childs::iterator it = _childs->begin(); it != _childs->end(); ++ it){
        (*it)->_setParent(_parent, false, true);
    }
}




TransformsTree::TransformsTree()
        :ComponentFactory()
{
    _components = new Components;
    _nodes = new TransformNodes;
}

TransformsTree::~TransformsTree()
{
    for(Components::iterator it = _components->begin(); it != _components->end(); ++ it){
        delete (*it).second;
    }
    delete _components;
    delete _nodes;
}

TransformComponent* TransformsTree::createComponent(const std::string& name_)
{
    Components::iterator it = _components->find(name_);
    if(it == _components->end()){
        TransformNode* n = new TransformNode(name_);
        _components->insert(std::make_pair(name_, n));
        _addNode(n);
        return n;
    }
    return NULL;
}

TransformComponent* TransformsTree::getComponent(const std::string& name_)
{
    return static_cast<TransformComponent*>(_getComponent(name_));
}

bool TransformsTree::destroyComponent(Component* component_)
{
    return destroyComponent(component_->name());
}

bool TransformsTree::destroyComponent(const std::string& name_)
{
    typename Components::iterator it = _components->find(name_);
    if(it != _components->end()){
        if(_delNode((*it).second)){
            _components->erase(it);
            return true;
        }
    }
    return false;
}

bool TransformsTree::setParent(const std::string& name_, const std::string& parent_name_)
{
    return _reparentNode(_getComponent(name_), _getComponent(parent_name_));
}

bool TransformsTree::setParent(TransformComponent* component_, const std::string& parent_name_)
{
    return _reparentNode(component_, _getComponent(parent_name_));
}

bool TransformsTree::setParent(TransformComponent* component_, TransformComponent* parent_component_)
{
    return _reparentNode(component_, parent_component_);
}

TransformsTree::iterator TransformsTree::componentsBegin()
{
    return iterator(_components->begin());
}

TransformsTree::iterator TransformsTree::componentsEnd()
{
    return iterator(_components->end());
}

TransformsTree::TransformNode* TransformsTree::_getComponent(const std::string& name_)
{
    Components::iterator it = _components->find(name_);
    if(it != _components->end()){
        return (*it).second;
    }
    return NULL;
}

void TransformsTree::_addNode(TransformNode* node_)
{
    _nodes->push_back(node_);
}

bool TransformsTree::_delNode(TransformNode* node_)
{
    TransformNodes::iterator it = std::find(_nodes->begin(), _nodes->end(), node_);
    if(it != _nodes->end()){
        delete (*it);
        _nodes->erase(it);
        return true;
    }
    return false;
}

bool TransformsTree::_reparentNode(TransformNode* node_, TransformNode* parent_)
{
    if(node_ == NULL) return false;
    
    TransformNodes::iterator childit = std::find(_nodes->begin(), _nodes->end(), node_);
    if(childit == _nodes->end()) return false;
    
    _nodes->erase(childit);
    
    if(parent_ == NULL){
        _nodes->insert(_nodes->begin(), node_);
    }else{
        TransformNodes::iterator parentit = std::find(_nodes->begin(), _nodes->end(), parent_);
        if(parentit != _nodes->end()){
            ++parentit;
        }else{
            parentit = _nodes->begin();
            parent_ = NULL;
        }
        _nodes->insert(parentit, node_);
    }
    
    node_->setParent(parent_);
    
    return true;
}
*/



TransformComponent::TransformComponent(const std::string& name_)
        : Component(name_)
{
    _transforms = new Transforms;
}

TransformComponent::~TransformComponent()
{
    delete _transforms;
}

const Transform& TransformComponent::localTransform() const
{
    return _local_transform;
}

void TransformComponent::setLocalTransform(const Transform& local_transform_)
{
    Transform parent_transform = parentTransform();
    _local_transform = local_transform_;
    _world_transform = parent_transform + _local_transform;
}

const Transform& TransformComponent::worldTransform() const
{
    return _world_transform;
}

void TransformComponent::setWorldTransform(const Transform& world_transform_)
{
    Transform parent_transform = parentTransform();
    _world_transform = world_transform_;
    _local_transform = _world_transform - parent_transform;
}

const Transform& TransformComponent::parentTransform() const
{
    if(_parent_transform.dirty){
        _parent_transform.value = _world_transform - _local_transform;
        _parent_transform.dirty = false;
    }
    return _parent_transform.value;
}

void TransformComponent::setParentTransform(const Transform& transform_)
{
    if(_parent_transform.dirty || _parent_transform.value != transform_){
        _world_transform = transform_ + _local_transform;
        _parent_transform.value = transform_;
        _parent_transform.dirty = false;
    }
}

void TransformComponent::addTransform(TransformType type_, const Transform& transform_)
{
    _transforms->push_back(std::make_pair(type_, transform_));
}

void TransformComponent::update()
{
    if(_transforms->empty()) return;
    
    Transform parent_transform = parentTransform();
    
    for(Transforms::iterator it = _transforms->begin(); it != _transforms->end(); ++ it){
        if((*it).first == LOCAL){
            _local_transform += (*it).second;
            _world_transform = parent_transform + _local_transform;
        }else{
            _world_transform += (*it).second;
            _local_transform = _world_transform - parent_transform;
        }
    }
}



TransformsTree::TransformNode::TransformNode(const std::string& name_)
        :Tree::Node<TransformNode>()
{
    _component = new TransformComponent(name_);
}

TransformsTree::TransformNode::~TransformNode()
{
    if(_parent) _parent->_removeChild(this, false);
    for(Childs::iterator it = _childs->begin(); it != _childs->end(); ++ it){
        (*it)->_setParent(_parent, false, true);
    }
    delete _component;
}

TransformComponent* TransformsTree::TransformNode::component()
{
    return _component;
}

const TransformComponent* TransformsTree::TransformNode::component() const
{
    return _component;
}


const std::string TransformsTree::root_node_name = std::string();

TransformsTree::TransformsTree()
        :ComponentFactory()
{
    _components = new Components;
    _addNode(root_node_name);
}

TransformsTree::~TransformsTree()
{
    std::for_each(iterators::MapValueIterator<Components> (_components->begin()),
                  iterators::MapValueIterator<Components> (_components->end()),
                  functors::delete_single());
    delete _components;
}

TransformComponent* TransformsTree::createComponent(const std::string& name_)
{
    TransformNode* node = _addNode(name_);
    if(node) return node->component();
    return NULL;
}

TransformComponent* TransformsTree::createComponent(const std::string& name_,
                                                const std::string& parent_name_)
{
    TransformNode* node = _addNode(name_, _getNode(parent_name_));
    if(node) return node->component();
    return NULL;
}

TransformComponent* TransformsTree::getComponent(const std::string& name_)
{
    TransformNode* node = _getNode(name_);
    if(node) return node->component();
    return NULL;
}

bool TransformsTree::destroyComponent(Component* component_)
{
    return destroyComponent(component_->name());
}

bool TransformsTree::destroyComponent(const std::string& name_)
{
    return _delNode(name_);
}

bool TransformsTree::setParent(const std::string& name_, const std::string& parent_name_)
{
    Components::iterator it_child = _components->find(name_);
    if(it_child == _components->end()){
        return false;
    }
    
    Components::iterator it_parent = _components->find(parent_name_);
    if(it_parent == _components->end()){
        return false;
    }
    
    (*it_child).second->setParent((*it_parent).second);
    
    return true;
}

TransformsTree::iterator TransformsTree::componentsBegin()
{
    return ComponentsIterator(_components->begin());
}

TransformsTree::iterator TransformsTree::componentsEnd()
{
    return ComponentsIterator(_components->end());
}

void TransformsTree::update()
{
    for(TransformNode::tree_iterator it = _root->treeBegin(); it != _root->treeEnd(); ++it){
        if((*it)->parent()){
            (*it)->component()->setParentTransform((*it)->parent()->component()->worldTransform());
        }
        (*it)->component()->update();
    }
}

TransformsTree::TransformNode* TransformsTree::_getNode(const std::string& name_)
{
    Components::iterator it = _components->find(name_);
    if(it != _components->end()){
        return (*it).second;
    }
    return NULL;
}

TransformsTree::TransformNode* TransformsTree::_addNode(const std::string& name_)
{
//    if(_getNode(name_) == NULL){
//        TransformNode* node = new TransformNode(name_);
//        _components->insert(std::make_pair(name_, node));
//        _root->addChild(node);
//        return node;
//    }
//    return NULL;
    return _addNode(name_, NULL);
}

TransformsTree::TransformNode* TransformsTree::_addNode(const std::string& name_,
                                                TransformNode* parent_node_)
{
    if(_getNode(name_) == NULL){
        TransformNode* node = new TransformNode(name_);
        _components->insert(std::make_pair(name_, node));
        if(parent_node_){
            parent_node_->addChild(node);
        }else{
            _root->addChild(node);
        }
        return node;
    }
    return NULL;
}

bool TransformsTree::_delNode(const std::string& name_)
{
    Components::iterator it = _components->find(name_);
    if(it != _components->end()){
        delete (*it).second;
        _components->erase(it);
        return true;
    }
    return false;
}


TransformsTree::ComponentsIterator::ComponentsIterator()
{
}

TransformsTree::ComponentsIterator::ComponentsIterator(Components::iterator it_)
{
    _it = it_;
}

TransformsTree::ComponentsIterator::ComponentsIterator(const ComponentsIterator& iter_)
{
    operator=(iter_);
}

TransformsTree::ComponentsIterator::~ComponentsIterator()
{
}

TransformsTree::ComponentsIterator& TransformsTree::ComponentsIterator::operator=(const ComponentsIterator& iter_)
{
    _it = iter_._it;
    return *this;
}

TransformsTree::ComponentsIterator& TransformsTree::ComponentsIterator::operator++()
{
    _it ++;
    return *this;
}

TransformsTree::ComponentsIterator TransformsTree::ComponentsIterator::operator++(int)
{
    ComponentsIterator res(*this);
    operator++();
    return res;
}

TransformsTree::ComponentsIterator& TransformsTree::ComponentsIterator::operator--()
{
    _it --;
    return *this;
}

TransformsTree::ComponentsIterator TransformsTree::ComponentsIterator::operator--(int)
{
    ComponentsIterator res(*this);
    operator--();
    return res;
}

bool TransformsTree::ComponentsIterator::operator==(const ComponentsIterator& iter_) const
{
    return _it == iter_._it;
}

bool TransformsTree::ComponentsIterator::operator!=(const ComponentsIterator& iter_) const
{
    return !operator==(iter_);
}

TransformComponent* TransformsTree::ComponentsIterator::operator*()
{
    return (*_it).second->component();
}



ENGINE_NAMESPACE_END
