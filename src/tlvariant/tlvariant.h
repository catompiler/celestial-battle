#ifndef _TLVARIANT_H_ 
#define _TLVARIANT_H_

#include <stddef.h>
#include "exception/badtypeexception.h"
#include "typelist/typelist.h"


template <class TypeList>
class TLVariant
{
public:
    
    typedef TypeList typelist;
    
    TLVariant();
    template <class T> TLVariant(const T& v_);
    TLVariant(const TLVariant<TypeList>& v_);
    ~TLVariant();
    
    template <class T> T& get() throw(BadTypeException&);
    template <class T> const T& get() const throw(BadTypeException&);
    template <class T> void set(const T& v_);

    template <class T> operator T&() throw(BadTypeException&);
    template <class T> operator const T&() const throw(BadTypeException&);
    template <class T> TLVariant<TypeList>& operator=(const T& v_);
    TLVariant<TypeList>& operator=(const TLVariant<TypeList>& v_);
    
private:
    
    class CurValueBase
    {
    public:
        CurValueBase(int type_index_){
            _type_index = type_index_;
        }
        virtual ~CurValueBase(){}
        
        int type_index() const{
            return _type_index;
        }
        
        virtual CurValueBase* clone() const = 0;
        
    protected:
        int _type_index;
    };
    
    template <class T>
    class CurValue
        :public CurValueBase
    {
    public:
        CurValue(int type_index_, const T& value_)
            :CurValueBase(type_index_)
        {
            _value = new T(value_);
        }
        ~CurValue(){delete _value;}
        
        T& value(){
            return *_value;
        }
        const T& value() const{
            return *_value;
        }
        
        void setValue(const T& value_){
            *_value = value_;
        }
        
        CurValue<T>* clone() const{
            return new CurValue<T>(CurValueBase::_type_index, *_value);
        }
        
    private:
        T* _value;
    };
    
    CurValueBase* _value;
};

template <class TypeList>
TLVariant<TypeList>::TLVariant()
{
    _value = NULL;
}

template <class TypeList>
template <class T>
TLVariant<TypeList>::TLVariant(const T& v_)
{
    _value = NULL;
    operator=(v_);
}

template <class TypeList>
TLVariant<TypeList>::TLVariant(const TLVariant<TypeList>& v_)
{
    _value = NULL;
    operator=(v_);
}

template <class TypeList>
TLVariant<TypeList>::~TLVariant()
{
    delete _value;
}


template <class TypeList>
template <class T>
T& TLVariant<TypeList>::get() throw(BadTypeException&)
{
    const int type_index = tl::index_of<TypeList, T>::value;
#ifdef DEBUG
    std::cout << "get: type_index = " << type_index << std::endl;
#endif
    if(type_index == -1){
        //return T();
        throw(BadTypeException("type not found"));
    }
    if((_value == NULL) || (_value->type_index() != type_index)){
        //return T();
        throw(BadTypeException("bad value type"));
    }
    return static_cast<CurValue<T>*>(_value)->value();
}

template <class TypeList>
template <class T>
const T& TLVariant<TypeList>::get() const throw(BadTypeException&)
{
    /*typedef T& (Value<TypeList>::*getProc)();
    getProc gp = &Value<TypeList>::get;
    return (const_cast<Value<TypeList>*>(this)->*gp)();*/
    return (const_cast<TLVariant<TypeList>*>(this)->*
        ((T& (TLVariant<TypeList>::*)())&TLVariant<TypeList>::get)
        )();//black magic
}

template <class TypeList>
template <class T>
void TLVariant<TypeList>::set(const T& v_)
{
    const int type_index = tl::index_of<TypeList, T>::value;
#ifdef DEBUG
    std::cout << "set: type_index = " << type_index << std::endl;
#endif
    if(type_index == -1){
        return;
    }
    if((_value == NULL) || (_value->type_index() != type_index)){
        delete _value;
        _value = new CurValue<T>(type_index, v_);
        return;
    }
    static_cast<CurValue<T>*>(_value)->setValue(v_);
}

template <class TypeList>
template <class T>
TLVariant<TypeList>::operator T&() throw(BadTypeException&)
{
    return get<T>();
}

template <class TypeList>
template <class T>
TLVariant<TypeList>::operator const T&() const throw(BadTypeException&)
{
    return get<T>();
}

template <class TypeList>
template <class T>
TLVariant<TypeList>& TLVariant<TypeList>::operator=(const T& v_)
{
    set(v_);
    return *this;
}

template <class TypeList>
TLVariant<TypeList>& TLVariant<TypeList>::operator=(const TLVariant<TypeList>& v_)
{
    delete _value;
    if(v_._value != NULL){
        _value = v_._value->clone();
    }else{
        _value = NULL;
    }
    return *this;
}



#endif  //_TLVARIANT_H_
