#ifndef _DELEGATE_H
#define _DELEGATE_H

#include <functional>

template<class T, class Ret>
class delegate
    :public std::unary_function<void, Ret>
{
public:
    
    typedef Ret (T::*Function)();
    
    delegate(T* obj_, Function func_){
        _obj = obj_;
        _func = func_;
    }
    
    Ret operator()() const{
        return (_obj->*_func)();
    }
    
private:
    
    Function _func;
    T* _obj;
};

template<class T, class Arg1, class Ret>
class unary_delegate
    :public std::unary_function<Arg1, Ret>
{
public:
    
    typedef Ret (T::*UnaryFunction)(Arg1);
    
    unary_delegate(T* obj_, UnaryFunction func_){
        _obj = obj_;
        _ufunc = func_;
    }
    
    Ret operator()(Arg1 arg1) const{
        return (_obj->*_ufunc)(arg1);
    }
    
private:
    
    UnaryFunction _ufunc;
    T* _obj;
};

template<class T, class Arg1, class Arg2, class Ret>
class binary_delegate
    :public std::binary_function<Arg1, Arg2, Ret>
{
public:
    
    typedef Ret (T::*BinaryFunction)(Arg1, Arg2);
    
    binary_delegate(T* obj_, BinaryFunction func_){
        _obj = obj_;
        _bfunc = func_;
    }
    
    Ret operator()(Arg1 arg1, Arg2 arg2) const{
        return (_obj->*_bfunc)(arg1, arg2);
    }
    
private:
    
    BinaryFunction _bfunc;
    T* _obj;
};

template<class T, class Ret>
delegate<T, Ret> make_delegate(T* obj_, Ret (T::*func_)())
{
    return delegate<T, Ret>(obj_, func_);
}

template<class T, class Arg1, class Ret>
unary_delegate<T, Arg1, Ret> make_delegate(T* obj_, Ret (T::*func_)(Arg1))
{
    return unary_delegate<T, Arg1, Ret>(obj_, func_);
}

template<class T, class Arg1, class Arg2, class Ret>
binary_delegate<T, Arg1, Arg2, Ret> make_delegate(T* obj_, Ret (T::*func_)(Arg1, Arg2))
{
    return binary_delegate<T, Arg1, Arg2, Ret>(obj_, func_);
}

#endif  //_DELEGATE_H
