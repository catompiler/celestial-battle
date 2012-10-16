#include "transformstree.h"
#include <algorithm>
#include <utility>
#include "utils/utils.h"
#include "config/config.h"

ENGINE_NAMESPACE_BEGIN


Transformation::Transformation(TransformsTree* creator_,
                                       const std::string& name_)
        : Component(creator_, name_)
{
    _transforms = new Transforms;
}

Transformation::~Transformation()
{
    delete _transforms;
}

const vec3_t& Transformation::localPosition() const
{
    return _local_transform.position;
}

void Transformation::setLocalPosition(const vec3_t& local_position_)
{
    Transform local = _local_transform;
    local.position = local_position_;
    setLocalTransform(local);
}

const quat_t& Transformation::localRotation() const
{
    return _local_transform.rotation;
}

void Transformation::setLocalRotation(const quat_t& local_rotation_)
{
    Transform local = _local_transform;
    local.rotation = local_rotation_;
    setLocalTransform(local);
}

const vec3_t& Transformation::localScaling() const
{
    return _local_transform.scaling;
}

void Transformation::setLocalScaling(const vec3_t& local_scaling_)
{
    Transform local = _local_transform;
    local.scaling = local_scaling_;
    setLocalTransform(local);
}

const Transform& Transformation::localTransform() const
{
    return _local_transform;
}

void Transformation::setLocalTransform(const Transform& local_transform_)
{
    Transform parent_transform = parentTransform();
    _local_transform = local_transform_;
    _world_transform = parent_transform + _local_transform;
}

const vec3_t& Transformation::worldPosition() const
{
    return _world_transform.position;
}

void Transformation::setWorldPosition(const vec3_t& world_position_)
{
    Transform world = _world_transform;
    world.position = world_position_;
    setWorldTransform(world);
}

const quat_t& Transformation::worldRotation() const
{
    return _world_transform.rotation;
}

void Transformation::setWorldRotation(const quat_t& world_rotation_)
{
    Transform world = _world_transform;
    world.rotation = world_rotation_;
    setWorldTransform(world);
}

const vec3_t& Transformation::worldScaling() const
{
    return _world_transform.scaling;
}

void Transformation::setWorldScaling(const vec3_t& world_scaling_)
{
    Transform world = _world_transform;
    world.scaling = world_scaling_;
    setWorldTransform(world);
}

const Transform& Transformation::worldTransform() const
{
    return _world_transform;
}

void Transformation::setWorldTransform(const Transform& world_transform_)
{
    Transform parent_transform = parentTransform();
    _world_transform = world_transform_;
    _local_transform = _world_transform - parent_transform;
}

const Transform& Transformation::parentTransform() const
{
    if(_parent_transform.dirty){
        _parent_transform.value = _world_transform - _local_transform;
        _parent_transform.dirty = false;
    }
    return _parent_transform.value;
}

void Transformation::setParentTransform(const Transform& transform_)
{
    if(_parent_transform.dirty || _parent_transform.value != transform_){
        _world_transform = transform_ + _local_transform;
        _parent_transform.value = transform_;
        _parent_transform.dirty = false;
    }
}

void Transformation::addTransform(TransformType type_, const Transform& transform_)
{
    _transforms->push_back(std::make_pair(type_, transform_));
}

void Transformation::update()
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



TransformsTree::TransformNode::TransformNode(TransformsTree* creator_,
                                             const std::string& name_)
        :Tree::Node<TransformNode>()
{
    _component = new Transformation(creator_, name_);
}

TransformsTree::TransformNode::~TransformNode()
{
    if(_parent) _parent->_removeChild(this, false);
    for(Childs::iterator it = _childs->begin(); it != _childs->end(); ++ it){
        (*it)->_setParent(_parent, false, true);
    }
    delete _component;
}

Transformation* TransformsTree::TransformNode::component()
{
    return _component;
}

const Transformation* TransformsTree::TransformNode::component() const
{
    return _component;
}


const ComponentFactory::parameterid_t TransformsTree::LOCAL_POSITION = 0;
const ComponentFactory::parameterid_t TransformsTree::LOCAL_ROTATION = 1;
const ComponentFactory::parameterid_t TransformsTree::LOCAL_SCALING = 2;
const ComponentFactory::parameterid_t TransformsTree::WORLD_POSITION = 3;
const ComponentFactory::parameterid_t TransformsTree::WORLD_ROTATION = 4;
const ComponentFactory::parameterid_t TransformsTree::WORLD_SCALING = 5;
const ComponentFactory::parameterid_t TransformsTree::PARENT = 6;


const std::string TransformsTree::root_node_name = std::string();

TransformsTree::TransformsTree()
        :ComponentFactory()
{
    _components = new Components;
    _addRootNode();
}

TransformsTree::~TransformsTree()
{
    std::for_each(iterators::MapValueIterator<Components> (_components->begin()),
                  iterators::MapValueIterator<Components> (_components->end()),
                  functors::delete_single());
    delete _components;
}

Transformation* TransformsTree::createComponent(const std::string& name_)
{
    TransformNode* node = _addNode(name_);
    if(node) return node->component();
    return NULL;
}

Transformation* TransformsTree::createComponent(const std::string& name_,
                                                const std::string& parent_name_)
{
    TransformNode* node = _addNode(name_, _getNode(parent_name_));
    if(node) return node->component();
    return NULL;
}

Transformation* TransformsTree::createComponent(const std::string& name_,
                                                    const ParametersList& parameters_)
{
    Transformation* component = createComponent(name_);
    if(component){
        _setParameters(component, parameters_);
    }
    return component;
}

Transformation* TransformsTree::createComponent(const std::string& name_,
                                                    const std::string& parent_name_,
                                                    const ParametersList& parameters_)
{
    Transformation* component = createComponent(name_, parent_name_);
    if(component){
        _setParameters(component, parameters_);
    }
    return component;
}

Transformation* TransformsTree::getComponent(const std::string& name_)
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

void TransformsTree::_addRootNode()
{
    _root = new TransformNode(this, root_node_name);
    _components->insert(std::make_pair(root_node_name, _root));
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
        TransformNode* node = new TransformNode(this, name_);
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

void TransformsTree::_setParameters(Transformation* component_,
                                    const ParametersList& parameters_)
{
    for(ParametersList::const_iterator it = parameters_.begin();
            it != parameters_.end(); ++ it){
        _setParameter(component_, (*it).first, (*it).second);
    }
}

void TransformsTree::_setParameter(Transformation* component_,
                                   const parameterid_t& parameter_,
                                   const ParameterValue& value_)
{
    try{
        /*if(parameter_ == local_position){
            component_->setLocalPosition(value_.get<vec3_t>());
        }else if(parameter_ == local_rotation){
            component_->setLocalRotation(value_.get<quat_t>());
        }else if(parameter_ == local_scaling){
            component_->setLocalScaling(value_.get<vec3_t>());
        }else if(parameter_ == world_position){
            component_->setWorldPosition(value_.get<vec3_t>());
        }else if(parameter_ == world_rotation){
            component_->setWorldRotation(value_.get<quat_t>());
        }else if(parameter_ == world_scaling){
            component_->setWorldScaling(value_.get<vec3_t>());
        }*/
        switch(parameter_){
            case LOCAL_POSITION:
                component_->setLocalPosition(value_.get<vec3_t>());
                break;
            case LOCAL_ROTATION:
                component_->setLocalRotation(value_.get<quat_t>());
                break;
            case LOCAL_SCALING:
                component_->setLocalScaling(value_.get<vec3_t>());
                break;
            case WORLD_POSITION:
                component_->setWorldPosition(value_.get<vec3_t>());
                break;
            case WORLD_ROTATION:
                component_->setWorldRotation(value_.get<quat_t>());
                break;
            case WORLD_SCALING:
                component_->setWorldScaling(value_.get<vec3_t>());
                break;
            case PARENT:
                setParent(component_->name(), value_.get<std::string>());
                break;
        }
    }catch(...){
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

Transformation* TransformsTree::ComponentsIterator::operator*()
{
    return (*_it).second->component();
}



ENGINE_NAMESPACE_END
