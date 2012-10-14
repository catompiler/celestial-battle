#ifndef _DELEGATE_H
#define _DELEGATE_H


//#define __GXX_EXPERIMENTAL_CXX0X__

#include <utility>
#include <functional>
#include <stddef.h>


#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L

template <typename Ret, typename... Args>
class Delegate
    :public std::function<Ret(Args...)>
{
public:
    
    Delegate();

    template<typename Obj>
    Delegate(Obj* obj_, Ret (Obj::*func_)(Args...));

    operator bool() const;
    bool operator==(const Delegate<Ret, Args...>& d_) const;
    
    template <typename Obj>
    bool compareObject(const Obj* obj_) const;
    
    template <typename Obj>
    bool compare(const Obj* obj_, Ret (Obj::*func_)(Args...)) const;
    
    Delegate<Ret, Args...>& operator=(const Delegate<Ret, Args...>& d_);

    //Ret operator()(Args&&... args_);
    Ret operator()(Args... args_);

private:
    struct obj_t{};
    typedef Ret (obj_t::*func_t)(Args...);

    obj_t* _obj;
    func_t _func;
};

template <typename Ret, typename... Args>
Delegate<Ret, Args...>::Delegate()
{
    _obj = nullptr;
    _func = nullptr;
}

template <typename Ret, typename... Args>
template <typename Obj>
Delegate<Ret, Args...>::Delegate(Obj* obj_, Ret (Obj::*func_)(Args...))
{
    _obj = reinterpret_cast<obj_t*>(obj_);
    _func = reinterpret_cast<func_t>(func_);
}

template <typename Ret, typename... Args>
Delegate<Ret, Args...>::operator bool() const
{
    return _obj != nullptr && _func != nullptr;
}

template <typename Ret, typename... Args>
bool Delegate<Ret, Args...>::operator==(const Delegate<Ret, Args...>& d_) const
{
    return _obj == d_._obj && _func == d_._func;
}

template <typename Ret, typename... Args>
template <typename Obj>
bool Delegate<Ret, Args...>::compareObject(const Obj* obj_) const
{
    return _obj == reinterpret_cast<const obj_t*>(obj_);
}

template <typename Ret, typename... Args>
template <typename Obj>
bool Delegate<Ret, Args...>::compare(const Obj* obj_, Ret (Obj::*func_)(Args...)) const
{
    return _obj == reinterpret_cast<const obj_t*>(obj_) &&
           _func == reinterpret_cast<func_t>(func_);
}

template <typename Ret, typename... Args>
Delegate<Ret, Args...>& Delegate<Ret, Args...>::operator=(const Delegate<Ret, Args...>& d_)
{
    _obj = d_._obj;
    _func = d_._func;
    return *this;
}

/*template <typename Ret, typename... Args>
Ret Delegate<Ret, Args...>::operator()(Args&&... args_)
{
    return (_obj->*_func)(std::forward<Args>(args_)...);
}*/

template <typename Ret, typename... Args>
Ret Delegate<Ret, Args...>::operator()(Args... args_)
{
    return (_obj->*_func)(args_...);
}


template <typename Ret, typename Arg>
using UnaryDelegate = Delegate<Ret, Arg>;

template <typename Ret, typename Arg0, typename Arg1>
using BinaryDelegate = Delegate<Ret, Arg0, Arg1>;


template <typename Obj, typename Ret, typename... Args>
Delegate<Ret, Args...> make_delegate(Obj* obj_, Ret (Obj::*func_)(Args...))
{
    return Delegate<Ret, Args...>(obj_, func_);
}


#else


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
    
    Delegate(const Delegate<Ret>& d_){
        _obj = d_._obj;
        _func = d_._func;
    }
    
    Delegate<Ret>& operator=(const Delegate<Ret>& d_){
        _obj = d_._obj;
        _func = d_._func;
        return *this;
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

template<class Ret, class Arg1>
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
    
    UnaryDelegate(const UnaryDelegate<Ret, Arg1>& d_){
        _obj = d_._obj;
        _func = d_._func;
    }
    
    UnaryDelegate<Ret, Arg1>& operator=(const UnaryDelegate<Ret, Arg1>& d_){
        _obj = d_._obj;
        _func = d_._func;
        return *this;
    }
    
    operator bool() const{
        return _obj != NULL;
    }
    
    Ret operator()(Arg1 arg1) const{
        return (_obj->*_func)(arg1);
    }
    
    bool operator==(const UnaryDelegate<Ret, Arg1>& delegate_) const{
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

template<class Ret, class Arg1, class Arg2>
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
    
    BinaryDelegate(const BinaryDelegate<Ret, Arg1, Arg2>& d_){
        _obj = d_._obj;
        _func = d_._func;
    }
    
    BinaryDelegate<Ret, Arg1, Arg2>& operator=(const BinaryDelegate<Ret, Arg1, Arg2>& d_){
        _obj = d_._obj;
        _func = d_._func;
        return *this;
    }
    
    operator bool() const{
        return _obj != NULL;
    }
    
    Ret operator()(Arg1 arg1, Arg2 arg2) const{
        return (_obj->*_func)(arg1, arg2);
    }
    
    bool operator==(const BinaryDelegate<Ret, Arg1, Arg2>& delegate_) const{
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

template<class Ret, class T>
Delegate<Ret> make_delegate(T* obj_, Ret (T::*func_)())
{
    return Delegate<Ret>(obj_, func_);
}

template<class T, class Ret, class Arg1>
UnaryDelegate<Ret, Arg1> make_delegate(T* obj_, Ret (T::*func_)(Arg1))
{
    return UnaryDelegate<Ret, Arg1>(obj_, func_);
}

template<class T, class Ret, class Arg1, class Arg2>
BinaryDelegate<Ret, Arg1, Arg2> make_delegate(T* obj_, Ret (T::*func_)(Arg1, Arg2))
{
    return BinaryDelegate<Ret, Arg1, Arg2>(obj_, func_);
}

#endif

#endif  //_DELEGATE_H
