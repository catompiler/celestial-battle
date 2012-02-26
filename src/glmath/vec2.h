#ifndef _VEC2_H_
#define _VEC2_H_

#include <math.h>
#include <algorithm>
#include "exception/badindexexception.h"

#pragma pack(push, 1)

template <class T>
class vec2{
public:

    static const size_t components_count = 2;

    vec2();
    explicit vec2(const T& a);
    vec2(const T& _x, const T& _y);
    explicit vec2(T _v[components_count]);
    template <class U> vec2(const vec2<U>& _v);

    inline void set(const T& _x, const T& _y);

    operator T*();
    operator const T*() const;
    T& operator[] (int index) throw(BadIndexException&);
    const T& operator[] (int index) const throw(BadIndexException&);
    bool operator==(const vec2<T>& _v) const;
    vec2<T>& operator=(const vec2<T>& _v);
    vec2<T> operator-() const;

    vec2<T>& operator+=(const vec2<T>& _v);
    vec2<T>& operator-=(const vec2<T>& _v);
    vec2<T>& operator*=(const vec2<T>& _v);
    vec2<T>& operator/=(const vec2<T>& _v);
    vec2<T>& operator*=(const T& n);
    vec2<T>& operator/=(const T& n);
    template <class U> friend vec2<U> operator+(const vec2<U>& _v1, const vec2<U>& _v2);
    template <class U> friend vec2<U> operator-(const vec2<U>& _v1, const vec2<U>& _v2);
    template <class U> friend vec2<U> operator*(const vec2<U>& _v1, const vec2<U>& _v2);
    template <class U> friend vec2<U> operator/(const vec2<U>& _v1, const vec2<U>& _v2);
    template <class U, class N> friend vec2<U> operator*(const vec2<U>& _v, const N& n);
    template <class U, class N> friend vec2<U> operator/(const vec2<U>& _v, const N& n);

    template <class U, class N> friend vec2<U> operator*(const N& n, const vec2<U>& _v);

    union{
        T v[components_count];
        struct{
            T x;
            T y;
        };
        struct{
            T r;
            T g;
        };
    };
};

#pragma pack(pop)

template <class T>
vec2<T>::vec2()
{
    set(T(), T());
}

template <class T>
vec2<T>::vec2(const T& a)
{
    set(a, a);
}

template <class T>
vec2<T>::vec2(const T& _x, const T& _y)
{
    set(_x, _y);
}

template <class T>
vec2<T>::vec2(T _v[2])
{
    set(_v[0], _v[1]);
}

template <class T>
template <class U>
vec2<T>::vec2(const vec2<U>& _v)
{
    set(T(_v.x), T(_v.y));
}

template <class T>
void vec2<T>::set(const T& _x, const T& _y)
{
    x = _x;
    y = _y;
}

template <class T>
vec2<T>::operator T*()
{
    return v;
}

template <class T>
vec2<T>::operator const T*() const
{
    return v;
}

template <class T>
T& vec2<T>::operator[](int index) throw(BadIndexException&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (BadIndexException("Index out of range!"));
    return v[index];
}

template <class T>
const T& vec2<T>::operator[](int index) const throw(BadIndexException&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (BadIndexException("Index out of range!"));
    return v[index];
}

template <class T>
bool vec2<T>::operator==(const vec2<T>& _v) const
{
    return x == _v.x && y == _v.y;
}

template <class T>
vec2<T>& vec2<T>::operator=(const vec2<T>& _v)
{
    set(T(_v.x), T(_v.y));
    return *this;
}

template <class T>
vec2<T> vec2<T>::operator-() const
{
    vec2<T> res;
    res.x = -x; res.y = -y;
    return res;
}

template <class T>
vec2<T>& vec2<T>::operator+=(const vec2<T>& _v)
{
    x += _v.x;
    y += _v.y;
    return *this;
}

template <class T>
vec2<T>& vec2<T>::operator-=(const vec2<T>& _v)
{
    x -= _v.x;
    y -= _v.y;
    return *this;
}

template <class T>
vec2<T>& vec2<T>::operator*=(const vec2<T>& _v)
{
    x *= _v.x;
    y *= _v.y;
    return *this;
}

template <class T>
vec2<T>& vec2<T>::operator/=(const vec2<T>& _v)
{
    x /= _v.x;
    y /= _v.y;
    return *this;
}

template <class T>
vec2<T>& vec2<T>::operator*=(const T& n)
{
    x *= n;
    y *= n;
    return *this;
}

template <class T>
vec2<T>& vec2<T>::operator/=(const T& n)
{
    x /= n;
    y /= n;
    return *this;
}

template <class U>
vec2<U> operator+(const vec2<U>& _v1, const vec2<U>& _v2)
{
    vec2<U> res(_v1);
    res += _v2;
    return res;
}

template <class U>
vec2<U> operator-(const vec2<U>& _v1, const vec2<U>& _v2)
{
    vec2<U> res(_v1);
    res -= _v2;
    return res;
}

template <class U>
vec2<U> operator*(const vec2<U>& _v1, const vec2<U>& _v2)
{
    vec2<U> res(_v1);
    res *= _v2;
    return res;
}

template <class U>
vec2<U> operator/(const vec2<U>& _v1, const vec2<U>& _v2)
{
    vec2<U> res(_v1);
    res /= _v2;
    return res;
}

template <class U, class N>
vec2<U> operator*(const vec2<U>& _v, const N& n)
{
    vec2<U> res(_v);
    res *= n;
    return res;
}


template <class U, class N>
vec2<U> operator/(const vec2<U>& _v, const N& n)
{
    vec2<U> res(_v);
    res /= n;
    return res;
}




template <class T>
double length(const vec2<T>& v)
{
    double res = sqrt(v.x * v.x + v.y * v.y);
    return res;
}

template <class T>
T distance(const vec2<T>& v1, const vec2<T>& v2)
{
    T res = length(v1 - v2);
    return res;
}

template <class T>
T dot(const vec2<T>& v1, const vec2<T>& v2)
{
    T res = v1.x * v2.x + v1.y * v2.y;
    return res;
}

template <class T>
vec2<T> normalize(const vec2<T>& v) throw (BadIndexException&)
{
    T l = length(v);
    
    if(l == 0.0){
        BadIndexException e("Length is equal to zero!");
        throw(e);
    }
    
    vec2<T> res(v);
    
    res.x /= l;
    res.y /= l;
    
    return res;
}

template <class T>
vec2<T> clamp(const vec2<T>& _v, const vec2<T>& minVal, const vec2<T>& maxVal)
{
    vec2<T> res;
    
    res.x = std::min(std::max(_v.x, minVal.x), maxVal.x);
    res.y = std::min(std::max(_v.y, minVal.y), maxVal.y);
    
    return res;
}

template <class U, class N>
vec2<U> operator*(const N& n, const vec2<U>& _v)
{
    return _v * n;
}

#endif
