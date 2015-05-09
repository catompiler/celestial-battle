#ifndef _VEC3_H_
#define _VEC3_H_

#include <math.h>
#include <algorithm>
#include "exception/badindexexception.h"

#include "vec2.h"

#pragma pack(push, 1)

template <class T>
class vec3{
public:

    typedef T component_type;
    static const size_t components_count = 3;

    vec3();
    explicit vec3(const T& a);
    vec3(const T& _x, const T& _y, const T& _z);
    explicit vec3(T _v[components_count]);
    template <class U> vec3(const vec3<U>& _v);

    vec3(const vec2<T>& _v, const T& _z = T());

    inline void set(const T& _x, const T& _y, const T& _z);

    vec2<T> xy() const;

    operator T*();
    operator const T*() const;
    T& operator[] (int index) throw(BadIndexException&);
    const T& operator[] (int index) const throw(BadIndexException&);
    bool operator==(const vec3<T>& _v) const;
    vec3<T>& operator=(const vec3<T>& _v);
    vec3<T> operator-() const;

    vec3<T>& operator+=(const vec3<T>& _v);
    vec3<T>& operator-=(const vec3<T>& _v);
    vec3<T>& operator*=(const vec3<T>& _v);
    vec3<T>& operator/=(const vec3<T>& _v);
    vec3<T>& operator*=(const T& n);
    vec3<T>& operator/=(const T& n);
    template <class U> friend vec3<U> operator+(const vec3<U>& _v1, const vec3<U>& _v2);
    template <class U> friend vec3<U> operator-(const vec3<U>& _v1, const vec3<U>& _v2);
    template <class U> friend vec3<U> operator*(const vec3<U>& _v1, const vec3<U>& _v2);
    template <class U> friend vec3<U> operator/(const vec3<U>& _v1, const vec3<U>& _v2);
    template <class U, class N> friend vec3<U> operator*(const vec3<U>& _v, const N& n);
    template <class U, class N> friend vec3<U> operator/(const vec3<U>& _v, const N& n);

    template <class U, class N> friend vec3<U> operator*(const N& n, const vec3<U>& _v);

    union{
        T v[components_count];
        struct{
            T x;
            T y;
            T z;
        };
        struct{
            T r;
            T g;
            T b;
        };
    };
};

#pragma pack(pop)

template <class T>
vec3<T>::vec3()
{
    set(T(), T(), T());
}

template <class T>
vec3<T>::vec3(const T& a)
{
    set(a, a, a);
}

template <class T>
vec3<T>::vec3(const T& _x, const T& _y, const T& _z)
{
    set(_x, _y, _z);
}

template <class T>
vec3<T>::vec3(T _v[components_count])
{
    set(_v[0], _v[1], _v[2]);
}

template <class T>
template <class U>
vec3<T>::vec3(const vec3<U>& _v)
{
    set(T(_v.x), T(_v.y), T(_v.z));
}

template <class T>
vec3<T>::vec3(const vec2<T>& _v, const T& _z)
{
    set(_v.x, _v.y, _z);
}

template <class T>
void vec3<T>::set(const T& _x, const T& _y, const T& _z)
{
    x = _x;
    y = _y;
    z = _z;
}

template <class T>
vec2<T> vec3<T>::xy() const
{
    return vec2<T>(x, y);
}

template <class T>
vec3<T>::operator T*()
{
    return v;
}

template <class T>
vec3<T>::operator const T*() const
{
    return v;
}

template <class T>
T& vec3<T>::operator[](int index) throw(BadIndexException&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (BadIndexException("Index out of range!"));
    return v[index];
}

template <class T>
const T& vec3<T>::operator[](int index) const throw(BadIndexException&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (BadIndexException("Index out of range!"));
    return v[index];
}

template <class T>
bool vec3<T>::operator==(const vec3<T>& _v) const
{
    return x == _v.x && y == _v.y && z == _v.z;
}

template <class T>
vec3<T>& vec3<T>::operator=(const vec3<T>& _v)
{
    set(T(_v.x), T(_v.y), T(_v.z));
    return *this;
}

template <class T>
vec3<T> vec3<T>::operator-() const
{
    vec3<T> res;
    res.x = -x; res.y = -y; res.z = -z;
    return res;
}

template <class T>
vec3<T>& vec3<T>::operator+=(const vec3<T>& _v)
{
    x += _v.x;
    y += _v.y;
    z += _v.z;
    return *this;
}

template <class T>
vec3<T>& vec3<T>::operator-=(const vec3<T>& _v)
{
    x -= _v.x;
    y -= _v.y;
    z -= _v.z;
    return *this;
}

template <class T>
vec3<T>& vec3<T>::operator*=(const vec3<T>& _v)
{
    x *= _v.x;
    y *= _v.y;
    z *= _v.z;
    return *this;
}

template <class T>
vec3<T>& vec3<T>::operator/=(const vec3<T>& _v)
{
    x /= _v.x;
    y /= _v.y;
    z /= _v.z;
    return *this;
}

template <class T>
vec3<T>& vec3<T>::operator*=(const T& n)
{
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

template <class T>
vec3<T>& vec3<T>::operator/=(const T& n)
{
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

template <class U>
vec3<U> operator+(const vec3<U>& _v1, const vec3<U>& _v2)
{
    vec3<U> res(_v1);
    res += _v2;
    return res;
}

template <class U>
vec3<U> operator-(const vec3<U>& _v1, const vec3<U>& _v2)
{
    vec3<U> res(_v1);
    res -= _v2;
    return res;
}

template <class U>
vec3<U> operator*(const vec3<U>& _v1, const vec3<U>& _v2)
{
    vec3<U> res(_v1);
    res *= _v2;
    return res;
}

template <class U>
vec3<U> operator/(const vec3<U>& _v1, const vec3<U>& _v2)
{
    vec3<U> res(_v1);
    res /= _v2;
    return res;
}

template <class U, class N>
vec3<U> operator*(const vec3<U>& _v, const N& n)
{
    vec3<U> res(_v);
    res *= n;
    return res;
}


template <class U, class N>
vec3<U> operator/(const vec3<U>& _v, const N& n)
{
    vec3<U> res(_v);
    res /= n;
    return res;
}



template <class T>
double length(const vec3<T>& v)
{
    double res = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return res;
}

template <class T>
T distance(const vec3<T>& v1, const vec3<T>& v2)
{
    T res = length(v1 - v2);
    return res;
}

template <class T>
T dot(const vec3<T>& v1, const vec3<T>& v2)
{
    T res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return res;
}

template <class T>
vec3<T> normalize(const vec3<T>& v) throw (BadIndexException&)
{
    T l = length(v);
    
    if(l == 0.0){
        BadIndexException e("Length is equal to zero!");
        throw(e);
    }
    
    vec3<T> res(v);
    
    res.x /= l;
    res.y /= l;
    res.z /= l;
    
    return res;
}

template <class T>
vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2)
{
    vec3<T> res;
    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    
    return res;
}

template <class T>
vec3<T> clamp(const vec3<T>& _v, const vec3<T>& minVal, const vec3<T>& maxVal)
{
    vec3<T> res;
    
    res.x = std::min(std::max(_v.x, minVal.x), maxVal.x);
    res.y = std::min(std::max(_v.y, minVal.y), maxVal.y);
    res.z = std::min(std::max(_v.z, minVal.z), maxVal.z);
    
    return res;
}

template <class U, class N>
vec3<U> operator*(const N& n, const vec3<U>& _v)
{
    return _v * n;
}

#endif
