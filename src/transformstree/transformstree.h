#ifndef _TRANSFORMATIONSTREE_H_
#define _TRANSFORMATIONSTREE_H_

#include "engine/engine.h"
#include "component/component.h"
#include "component/componentfactory.h"
#include "transform/transform.h"
#include "tree/tree_node.h"
#include <string>
#include <list>


ENGINE_NAMESPACE_BEGIN


class TransformsTree;

class Transformation
        :public Component
{
public:
    Transformation(TransformsTree* creator_,
                       const std::string& name_ = std::string());
    ~Transformation();
    
    const vec3_t& localPosition() const;
    void setLocalPosition(const vec3_t& local_position_);
    
    const quat_t& localRotation() const;
    void setLocalRotation(const quat_t& local_rotation_);
    
    const vec3_t& localScaling() const;
    void setLocalScaling(const vec3_t& local_scaling_);
    
    const Transform& localTransform() const;
    void setLocalTransform(const Transform& local_transform_);
        
    const vec3_t& worldPosition() const;
    void setWorldPosition(const vec3_t& world_position_);
    
    const quat_t& worldRotation() const;
    void setWorldRotation(const quat_t& world_rotation_);
    
    const vec3_t& worldScaling() const;
    void setWorldScaling(const vec3_t& world_scaling_);
    
    const Transform& worldTransform() const;
    void setWorldTransform(const Transform& world_transform_);
    
    const Transform& parentTransform() const;
    void setParentTransform(const Transform& transform_);
    
    enum TransformType{LOCAL=0, WORLD};
    
    void addTransform(TransformType type_, const Transform& transform_);
    
    void update();
    
private:
    Transform _local_transform;
    Transform _world_transform;
    
    mutable DirtyValue<Transform> _parent_transform;
    
    typedef std::list<std::pair<TransformType, Transform> > Transforms;
    Transforms* _transforms;
};

class TransformsTree
        :public ComponentFactory
{
public:
    
    static const parameterid_t LOCAL_POSITION;
    static const parameterid_t LOCAL_ROTATION;
    static const parameterid_t LOCAL_SCALING;
    static const parameterid_t WORLD_POSITION;
    static const parameterid_t WORLD_ROTATION;
    static const parameterid_t WORLD_SCALING;
    static const parameterid_t PARENT;

    class TransformNode
        :public Tree::Node<TransformNode>
    {
    public:
        TransformNode(TransformsTree* creator_,
                      const std::string& name_ = std::string());
        ~TransformNode();
        
        Transformation* component();
        const Transformation* component() const;
        
    private:
        Transformation* _component;
    };
    
    
    typedef std::map<std::string, TransformNode*> Components;
    
    
    class ComponentsIterator
    :public std::iterator<std::bidirectional_iterator_tag, Transformation*>
    {
    public:
        ComponentsIterator();
        ComponentsIterator(Components::iterator it_);
        ComponentsIterator(const ComponentsIterator& iter_);
        ~ComponentsIterator();

        ComponentsIterator& operator=(const ComponentsIterator& iter_);

        ComponentsIterator& operator++();
        ComponentsIterator operator++(int);
        ComponentsIterator& operator--();
        ComponentsIterator operator--(int);

        bool operator==(const ComponentsIterator& iter_) const;
        bool operator!=(const ComponentsIterator& iter_) const;

        Transformation* operator*();

    private:
        Components::iterator _it;
    };
    
    typedef ComponentsIterator iterator;
    //typedef Components::iterator iterator;
    //typedef TransformNode::tree_iterator iterator;
    
    TransformsTree();
    ~TransformsTree();
    
    Transformation* createComponent(const std::string& name_);
    Transformation* createComponent(const std::string& name_,
                                     const std::string& parent_name_);    
    Transformation* createComponent(const std::string& name_,
                                     const ParametersList& parameters_);
    Transformation* createComponent(const std::string& name_,
                                     const std::string& parent_name_,
                                     const ParametersList& parameters_);
    
    Transformation* createComponent(const std::string& name_,
                                     Transformation* transformation_){
        return createComponent(name_);
    }
    Transformation* createComponent(const std::string& name_,
                                     Transformation* transformation_,
                                     const ParametersList& parameters_){
        return createComponent(name_, parameters_);
    }
    
    Transformation* getComponent(const std::string& name_);
    bool destroyComponent(Component* component_);
    bool destroyComponent(const std::string& name_);
    
    bool setParent(const std::string& name_, const std::string& parent_name_);
    
    iterator componentsBegin();
    iterator componentsEnd();
    
    void update();
    
private:
    
    static const std::string root_node_name;
    
    TransformNode* _root;
    Components* _components;
    
    void _addRootNode();
    TransformNode* _getNode(const std::string& name_);
    TransformNode* _addNode(const std::string& name_);
    TransformNode* _addNode(const std::string& name_, TransformNode* parent_node_);
    bool _delNode(const std::string& name_);
    
    void _setParameters(Transformation* component_, const ParametersList& parameters_);
    void _setParameter(Transformation* component_, const parameterid_t& parameter_,
                       const ParameterValue& value_);
    
};



ENGINE_NAMESPACE_END

#endif  //_TRANSFORMATIONSTREE_H_
