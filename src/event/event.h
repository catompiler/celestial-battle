#ifndef _EVENT_H
#define _EVENT_H

#include "delegate/delegate.h"
#include <list>
#include <algorithm>
#include <utility>


//#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L


template <typename... Args>
class BaseEvent
{
public:
    
    typedef Delegate<void, Args...> delegate_t;
    
    BaseEvent();
    virtual ~BaseEvent();
    
    bool addHandler(const delegate_t& delegate_);
    bool removeHandler(const delegate_t& delegate_);
    template<class Handler>
        bool removeHandler(const Handler* handler_);
    template<class Handler, class Function>
        bool removeHandler(const Handler* handler_, Function func_);
    
protected:
    typedef std::list<delegate_t> DelegateList;
    DelegateList _delegate_list;
};



template <typename... Args>
class Event
    :public BaseEvent<Args...>
{
public:
    
    typedef BaseEvent<Args...> Base;
    
    Event();
    ~Event();
    
    void operator()(Args... args_);
};



template <typename Arg0>
using UnaryEvent = Event<Arg0>;

template <typename Arg0, typename Arg1>
using BinaryEvent = Event<Arg0, Arg1>;



template <typename... Args>
BaseEvent<Args...>::BaseEvent()
{
}

template <typename... Args>
BaseEvent<Args...>::~BaseEvent()
{
}

template <typename... Args>
bool BaseEvent<Args...>::addHandler(const delegate_t& delegate_)
{
    if(std::find(_delegate_list.begin(), _delegate_list.end(), delegate_)
            != _delegate_list.end()){
        return false;
    }
    _delegate_list.push_back(delegate_);
    return true;
}

template <typename... Args>
bool BaseEvent<Args...>::removeHandler(const delegate_t& delegate_)
{
    typename DelegateList::iterator it = std::find(_delegate_list.begin(),
                                            _delegate_list.end(), delegate_);
    if(it == _delegate_list.end()){
        return false;
    }
    _delegate_list.erase(it);
    return true;
}

template <typename... Args>
template <typename Handler>
bool BaseEvent<Args...>::removeHandler(const Handler* handler_)
{
    bool found = false;
    for(typename DelegateList::iterator it = _delegate_list.begin();
            it != _delegate_list.end();){
        
        if((*it).compareObject(handler_)){
            _delegate_list.erase(it++);
            found = true;
        }else{
            ++it;
        }
    }
    return found;
}

template <typename... Args>
template <typename Handler, typename Function>
bool BaseEvent<Args...>::removeHandler(const Handler* handler_, Function func_)
{
    for(typename DelegateList::iterator it = _delegate_list.begin();
            it != _delegate_list.end(); ++it){
        
        if((*it).compare(handler_, func_)){
            _delegate_list.erase(it);
            return true;
        }
    }
    return false;
}



template <typename... Args>
Event<Args...>::Event()
{
}

template <typename... Args>
Event<Args...>::~Event()
{
}

template <typename... Args>
void Event<Args...>::operator()(Args... args_)
{
    for(typename Base::DelegateList::iterator it = Base::_delegate_list.begin();
            it != Base::_delegate_list.end(); ++it){
        //(*it)(std::forward<Arg>(arg_));
        (*it)(args_...);
    }
}


#endif  //_EVENT_H
