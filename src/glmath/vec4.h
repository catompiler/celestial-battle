#ifndef _VEC4_H_
#define _VEC4_H_

#include <math.h>
#include <algorithm>
#include "exception/badindexexception.h"

#include "vec2.h"
#include "vec3.h"

#pragma pack(push, 1)

template <class T>
class vec4{
public:

    static const size_t components_count = 4;

    vec4();
    explicit vec4(const T& a);
    vec4(const T& _x, const T& _y, const T& _z, const T& _w);
    explicit vec4(T _v[components_count]);
    template <class U> vec4(const vec4<U>& _v);

    vec4(const vec2<T>& _v, const T& _z = T(), const T& _w = T());
    vec4(const vec3<T>& _v, const T& _w = T());

    inline void set(const T& _x, const T& _y, const T& _z, const T& _w);

    vec2<T> xy() const;
    vec3<T> xyz() const;

    operator T*();
    operator const T*() const;
    T& operator[] (int index) throw(BadIndexException&);
    const T& operator[] (int index) const throw(BadIndexException&);
    bool operator==(const vec4<T>& _v) const;
    vec4<T>& operator=(const vec4<T>& _v);
    vec4<T> operator-() const;

    vec4<T>& operator+=(const vec4<T>& _v);
    vec4<T>& operator-=(const vec4<T>& _v);
    vec4<T>& operator*=(const vec4<T>& _v);
    vec4<T>& operator/=(const vec4<T>& _v);
    vec4<T>& operator*=(const T& n);
    vec4<T>& operator/=(const T& n);
    template <class U> friend vec4<U> operator+(const vec4<U>& _v1, const vec4<U>& _v2);
    template <class U> friend vec4<U> operator-(const vec4<U>& _v1, const vec4<U>& _v2);
    template <class U> friend vec4<U> operator*(const vec4<U>& _v1, const vec4<U>& _v2);
    template <class U> friend vec4<U> operator/(const vec4<U>& _v1, const vec4<U>& _v2);
    template <class U, class N> friend vec4<U> operator*(const vec4<U>& _v, const N& n);
    template <class U, class N> friend vec4<U> operator/(const vec4<U>& _v, const N& n);

    template <class U, class N> friend vec4<U> operator*(const N& n, const vec4<U>& _v);

    union{
        T v[components_count];
        struct{
            T x;
            T y;
            T z;
            T w;
        };
        struct{
            T r;
            T g;
            T b;
            T a;
        };
    };
};

#pragma pack(pop)

template <class T>
vec4<T>::vec4()
{
    set(T(), T(), T(), T());
}

template <class T>
vec4<T>::vec4(const T& a)
{
    set(a, a, a, a);
}

template <class T>
vec4<T>::vec4(const T& _x, const T& _y, const T& _z, const T& _w)
{
    set(_x, _y, _z, _w);
}

template <class T>
vec4<T>::vec4(T _v[components_count])
{
    set(_v[0], _v[1], _v[2], _v[3]);
}

template <class T>
template <class U>
vec4<T>::vec4(const vec4<U>& _v)
{
    set(T(_v.x), T(_v.y), T(_v.z), T(_v.w));
}

template <class T>
vec4<T>::vec4(const vec2<T>& _v, const T& _z, const T& _w)
{
    set(_v.x, _v.y, _z, _w);
}

template <class T>
vec4<T>::vec4(const vec3<T>& _v, const T& _w)
{
    set(_v.x, _v.y, _v.z, _w);
}

template <class T>
void vec4<T>::set(const T& _x, const T& _y, const T& _z, const T& _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

template <class T>
vec2<T> vec4<T>::xy() const
{
    return vec2<T>(x, y);
}

template <class T>
vec3<T> vec4<T>::xyz() const
{
    return vec3<T>(x, y, z);
}

template <class T>
vec4<T>::operator T*()
{
    return v;
}

template <class T>
vec4<T>::operator const T*() const
{
    return v;
}

template <class T>
T& vec4<T>::operator[](int index) throw(BadIndexException&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (BadIndexException("Index out of range!"));
    return v[index];
}

template <class T>
const T& vec4<T>::operator[](int index) const throw(BadIndexException&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (BadIndexException("Index out of range!"));
    return v[index];
}

template <class T>
bool vec4<T>::operator==(const vec4<T>& _v) const
{
    return x == _v.x && y == _v.y && z == _v.z && w == _v.w;
}

template <class T>
vec4<T>& vec4<T>::operator=(const vec4<T>& _v)
{
    set(T(_v.x), T(_v.y), T(_v.z), T(_v.w));
    return *this;
}

template <class T>
vec4<T> vec4<T>::operator-() const
{
    vec4<T> res;
    res.x = -x; res.y = -y; res.z = -z; res.w = -w;
    return res;
}

template <class T>
vec4<T>& vec4<T>::operator+=(const vec4<T>& _v)
{
    x += _v.x;
    y += _v.y;
    z += _v.z;
    w += _v.w;
    return *this;
}

template <class T>
vec4<T>& vec4<T>::operator-=(const vec4<T>& _v)
{
    x -= _v.x;
    y -= _v.y;
    z -= _v.z;
    w -= _v.w;
    return *this;
}

template <class T>
vec4<T>& vec4<T>::operator*=(const vec4<T>& _v)
{
    x *= _v.x;
    y *= _v.y;
    z *= _v.z;
    w *= _v.w;
    return *this;
}

template <class T>
vec4<T>& vec4<T>::operator/=(const vec4<T>& _v)
{
    x /= _v.x;
    y /= _v.y;
    z /= _v.z;
    w /= _v.w;
    return *this;
}

template <class T>
vec4<T>& vec4<T>::operator*=(const T& n)
{
    x *= n;
    y *= n;
    z *= n;
    w *= n;
    return *this;
}

template <class T>
vec4<T>& vec4<T>::operator/=(const T& n)
{
    x /= n;
    y /= n;
    z /= n;
    w /= n;
    return *this;
}

template <class U>
vec4<U> operator+(const vec4<U>& _v1, const vec4<U>& _v2)
{
    vec4<U> res(_v1);
    res += _v2;
    return res;
}

template <class U>
vec4<U> operator-(const vec4<U>& _v1, const vec4<U>& _v2)
{
    vec4<U> res(_v1);
    res -= _v2;
    return res;
}

template <class U>
vec4<U> operator*(const vec4<U>& _v1, const vec4<U>& _v2)
{
    vec4<U> res(_v1);
    res *= _v2;
    return res;
}

template <class U>
vec4<U> operator/(const vec4<U>& _v1, const vec4<U>& _v2)
{
    vec4<U> res(_v1);
    res /= _v2;
    return res;
}

template <class U, class N>
vec4<U> operator*(const vec4<U>& _v, const N& n)
{
    vec4<U> res(_v);
    res *= n;
    return res;
}


template <class U, class N>
vec4<U> operator/(const vec4<U>& _v, const N& n)
{
    vec4<U> res(_v);
    res /= n;
    return res;
}




template <class T>
double length(const vec4<T>& v)
{
    double res = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    return res;
}

template <class T>
T distance(const vec4<T>& v1, const vec4<T>& v2)
{
    T res = length(v1 - v2);
    return res;
}

template <class T>
T dot(const vec4<T>& v1, const vec4<T>& v2)
{
    T res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    return res;
}

template <class T>
vec4<T> normalize(const vec4<T>& v) throw (BadIndexException&)
{
    T l = length(v);
    
    if(l == 0.0){
        BadIndexException e("Length is equal to zero!");
        throw(e);
    }
    
    vec4<T> res(v);
    
    res.x /= l;
    res.y /= l;
    res.z /= l;
    res.w /= l;
    
    return res;
}

template <class T>
vec4<T> clamp(const vec4<T>& _v, const vec4<T>& minVal, const vec4<T>& maxVal)
{
    vec4<T> res;
    
    res.x = std::min(std::max(_v.x, minVal.x), maxVal.x);
    res.y = std::min(std::max(_v.y, minVal.y), maxVal.y);
    res.z = std::min(std::max(_v.z, minVal.z), maxVal.z);
    res.w = std::min(std::max(_v.w, minVal.w), maxVal.w);
    
    return res;
}

template <class U, class N>
vec4<U> operator*(const N& n, const vec4<U>& _v)
{
    return _v * n;
}


#endif
