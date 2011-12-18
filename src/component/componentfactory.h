#ifndef _COMPONENTFACTORY_H_
#define _COMPONENTFACTORY_H_

#include "component.h"
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include "utils/utils.h"
#include "tlvariant/tlvariant.h"
#include "glmath/glmath.h"

ENGINE_NAMESPACE_BEGIN


class ComponentFactory
        :public ::Object
{
public:
    
    typedef tl::makeTypeList11<bool, int, float, std::string,
                             vec2_t, vec3_t, vec4_t, quat_t,
                             mat2_t, mat3_t, mat4_t>::value ParameterValueTypes;
    typedef TLVariant<ParameterValueTypes> ParameterValue;
    typedef int parameterid_t;
    typedef std::map<parameterid_t, ParameterValue> ParametersList;
    
    //ComponentFactory();
    virtual ~ComponentFactory(){};
    
    virtual Component* createComponent(const std::string& name_) = 0;
    virtual Component* createComponent(const std::string& name_,
                                       const ParametersList& parameters_) = 0;
    virtual Component* getComponent(const std::string& name_) = 0;
    virtual bool destroyComponent(Component* component_) = 0;
    virtual bool destroyComponent(const std::string& name_) = 0;
};


template<class T, class Factory = ComponentFactory>
class ComponentFactoryTmpl
        :public ComponentFactory
{
public:
    
    typedef std::map<std::string, T*> Components;
    typedef iterators::MapValueIterator<Components> iterator;
    
    ComponentFactoryTmpl();
    ~ComponentFactoryTmpl();
    
    T* createComponent(const std::string& name_);
    T* createComponent(const std::string& name_,
                       const ParametersList& parameters_);
    T* getComponent(const std::string& name_);
    bool destroyComponent(Component* component_);
    bool destroyComponent(const std::string& name_);
    
    iterator componentsBegin();
    iterator componentsEnd();
    
protected:
    
    Components* _components;
    
    virtual void _setParameter(T* component_, const parameterid_t& parameter_,
                               const ParameterValue& value_) = 0;
    
};


template<class T, class Factory>
ComponentFactoryTmpl<T, Factory>::ComponentFactoryTmpl()
        :ComponentFactory()
{
    _components = new Components;
}

template<class T, class Factory>
ComponentFactoryTmpl<T, Factory>::~ComponentFactoryTmpl()
{
    std::for_each(_components->begin(), _components->end(), functors::delete_single());
    delete _components;
}

template<class T, class Factory>
T* ComponentFactoryTmpl<T, Factory>::createComponent(const std::string& name_)
{
    typename Components::iterator it = _components->find(name_);
    if(it == _components->end()){
        T* c = new T(static_cast<Factory*>(this), name_);
        _components->insert(std::make_pair(name_, c));
        return c;
    }
    return NULL;
}

template<class T, class Factory>
T* ComponentFactoryTmpl<T, Factory>::createComponent(const std::string& name_,
                                            const ParametersList& parameters_)
{
    T* component = createComponent(name_);
    if(component){
        for(ParametersList::const_iterator it = parameters_.begin();
                it != parameters_.end(); ++ it){
            this->_setParameter(component, (*it).first, (*it).second);
        }
    }
    return component;
}

template<class T, class Factory>
T* ComponentFactoryTmpl<T, Factory>::getComponent(const std::string& name_)
{
    typename Components::iterator it = _components->find(name_);
    if(it != _components->end()){
        return (*it).second;
    }
    return NULL;
}

template<class T, class Factory>
bool ComponentFactoryTmpl<T, Factory>::destroyComponent(Component* component_)
{
    return destroyComponent(component_->name());
}

template<class T, class Factory>
bool ComponentFactoryTmpl<T, Factory>::destroyComponent(const std::string& name_)
{
    typename Components::iterator it = _components->find(name_);
    if(it != _components->end()){
        delete (*it).second;
        _components->erase(it);
        return true;
    }
    return false;
}

template<class T, class Factory>
typename ComponentFactoryTmpl<T, Factory>::iterator ComponentFactoryTmpl<T, Factory>::componentsBegin()
{
    return iterator(_components->begin());
}

template<class T, class Factory>
typename ComponentFactoryTmpl<T, Factory>::iterator ComponentFactoryTmpl<T, Factory>::componentsEnd()
{
    return iterator(_components->end());
}


ENGINE_NAMESPACE_END


#endif  //_COMPONENTFACTORY_H_
