#include "transformstree.h"
#include <algorithm>
#include <utility>
#include "utils/utils.h"

ENGINE_NAMESPACE_BEGIN


TransformComponent::TransformComponent(const std::string& name_)
        : Component(name_)
{
    _transforms = new Transforms;
}

TransformComponent::~TransformComponent()
{
    delete _transforms;
}

const vec3_t& TransformComponent::localPosition() const
{
    return _local_transform.position;
}

void TransformComponent::setLocalPosition(const vec3_t& local_position_)
{
    Transform local = _local_transform;
    local.position = local_position_;
    setLocalTransform(local);
}

const quat_t& TransformComponent::localRotation() const
{
    return _local_transform.rotation;
}

void TransformComponent::setLocalRotation(const quat_t& local_rotation_)
{
    Transform local = _local_transform;
    local.rotation = local_rotation_;
    setLocalTransform(local);
}

const vec3_t& TransformComponent::localScaling() const
{
    return _local_transform.scaling;
}

void TransformComponent::setLocalScaling(const vec3_t& local_scaling_)
{
    Transform local = _local_transform;
    local.scaling = local_scaling_;
    setLocalTransform(local);
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

const vec3_t& TransformComponent::worldPosition() const
{
    return _world_transform.position;
}

void TransformComponent::setWorldPosition(const vec3_t& world_position_)
{
    Transform world = _world_transform;
    world.position = world_position_;
    setWorldTransform(world);
}

const quat_t& TransformComponent::worldRotation() const
{
    return _world_transform.rotation;
}

void TransformComponent::setWorldRotation(const quat_t& world_rotation_)
{
    Transform world = _world_transform;
    world.rotation = world_rotation_;
    setWorldTransform(world);
}

const vec3_t& TransformComponent::worldScaling() const
{
    return _world_transform.scaling;
}

void TransformComponent::setWorldScaling(const vec3_t& world_scaling_)
{
    Transform world = _world_transform;
    world.scaling = world_scaling_;
    setWorldTransform(world);
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

TransformComponent* TransformsTree::createComponent(const std::string& name_,
                                                    const ParametersList& parameters_)
{
    TransformComponent* component = createComponent(name_);
    if(component){
        for(ParametersList::const_iterator it = parameters_.begin();
                it != parameters_.end(); ++ it){
            _setParameter(component, (*it).first, (*it).second);
        }
    }
    return component;
}

TransformComponent* TransformsTree::createComponent(const std::string& name_,
                                                    const std::string& parent_name_,
                                                    const ParametersList& parameters_)
{
    TransformComponent* component = createComponent(name_, parent_name_);
    if(component){
        for(ParametersList::const_iterator it = parameters_.begin();
                it != parameters_.end(); ++ it){
            _setParameter(component, (*it).first, (*it).second);
        }
    }
    return component;
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

void TransformsTree::_setParameter(TransformComponent* component_, const std::string& parameter_,
                                   const ParameterValue& value_)
{
    if(parameter_ == "local_pos"){
        try{
            component_->setLocalPosition(value_.get<vec3_t>());
        }catch(...){
        }
    }else if(parameter_ == "local_rot"){
        try{
            component_->setLocalRotation(value_.get<quat_t>());
        }catch(...){
        }
    }else if(parameter_ == "local_scale"){
        try{
            component_->setLocalScaling(value_.get<vec3_t>());
        }catch(...){
        }
    }else if(parameter_ == "world_pos"){
        try{
            component_->setWorldPosition(value_.get<vec3_t>());
        }catch(...){
        }
    }else if(parameter_ == "world_rot"){
        try{
            component_->setWorldRotation(value_.get<quat_t>());
        }catch(...){
        }
    }else if(parameter_ == "world_scale"){
        try{
            component_->setWorldScaling(value_.get<vec3_t>());
        }catch(...){
        }
    }
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
