#ifndef _EVENT_H
#define _EVENT_H

#include "delegate/delegate.h"
#include <list>
#include <algorithm>


template<class HandlerDelegate>
class BaseEvent
{
public:
    
    typedef HandlerDelegate delegate_t;
    
    BaseEvent();
    virtual ~BaseEvent();
    
    bool addHandler(const HandlerDelegate& delegate_);
    bool removeHandler(const HandlerDelegate& delegate_);
    template<class Handler>
        bool removeHandler(const Handler* handler_);
    template<class Handler, class Function>
        bool removeHandler(const Handler* handler_, Function func_);
protected:
    typedef std::list<HandlerDelegate> DelegateList;
    DelegateList _delegate_list;
};

class Event
    :public BaseEvent<Delegate<void> >
{
public:
    
    typedef BaseEvent<Delegate<void> > Base;
    
    Event();
    ~Event();
    
    void operator()();
};

template<class Arg>
class UnaryEvent
    :public BaseEvent<UnaryDelegate<Arg, void> >
{
public:
    
    typedef BaseEvent<UnaryDelegate<Arg, void> > Base;
    
    UnaryEvent();
    ~UnaryEvent();
    
    void operator()(const Arg& arg_);
};

template<class Arg1, class Arg2>
class BinaryEvent
    :public BaseEvent<BinaryDelegate<Arg1, Arg2, void> >
{
public:
    
    typedef BaseEvent<BinaryDelegate<Arg1, Arg2, void> > Base;
    
    BinaryEvent();
    ~BinaryEvent();
    
    void operator()(const Arg1& arg1_, const Arg2& arg2_);
};


template<class HandlerDelegate>
BaseEvent<HandlerDelegate>::BaseEvent()
{
}

template<class HandlerDelegate>
BaseEvent<HandlerDelegate>::~BaseEvent()
{
}

template<class HandlerDelegate>
bool BaseEvent<HandlerDelegate>::addHandler(const HandlerDelegate& delegate_)
{
    if(std::find(_delegate_list.begin(), _delegate_list.end(), delegate_)
            != _delegate_list.end()){
        return false;
    }
    _delegate_list.push_back(delegate_);
    return true;
}

template<class HandlerDelegate>
bool BaseEvent<HandlerDelegate>::removeHandler(const HandlerDelegate& delegate_)
{
    typename DelegateList::iterator it = std::find(_delegate_list.begin(),
                                            _delegate_list.end(), delegate_);
    if(it == _delegate_list.end()){
        return false;
    }
    _delegate_list.erase(it);
    return true;
}

template<class HandlerDelegate>
template<class Handler>
bool BaseEvent<HandlerDelegate>::removeHandler(const Handler* handler_)
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

template<class HandlerDelegate>
template<class Handler, class Function>
bool BaseEvent<HandlerDelegate>::removeHandler(const Handler* handler_, Function func_)
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


template<class Arg>
UnaryEvent<Arg>::UnaryEvent()
{
}

template<class Arg>
UnaryEvent<Arg>::~UnaryEvent()
{
}

template<class Arg>
void UnaryEvent<Arg>::operator()(const Arg& arg_)
{
    for(typename Base::DelegateList::iterator it = Base::_delegate_list.begin();
            it != Base::_delegate_list.end(); ++it){
        (*it)(arg_);
    }
}


template<class Arg1, class Arg2>
BinaryEvent<Arg1, Arg2>::BinaryEvent()
{
}

template<class Arg1, class Arg2>
BinaryEvent<Arg1, Arg2>::~BinaryEvent()
{
}

template<class Arg1, class Arg2>
void BinaryEvent<Arg1, Arg2>::operator()(const Arg1& arg1_, const Arg2& arg2_)
{
    for(typename Base::DelegateList::iterator it = Base::_delegate_list.begin();
            it != Base::_delegate_list.end(); ++it){
        (*it)(arg1_, arg2_);
    }
}

#endif  //_EVENT_H
