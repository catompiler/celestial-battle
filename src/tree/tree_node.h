#ifndef _NODE_H_
#define _NODE_H_

#include <list>
#include <algorithm>
#include "tree_iterator.h"


namespace Tree{


template <class T>
class Node{
public:
    
    typedef std::list<T*> Childs;
    typedef typename Childs::iterator childs_iterator;

    typedef iterator<T> tree_iterator;
    
    Node();
    
    virtual ~Node();
    
    T* parent();
    
    childs_iterator childsBegin();
    childs_iterator childsEnd();

    tree_iterator treeBegin();
    tree_iterator treeEnd();
    
    bool hasChilds() const;
    size_t childsCount() const;
    
    void setParent(T* parent_);
    void addChild(T* child_);
    void removeChild(T* child_);
    
protected:
    
    void _setParent(T* parent_, bool removechild_, bool addchild_);
    void _addChild(T* child_, bool setparent_);
    void _removeChild(T* child_, bool setparent_);
    
    T* _parent;
    Childs* _childs;
};


template <class T>
Node<T>::Node(){
    _childs = new Childs;
}

template <class T>
Node<T>::~Node(){
    delete _childs;
}

template <class T>
T* Node<T>::parent(){
    return _parent;
}

template <class T>
typename Node<T>::childs_iterator Node<T>::childsBegin(){
    return _childs->begin();
}

template <class T>
typename Node<T>::childs_iterator Node<T>::childsEnd(){
    return _childs->end();
}

template <class T>
typename Node<T>::tree_iterator Node<T>::treeBegin()
{
    return Node<T>::tree_iterator(static_cast<T*>(this));
}

template <class T>
typename Node<T>::tree_iterator Node<T>::treeEnd()
{
    return Node<T>::tree_iterator();
}

template <class T>
bool Node<T>::hasChilds() const
{
    return !_childs->empty();
}

template <class T>
size_t  Node<T>::childsCount() const
{
    return _childs->size();
}

template <class T>
void Node<T>::setParent(T* parent_){
    _setParent(parent_, true, true);
}

template <class T>
void Node<T>::addChild(T* child_){
    _addChild(child_, true);
}

template <class T>
void Node<T>::removeChild(T* child_){
    _removeChild(child_, true);
}

template <class T>
void Node<T>::_setParent(T* parent_, bool removechild_, bool addchild_){
    if(parent_ == this || parent_ == _parent) return;

    if(_parent && removechild_) _parent->_removeChild(static_cast<T*>(this), false);
    if(parent_ && addchild_) parent_->_addChild(static_cast<T*>(this), false);

    _parent = parent_;
}

template <class T>
void Node<T>::_addChild(T* child_, bool setparent_){
    typename Childs::iterator it = std::find(_childs->begin(), _childs->end(), child_);
    if(it == _childs->end()){
        _childs->push_back(child_);
        if(setparent_) child_->_setParent(static_cast<T*>(this), true, false);
    }
}

template <class T>
void Node<T>::_removeChild(T* child_, bool setparent_){
    typename Childs::iterator it = std::find(_childs->begin(), _childs->end(), child_);
    if(it != _childs->end()){
        _childs->erase(it);
        if(setparent_) child_->_setParent(NULL, false, false);
    }
}


}


#endif  //_NODE_H_
