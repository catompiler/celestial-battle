#ifndef _DELEGATE_H
#define _DELEGATE_H

#include <functional>
#include <stddef.h>

template<class Ret>
class Delegate
    :public std::unary_function<void, Ret>
{
public:
    
    Delegate(){
        _obj = NULL;
        _func = NULL;
    }
    
    template<class T>
    Delegate(T* obj_, Ret (T::*func_)()){
        _obj = reinterpret_cast<Obj*>(obj_);
        _func = reinterpret_cast<Function>(func_);
    }
    
    operator bool() const{
        return _obj != NULL;
    }
    
    Ret operator()() const{
        return (_obj->*_func)();
    }
    
    bool operator==(const Delegate& delegate_) const{
        return _obj == reinterpret_cast<Obj*>(delegate_._obj) &&
        _func == reinterpret_cast<Function>(delegate_._func);
    }
    
    template<class T>
    bool compareObject(const T* obj_) const{
        return _obj == reinterpret_cast<const Obj*>(obj_);
    }
    
    template<class T>
    bool compare(const T* obj_, Ret (T::*func_)()) const{
        return _obj == reinterpret_cast<const Obj*>(obj_) &&
        _func == reinterpret_cast<Function>(func_);
    }
    
private:
    struct Obj{};
    typedef Ret (Obj::*Function)();
    
    Function _func;
    Obj* _obj;
};

template<class Arg1, class Ret>
class UnaryDelegate
    :public std::unary_function<Arg1, Ret>
{
public:
    
    UnaryDelegate(){
        _obj = NULL;
        _func = NULL;
    }
    
    template<class T>
    UnaryDelegate(T* obj_, Ret (T::*func_)(Arg1)){
        _obj = reinterpret_cast<Obj*>(obj_);
        _func = reinterpret_cast<Function>(func_);
    }
    
    operator bool() const{
        return _obj != NULL;
    }
    
    Ret operator()(Arg1 arg1) const{
        return (_obj->*_func)(arg1);
    }
    
    bool operator==(const UnaryDelegate& delegate_) const{
        return _obj == reinterpret_cast<Obj*>(delegate_._obj) &&
        _func == reinterpret_cast<Function>(delegate_._func);
    }
    
    template<class T>
    bool compareObject(const T* obj_) const{
        return _obj == reinterpret_cast<const Obj*>(obj_);
    }
    
    template<class T>
    bool compare(const T* obj_, Ret (T::*func_)(Arg1)) const{
        return _obj == reinterpret_cast<const Obj*>(obj_) &&
        _func == reinterpret_cast<Function>(func_);
    }
    
private:
    struct Obj{};
    typedef Ret (Obj::*Function)(Arg1);
    
    Function _func;
    Obj* _obj;
};

template<class Arg1, class Arg2, class Ret>
class BinaryDelegate
    :public std::binary_function<Arg1, Arg2, Ret>
{
public:
    
    BinaryDelegate(){
        _obj = NULL;
        _func = NULL;
    }
    
    template<class T>
    BinaryDelegate(T* obj_, Ret (T::*func_)(Arg1, Arg2)){
        _obj = reinterpret_cast<Obj*>(obj_);
        _func = reinterpret_cast<Function>(func_);
    }
    
    operator bool() const{
        return _obj != NULL;
    }
    
    Ret operator()(Arg1 arg1, Arg2 arg2) const{
        return (_obj->*_func)(arg1, arg2);
    }
    
    bool operator==(const BinaryDelegate& delegate_) const{
        return _obj == reinterpret_cast<Obj*>(delegate_._obj) &&
        _func == reinterpret_cast<Function>(delegate_._func);
    }
    
    template<class T>
    bool compareObject(const T* obj_) const{
        return _obj == reinterpret_cast<const Obj*>(obj_);
    }
    
    template<class T>
    bool compare(const T* obj_, Ret (T::*func_)(Arg1, Arg2)) const{
        return _obj == reinterpret_cast<const Obj*>(obj_) &&
        _func == reinterpret_cast<Function>(func_);
    }
    
private:
    struct Obj{};
    typedef Ret (Obj::*Function)(Arg1, Arg2);
    
    Function _func;
    Obj* _obj;
};

template<class T, class Ret>
Delegate<Ret> make_delegate(T* obj_, Ret (T::*func_)())
{
    return Delegate<Ret>(obj_, func_);
}

template<class T, class Arg1, class Ret>
UnaryDelegate<Arg1, Ret> make_delegate(T* obj_, Ret (T::*func_)(Arg1))
{
    return UnaryDelegate<Arg1, Ret>(obj_, func_);
}

template<class T, class Arg1, class Arg2, class Ret>
BinaryDelegate<Arg1, Arg2, Ret> make_delegate(T* obj_, Ret (T::*func_)(Arg1, Arg2))
{
    return BinaryDelegate<Arg1, Arg2, Ret>(obj_, func_);
}

#endif  //_DELEGATE_H
