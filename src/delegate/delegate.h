#ifndef _DELEGATE_H
#define _DELEGATE_H

#include <functional>

template<class Ret>
class delegate
    :public std::unary_function<void, Ret>
{
public:
    
    template<class T>
    delegate(T* obj_, Ret (T::*func_)()){
        _obj = reinterpret_cast<Obj*>(obj_);
        _func = reinterpret_cast<Function>(func_);
    }
    
    Ret operator()() const{
        return (_obj->*_func)();
    }
    
private:
    struct Obj{};
    typedef Ret (Obj::*Function)();
    
    Function _func;
    Obj* _obj;
};

template<class Arg1, class Ret>
class unary_delegate
    :public std::unary_function<Arg1, Ret>
{
public:
    
    template<class T>
    unary_delegate(T* obj_, Ret (T::*func_)(Arg1)){
        _obj = reinterpret_cast<Obj*>(obj_);
        _ufunc = reinterpret_cast<Function>(func_);
    }
    
    Ret operator()(Arg1 arg1) const{
        return (_obj->*_ufunc)(arg1);
    }
    
private:
    struct Obj{};
    typedef Ret (Obj::*Function)(Arg1);
    
    Function _ufunc;
    Obj* _obj;
};

template<class Arg1, class Arg2, class Ret>
class binary_delegate
    :public std::binary_function<Arg1, Arg2, Ret>
{
public:
    
    template<class T>
    binary_delegate(T* obj_, Ret (T::*func_)(Arg1, Arg2)){
        _obj = reinterpret_cast<Obj*>(obj_);
        _bfunc = reinterpret_cast<Function>(func_);
    }
    
    Ret operator()(Arg1 arg1, Arg2 arg2) const{
        return (_obj->*_bfunc)(arg1, arg2);
    }
    
private:
    struct Obj{};
    typedef Ret (Obj::*Function)(Arg1, Arg2);
    
    Function _bfunc;
    Obj* _obj;
};

template<class T, class Ret>
delegate<Ret> make_delegate(T* obj_, Ret (T::*func_)())
{
    return delegate<Ret>(obj_, func_);
}

template<class T, class Arg1, class Ret>
unary_delegate<Arg1, Ret> make_delegate(T* obj_, Ret (T::*func_)(Arg1))
{
    return unary_delegate<Arg1, Ret>(obj_, func_);
}

template<class T, class Arg1, class Arg2, class Ret>
binary_delegate<Arg1, Arg2, Ret> make_delegate(T* obj_, Ret (T::*func_)(Arg1, Arg2))
{
    return binary_delegate<Arg1, Arg2, Ret>(obj_, func_);
}

#endif  //_DELEGATE_H
