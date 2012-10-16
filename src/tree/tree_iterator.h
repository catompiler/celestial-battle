#ifndef _TREE_ITERATOR_H_
#define _TREE_ITERATOR_H_


#include <stack>
#include <iterator>
#include <utility>

namespace Tree{


template <class Node>
class iterator
    :public std::iterator<std::forward_iterator_tag, Node*>
{
public:
    iterator();
    iterator(Node* node_);
    iterator(const iterator& tree_iter_);
    ~iterator();
    
    iterator& operator=(const iterator& tree_iter_);
    bool operator==(const iterator& tree_iter_) const;
    bool operator!=(const iterator& tree_iter_) const;
    iterator& operator++();
    iterator operator++(int);
    Node*& operator*();
    
private:
    typedef typename Node::childs_iterator node_childs_iterator;
    
    struct State{
        State(){
            node = NULL;
        }
        State(node_childs_iterator nci_, Node* n_){
            node_childs_iter = nci_;
            node = n_;
        }
        State(const State& state_){
            (*this) = state_;
        }
        State& operator=(const State& state_){
            node_childs_iter = state_.node_childs_iter;
            node = state_.node;
            return *this;
        }
        bool operator==(const State& state_) const{
            return node_childs_iter == state_.node_childs_iter &&
                   node == state_.node;
        }
        node_childs_iterator node_childs_iter;
        Node* node;
    };
    
    State _state;
    
    typedef std::stack<State> Stack;
    Stack _stack;
    
    void _pushState();
    bool _popState();
};


template <class Node>
iterator<Node>::iterator()
{
}

template <class Node>
iterator<Node>::iterator(Node* node_)
{
    _state.node = node_;
    _state.node_childs_iter = node_->childsBegin();
}

template <class Node>
iterator<Node>::iterator(const iterator& tree_iter_)
{
    (*this) = tree_iter_;
}

template <class Node>
iterator<Node>::~iterator()
{
}
   
template <class Node>
iterator<Node>& iterator<Node>::operator=(const iterator& tree_iter_)
{
    _state = tree_iter_._state;
    _stack = tree_iter_._stack;
    return *this;
}

template <class Node>
bool iterator<Node>::operator==(const iterator& tree_iter_) const
{
    return _state == tree_iter_._state && _stack == tree_iter_._stack;
}

template <class Node>
bool iterator<Node>::operator!=(const iterator& tree_iter_) const
{
    return !operator==(tree_iter_);
}

template <class Node>
iterator<Node>& iterator<Node>::operator++()
{
    if(_state.node_childs_iter != _state.node->childsEnd()){
        node_childs_iterator it = _state.node_childs_iter;
        ++ _state.node_childs_iter;
        _pushState();
        _state.node = *it;
        _state.node_childs_iter = _state.node->childsBegin();
    }else{
        if(_popState()){
            return operator++();
        }else{
            (*this) = iterator<Node>();
        }
    }
    return *this;
}

template <class Node>
iterator<Node> iterator<Node>::operator++(int)
{
    iterator<Node> res(*this);
    operator++();
    return res;
}

template <class Node>
Node*& iterator<Node>::operator*()
{
    return _state.node;
}

template <class Node>
void iterator<Node>::_pushState()
{
    _stack.push(_state);
}

template <class Node>
bool iterator<Node>::_popState()
{
    if(_stack.empty()) return false;
    _state = _stack.top();
    _stack.pop();
    return true;
}


}

#endif  //_TREE_ITERATOR_H_
