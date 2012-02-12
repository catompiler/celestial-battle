#ifndef _SMARTPTR_H
#define _SMARTPTR_H

#include <stddef.h>


template<class T>
class smart_ptr
{
public:
    smart_ptr();
    smart_ptr(T* ptr_);
    smart_ptr(const smart_ptr<T>& sptr_);
    ~smart_ptr();
    
    int refs_count() const;
    
    T* get();
    const T* get() const;
    
    T* reset();
    bool acquire();
    bool release();
    
    operator bool() const;
    
    T* operator->();
    const T* operator->() const;
    
    T& operator*();
    const T& operator*() const;
    
    operator T*();
    operator const T*() const;
    
    smart_ptr<T>& operator=(const smart_ptr<T>& sptr_);
    smart_ptr<T>& operator=(T* ptr_);
    
    bool operator==(const smart_ptr<T>& sptr_) const;
    bool operator==(T* ptr_) const;
    
    template<class To, class From>
    friend smart_ptr<To>& smart_ptr_cast(smart_ptr<From>& sptr_);
    
private:
    class ptr_rep{
    public:
        ptr_rep();
        ptr_rep(T* ptr_);
        ~ptr_rep();
        
        inline T* ptr();
        inline const T* ptr() const;
        inline int refs_count() const;
        
        inline T* reset();
        
        inline bool acquire();
        inline bool release();
        
        inline void acquire_ptr(T* ptr_);
        inline void set_ptr(T* ptr_);
        
    private:
        inline void _ctor(T* ptr_);
        T* _ptr;
        int _refs_count;
    };
    
    mutable ptr_rep* _rep;
    
    inline int _refs_count() const;
    
    inline void _set_ptr(T* ptr_);
    inline void _set_ptr(const smart_ptr<T>& sptr_);
    
    inline T* _get_ptr();
    inline const T* _get_ptr() const;
    
    inline bool _equal(const T* ptr_) const;
    inline bool _equal(const smart_ptr<T>& sptr_) const;
    
    inline T* _reset();
    inline bool _acquire();
    inline bool _release();
};

template<class T>
smart_ptr<T>::smart_ptr()
{
    _rep = NULL;
}

template<class T>
smart_ptr<T>::smart_ptr(T* ptr_)
{
    _rep = NULL;
    _set_ptr(ptr_);
}

template<class T>
smart_ptr<T>::smart_ptr(const smart_ptr<T>& sptr_)
{
    _rep = NULL;
    _set_ptr(sptr_);
}

template<class T>
smart_ptr<T>::~smart_ptr()
{
    if(_rep && _rep->release()){
        delete _rep;
    }
}

template<class T>
int smart_ptr<T>::refs_count() const
{
    return _refs_count();
}

template<class T>
T* smart_ptr<T>::get()
{
    return _get_ptr();
}

template<class T>
const T* smart_ptr<T>::get() const
{
    return _get_ptr();
}

template<class T>
T* smart_ptr<T>::reset()
{
    return _reset();
}

template<class T>
bool smart_ptr<T>::acquire()
{
    return _acquire();
}

template<class T>
bool smart_ptr<T>::release()
{
    return _release();
}

template<class T>
smart_ptr<T>::operator bool() const
{
    return _get_ptr() != NULL;
}

template<class T>
T* smart_ptr<T>::operator->()
{
    return _get_ptr();
}

template<class T>
const T* smart_ptr<T>::operator->() const
{
    return _get_ptr();
}

template<class T>
T& smart_ptr<T>::operator*()
{
    return *_get_ptr();
}

template<class T>
const T& smart_ptr<T>::operator*() const
{
    return *_get_ptr();
}

template<class T>
smart_ptr<T>::operator T*()
{
    return get();
}

template<class T>
smart_ptr<T>::operator const T*() const
{
    return get();
}

template<class T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr<T>& sptr_)
{
    _set_ptr(sptr_);
    return *this;
}

template<class T>
smart_ptr<T>& smart_ptr<T>::operator=(T* ptr_)
{
    _set_ptr(ptr_);
    return *this;
}

template<class T>
bool smart_ptr<T>::operator==(const smart_ptr<T>& sptr_) const
{
    return _equal(sptr_);
}

template<class T>
bool smart_ptr<T>::operator==(T* ptr_) const
{
    return _equal(ptr_);
}

/*
 * rep states:
 * - NULL
 * - with refs
 * - without (with one) refs
 * if ptr == NULL => rep = NULL
 */
template<class T>
void smart_ptr<T>::_set_ptr(T* ptr_)//!!
{
    //if rep is not NULL
    if(_rep){
        //if ptr is not NULL
        if(ptr_){
            //if rep is shared
            if(!_rep->release()){//release it
                _rep = new ptr_rep();//and create new
            }
            //set ptr && inc refs
            _rep->acquire_ptr(ptr_);
        }else{//if ptr == NULL
            if(_rep->release()){//if rep has no refs
                delete _rep;//delete rep
            }
            _rep = NULL;//rep = NULL
        }
    }else{//if rep == NULL
        if(ptr_){//if ptr is not NULL
            _rep = new ptr_rep(ptr_);//create new rep
        }else{
            //do nothing
        }
    }
}

template<class T>
void smart_ptr<T>::_set_ptr(const smart_ptr<T>& sptr_)
{
    if(sptr_._rep) sptr_._rep->acquire();
    if(_rep){
        if(_rep->release()){
            delete _rep;
            _rep = NULL;
        }
    }
    _rep = sptr_._rep;
}

template<class T>
T* smart_ptr<T>::_get_ptr()
{
    return _rep ? _rep->ptr() : NULL;
}

template<class T>
const T* smart_ptr<T>::_get_ptr() const
{
    return _rep ? _rep->ptr() : NULL;
}

template<class T>
bool smart_ptr<T>::_equal(const T* ptr_) const
{
    return _get_ptr() == ptr_;
}

template<class T>
bool smart_ptr<T>::_equal(const smart_ptr<T>& sptr_) const
{
    return _get_ptr() == sptr_._get_ptr();
}

template<class T>
int smart_ptr<T>::_refs_count() const
{
    return _rep ? _rep->refs_count() : 0;
}

template<class T>
T* smart_ptr<T>::_reset()
{
    T* ptr = _get_ptr();
    
    if(_rep){
        if(_rep->refs_count() <= 1){//can be 0 ?
            _rep->reset();
            delete _rep;
        }
        _rep = NULL;
    }
    
    return ptr;
}

template<class T>
bool smart_ptr<T>::_acquire()
{
    return _rep ? _rep->acquire() : false;
}

template<class T>
bool smart_ptr<T>::_release()
{
    if(_rep == NULL) return true;
    if(_rep->release()){
        delete _rep;
        _rep = NULL;
        return true;
    }
    return false;
}



//rep
template<class T>
smart_ptr<T>::ptr_rep::ptr_rep()
{
    _ctor(NULL);
}

template<class T>
smart_ptr<T>::ptr_rep::ptr_rep(T* ptr_)
{
    _ctor(ptr_);
}

template<class T>
smart_ptr<T>::ptr_rep::~ptr_rep()
{
}

template<class T>
T* smart_ptr<T>::ptr_rep::ptr()
{
    return _ptr;
}

template<class T>
const T* smart_ptr<T>::ptr_rep::ptr() const
{
    return _ptr;
}

template<class T>
int smart_ptr<T>::ptr_rep::refs_count() const
{
    return _refs_count;
}

template<class T>
T* smart_ptr<T>::ptr_rep::reset()
{
    T* res = _ptr;
    
    _ptr = NULL;
    _refs_count = 0;
    
    return res;
}

template<class T>
bool smart_ptr<T>::ptr_rep::acquire()
{
    _refs_count ++;
    return true;
}

template<class T>
bool smart_ptr<T>::ptr_rep::release()
{
    if(_refs_count == 0) return true;
    if(--_refs_count == 0){
        delete _ptr;
        _ptr = NULL;
        return true;
    }
    return false;
}

template<class T>
void smart_ptr<T>::ptr_rep::acquire_ptr(T* ptr_)//!!
{
    set_ptr(ptr_);
    acquire();
}

template<class T>
void smart_ptr<T>::ptr_rep::set_ptr(T* ptr_)//!!
{
    _ptr = ptr_;
}

template<class T>
void smart_ptr<T>::ptr_rep::_ctor(T* ptr_)
{
    _ptr = ptr_;
    if(ptr_){
        _refs_count = 1;
    }else{
        _refs_count = 0;
    }
}


template<class To, class From>
smart_ptr<To>& smart_ptr_cast(smart_ptr<From>& sptr_)
{
    return *reinterpret_cast<smart_ptr<To>*>(&sptr_);
}

#endif //_SMARTPTR_H
