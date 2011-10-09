#ifndef _COMPONENTFACTORY_H_
#define _COMPONENTFACTORY_H_

#include "component.h"
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include "utils/utils.h"

ENGINE_NAMESPACE_BEGIN


class ComponentFactory
        :public ::Object
{
public:
    //ComponentFactory();
    virtual ~ComponentFactory(){};
    
    virtual Component* createComponent(const std::string& name_) = 0;
    virtual Component* getComponent(const std::string& name_) = 0;
    virtual bool destroyComponent(Component* component_) = 0;
    virtual bool destroyComponent(const std::string& name_) = 0;
};


template<class T>
class ComponentFactoryTmpl
        :public ComponentFactory
{
public:
    
    typedef std::map<std::string, T*> Components;
    typedef iterators::MapValueIterator<Components> iterator;
    
    ComponentFactoryTmpl();
    ~ComponentFactoryTmpl();
    
    T* createComponent(const std::string& name_);
    T* getComponent(const std::string& name_);
    bool destroyComponent(Component* component_);
    bool destroyComponent(const std::string& name_);
    
    iterator componentsBegin();
    iterator componentsEnd();
    
protected:
    
    Components* _components;
    
};


template<class T>
ComponentFactoryTmpl<T>::ComponentFactoryTmpl()
        :ComponentFactory()
{
    _components = new Components;
}

template<class T>
ComponentFactoryTmpl<T>::~ComponentFactoryTmpl()
{
    std::for_each(_components->begin(), _components->end(), functors::delete_single());
    delete _components;
}

template<class T>
T* ComponentFactoryTmpl<T>::createComponent(const std::string& name_)
{
    typename Components::iterator it = _components->find(name_);
    if(it == _components->end()){
        T* c = new T(name_);
        _components->insert(std::make_pair(name_, c));
        return c;
    }
    return NULL;
}

template<class T>
T* ComponentFactoryTmpl<T>::getComponent(const std::string& name_)
{
    typename Components::iterator it = _components->find(name_);
    if(it != _components->end()){
        return (*it).second;
    }
    return NULL;
}

template<class T>
bool ComponentFactoryTmpl<T>::destroyComponent(Component* component_)
{
    return destroyComponent(component_->name());
}

template<class T>
bool ComponentFactoryTmpl<T>::destroyComponent(const std::string& name_)
{
    typename Components::iterator it = _components->find(name_);
    if(it != _components->end()){
        delete (*it).second;
        _components->erase(it);
        return true;
    }
    return false;
}

template<class T>
typename ComponentFactoryTmpl<T>::iterator ComponentFactoryTmpl<T>::componentsBegin()
{
    return iterator(_components->begin());
}

template<class T>
typename ComponentFactoryTmpl<T>::iterator ComponentFactoryTmpl<T>::componentsEnd()
{
    return iterator(_components->end());
}


ENGINE_NAMESPACE_END


#endif  //_COMPONENTFACTORY_H_
