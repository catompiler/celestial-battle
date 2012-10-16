#ifndef _DELEGATE_H
#define _DELEGATE_H

#include <utility>
#include <functional>
#include <stddef.h>


//#if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L

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


#endif  //_DELEGATE_H
