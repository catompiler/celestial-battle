#ifndef _SMARTPTR_H
#define _SMARTPTR_H

#include <stddef.h>

template <class T>
class smart_ptr
{
public:
    smart_ptr();
    smart_ptr(T* ptr);
    smart_ptr(const smart_ptr<T>& sptr);
    ~smart_ptr();

    T& operator*();
    T* operator->();
    T* get();
    
    bool operator==(T* ptr);

    smart_ptr<T>& operator=(const smart_ptr<T>& sptr);
    smart_ptr<T>& operator=(T* ptr);

    void release();

private:
    class Rep{
    public:
        Rep();
        Rep(T* ptr);
        ~Rep();
        
        bool release();
        
        T& operator*();
        T* operator->();
        T* get();
        
        bool operator==(T* ptr);
        Rep& operator=(T* ptr);
        
        T* _ptr;
        size_t _links_count;
    };

    mutable Rep* _rep;

};


template <class T>
smart_ptr<T>::smart_ptr()
{
    _rep = new Rep();
}

template <class T>
smart_ptr<T>::smart_ptr(T* ptr)
{
    _rep = new Rep(ptr);
}

template <class T>
smart_ptr<T>::smart_ptr(const smart_ptr<T>& sptr)
{
    sptr._rep->_links_count ++;
    _rep = sptr._rep;
}

template <class T>
smart_ptr<T>::~smart_ptr()
{
    if(_rep->release()){
        delete _rep;
    }
}

template <class T>
T* smart_ptr<T>::operator->()
{
    return _rep->operator->();
}

template <class T>
T* smart_ptr<T>::get()
{
    return _rep->get();
}

template <class T>
bool smart_ptr<T>::operator==(T* ptr)
{
    return _rep->operator==(ptr);
}

template <class T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr<T>& sptr)
{
    if(_rep->release()){
        delete _rep;
    }
    sptr._rep->_links_count++;
    _rep = sptr._rep;
    
    return *this;
}

template <class T>
smart_ptr<T>& smart_ptr<T>::operator=(T* ptr)
{
    if(!_rep->release()){
        _rep = new Rep;
    }
    
    _rep->operator=(ptr);
    
    return *this;
}

template <class T>
T& smart_ptr<T>::operator*()
{
    return _rep->operator*();
}

template <class T>
void smart_ptr<T>::release()
{
    if(!_rep->release()){
        _rep = new Rep();
    }else{
        _rep->operator=(NULL);
    }
}


template <class T>
smart_ptr<T>::Rep::Rep()
{
    _ptr = NULL;
    _links_count = 1;
}

template <class T>
smart_ptr<T>::Rep::Rep(T* ptr)
{
    _ptr = ptr;
    _links_count = 1;
}

template <class T>
smart_ptr<T>::Rep::~Rep()
{
    //release();
}

template <class T>
bool smart_ptr<T>::Rep::release()
{
    if(_links_count > 0){
        if(--_links_count == 0){
            if(_ptr != NULL){
                delete _ptr;
                _ptr = NULL;
            }
            return true;
        }
    }else{
        return true;
    }
    return false;
}

template <class T>
T& smart_ptr<T>::Rep::operator*()
{
    return *_ptr;
}

template <class T>
T* smart_ptr<T>::Rep::operator->()
{
    return _ptr;
}

template <class T>
T* smart_ptr<T>::Rep::get()
{
    return _ptr;
}

template <class T>
bool smart_ptr<T>::Rep::operator==(T* ptr)
{
    return ptr == _ptr;
}

template <class T>
typename smart_ptr<T>::Rep& smart_ptr<T>::Rep::operator=(T* ptr)
{
    //delete _ptr;
    
    _ptr = ptr;
    _links_count = 1;
    
    return *this;
}

#endif //_SMARTPTR_H
