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

/*
class TransformComponent
        :public Component
{
public:
    TransformComponent(const std::string& name_ = std::string());
    ~TransformComponent();
    
    const Transform& localTransform() const;
    void setLocalTransform(const Transform& local_transform_);
    
    const Transform& worldTransform() const;
    void setWorldTransform(const Transform& world_transform_);
    
private:
    Transform _local_transform;
    Transform _world_transform;
};

class TransformsTree
        :public ComponentFactory
{
public:
    
    class TransformNode
        :public ::Node<TransformNode>
    {
    public:
        TransformNode(const std::string& name_ = std::string());
        ~TransformNode();
        
        TransformComponent* component();
        
    private:
        TransformComponent* _component;
    };
    
    
    typedef std::map<std::string, TransformNode*> Components;
    typedef std::list<TransformNode*> TransformNodes;
    //typedef iterators::MapValueIterator<Components, TransformComponent*> iterator;
    typedef TransformNodes::iterator iterator;
    
    TransformsTree();
    ~TransformsTree();
    
    TransformComponent* createComponent(const std::string& name_);
    TransformComponent* getComponent(const std::string& name_);
    bool destroyComponent(Component* component_);
    bool destroyComponent(const std::string& name_);
    
    bool setParent(const std::string& name_, const std::string& parent_name_);
    bool setParent(TransformComponent* component_, const std::string& parent_name_);
    bool setParent(TransformComponent* component_, TransformComponent* parent_component_);
    
    iterator componentsBegin();
    iterator componentsEnd();
    
private:
    
    Components* _components;
    TransformNodes* _nodes;
    
    TransformNode* _getComponent(const std::string& name_);
    void _addNode(TransformNode* node_);
    bool _delNode(TransformNode* node_);
    bool _reparentNode(TransformNode* node_, TransformNode* parent_);
};
*/



class TransformComponent
        :public Component
{
public:
    TransformComponent(const std::string& name_ = std::string());
    ~TransformComponent();
    
    const Transform& localTransform() const;
    void setLocalTransform(const Transform& local_transform_);
    
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
    
    class TransformNode
        :public Tree::Node<TransformNode>
    {
    public:
        TransformNode(const std::string& name_ = std::string());
        ~TransformNode();
        
        TransformComponent* component();
        const TransformComponent* component() const;
        
    private:
        TransformComponent* _component;
    };
    
//    struct NodeLessCmp{
//        bool operator()(const TransformNode*
//                        node1_, const TransformNode* node2_) const
//        {
//            return node1_->component()->name() < node2_->component()->name();
//        }
//    };
    
    
    typedef std::map<std::string, TransformNode*> Components;
    
    
    class ComponentsIterator
    :public std::iterator<std::bidirectional_iterator_tag, TransformComponent*>
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

        TransformComponent* operator*();

    private:
        Components::iterator _it;
    };
    
    typedef ComponentsIterator iterator;
    //typedef Components::iterator iterator;
    //typedef TransformNode::tree_iterator iterator;
    
    TransformsTree();
    ~TransformsTree();
    
    TransformComponent* createComponent(const std::string& name_);
    TransformComponent* createComponent(const std::string& name_,
                                        const std::string& parent_name_);
    TransformComponent* getComponent(const std::string& name_);
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
    
    TransformNode* _getNode(const std::string& name_);
    TransformNode* _addNode(const std::string& name_);
    TransformNode* _addNode(const std::string& name_, TransformNode* parent_node_);
    bool _delNode(const std::string& name_);
    
};



ENGINE_NAMESPACE_END

#endif  //_TRANSFORMATIONSTREE_H_
