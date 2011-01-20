#ifndef _QUAT_H_
#define _QUAT_H_

#include <math.h>
//#include <algorithm>
#include "../exception/exception.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"
#include "glmath.h"

template <class T> class mat3;
template <class T> class mat4;

#pragma pack(push, 1)

template <class T>
class quat{
public:

    static const size_t components_count = 4;

    quat();
    explicit quat(const T& a);
    quat(const T& _x, const T& _y, const T& _z, const T& _w);
    explicit quat(T _q[components_count]);
    template <class U> quat(const quat<U>& _q);

    quat(const vec2<T>& _v, const T& _z = T(), const T& _w = T());
    quat(const vec3<T>& _v, const T& _w = T());
    quat(const vec4<T>& _v);

    inline void set(const T& _x, const T& _y, const T& _z, const T& _w);

    vec2<T> xy() const;
    vec3<T> xyz() const;
    vec4<T> xyzw() const;
    
    T angle() const;
    vec3<T> axis() const throw(Exception&);

    operator T*();
    operator const T*() const;
    T& operator[] (int index) throw(Exception&);
    const T& operator[] (int index) const throw(Exception&);
    bool operator==(const quat<T>& _q) const;
    quat<T>& operator=(const quat<T>& _q);
    quat<T> operator-() const;

    quat<T>& operator+=(const quat<T>& _q);
    quat<T>& operator-=(const quat<T>& _q);
    quat<T>& operator*=(const quat<T>& _q);
    quat<T>& operator*=(const T& n);
    quat<T>& operator/=(const T& n);
    quat<T> operator+(const quat<T>& _q) const;
    quat<T> operator-(const quat<T>& _q) const;
    quat<T> operator*(const quat<T>& _q) const;
    quat<T> operator*(const T& n) const;
    quat<T> operator/(const T& n) const;

    static quat<T> identity();
    static quat<T> from_matrix(const mat3<T>& _m);
    static quat<T> from_matrix(const mat4<T>& _m);
    static quat<T> rotation(const T& _x, const T& _y, const T& _z, const T& _angle);
    static quat<T> rotation(const vec3<T>& _v, const T& _angle);
    static quat<T> rotation(const vec3<T>& _v1, const vec3<T>& _v2);
    
    template<class U> friend vec4<U> operator*(const vec4<U>& _v, const quat<U>& _q);
    template<class U> friend vec3<U> operator*(const vec3<U>& _v, const quat<U>& _q);
    template<class U> friend vec4<U> operator*(const quat<U>& _q, const vec4<U>& _v);
    template<class U> friend vec3<U> operator*(const quat<U>& _q, const vec3<U>& _v);
    
    union{
        T q[components_count];
        struct{
            T x;
            T y;
            T z;
            T w;
        };
    };
};

#pragma pack(pop)

template <class T>
quat<T>::quat()
{
    set(T(), T(), T(), T());
}

template <class T>
quat<T>::quat(const T& a)
{
    set(a, a, a, a);
}

template <class T>
quat<T>::quat(const T& _x, const T& _y, const T& _z, const T& _w)
{
    set(_x, _y, _z, _w);
}

template <class T>
quat<T>::quat(T _q[components_count])
{
    set(_q[0], _q[1], _q[2], _q[3]);
}

template <class T>
template <class U>
quat<T>::quat(const quat<U>& _q)
{
    set(T(_q.x), T(_q.y), T(_q.z), T(_q.w));
}

template <class T>
quat<T>::quat(const vec2<T>& _v, const T& _z, const T& _w)
{
    set(_v.x, _v.y, _z, _w);
}

template <class T>
quat<T>::quat(const vec3<T>& _v, const T& _w)
{
    set(_v.x, _v.y, _v.z, _w);
}

template <class T>
quat<T>::quat(const vec4<T>& _v)
{
    set(_v.x, _v.y, _v.z, _v.w);
}

template <class T>
void quat<T>::set(const T& _x, const T& _y, const T& _z, const T& _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

template <class T>
vec2<T> quat<T>::xy() const
{
    return vec2<T>(x, y);
}

template <class T>
vec3<T> quat<T>::xyz() const
{
    return vec3<T>(x, y, z);
}

template <class T>
vec4<T> quat<T>::xyzw() const
{
    return vec4<T>(x, y, z, w);
}

template <class T>
T quat<T>::angle() const
{
    return acos(w) * 2.0;
}

template <class T>
vec3<T> quat<T>::axis() const throw(Exception&)
{
    vec3<T> res;
    T sin_a2;
    
    sin_a2 = sqrt( 1.0f - w * w );
    
    if(sin_a2 == 0.0){
        Exception e("Rotation is zero!");
        throw(e);
    }
    
    res.x = x / sin_a2;
    res.y = y / sin_a2;
    res.z = z / sin_a2;
    
    return res;
}

template <class T>
quat<T>::operator T*()
{
    return q;
}

template <class T>
quat<T>::operator const T*() const
{
    return q;
}

template <class T>
T& quat<T>::operator[](int index) throw(Exception&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (Exception("Index out of range!"));
    return q[index];
}

template <class T>
const T& quat<T>::operator[](int index) const throw(Exception&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (Exception("Index out of range!"));
    return q[index];
}

template <class T>
bool quat<T>::operator==(const quat<T>& _q) const
{
    return x == _q.x && y == _q.y && z == _q.z && w == _q.w;
}

template <class T>
quat<T>& quat<T>::operator=(const quat<T>& _q)
{
    set(T(_q.x), T(_q.y), T(_q.z), T(_q.w));
    return *this;
}

template <class T>
quat<T> quat<T>::operator-() const
{
    quat<T> res;
    res.x = -x; res.y = -y; res.z = -z; res.w = -w;
    return res;
}

template <class T>
quat<T>& quat<T>::operator+=(const quat<T>& _q)
{
    x += _q.x;
    y += _q.y;
    z += _q.z;
    w += _q.w;
    return *this;
}

template <class T>
quat<T>& quat<T>::operator-=(const quat<T>& _q)
{
    x -= _q.x;
    y -= _q.y;
    z -= _q.z;
    w -= _q.w;
    return *this;
}

template <class T>
quat<T>& quat<T>::operator*=(const quat<T>& _q)
{
    vec3<T> v1  = xyz();
    T w1 = w;
    vec3<T> v2 = _q.xyz();
    T w2 = _q.w;
    
    vec3<T> resv;
    T resw;
    
    resv = cross(v1,v2) + w1 * v2 + w2 * v1;
    resw = w1 * w2 - dot(v1,v2);
    
    set(resv.x, resv.y, resv.z, resw);
    
    return *this;
}

template <class T>
quat<T>& quat<T>::operator*=(const T& n)
{
    x *= n;
    y *= n;
    z *= n;
    w *= n;
    return *this;
}

template <class T>
quat<T>& quat<T>::operator/=(const T& n)
{
    x /= n;
    y /= n;
    z /= n;
    w /= n;
    return *this;
}

template <class T>
quat<T> quat<T>::operator+(const quat<T>& _q) const
{
    quat<T> res(*this);
    res += _q;
    return res;
}

template <class T>
quat<T> quat<T>::operator-(const quat<T>& _q) const
{
    quat<T> res(*this);
    res -= _q;
    return res;
}

template <class T>
quat<T> quat<T>::operator*(const quat<T>& _q) const
{
    quat<T> res(*this);
    res *= _q;
    return res;
}

template <class T>
quat<T> quat<T>::operator*(const T& n) const
{
    quat<T> res(*this);
    res *= n;
    return res;
}

template <class T>
quat<T> quat<T>::operator/(const T& n) const
{
    quat<T> res(*this);
    res /= n;
    return res;
}

template <class T>
quat<T> quat<T>::identity()
{
    return quat<T>(T(0.0),T(0.0),T(0.0),T(1.0));
}

template <class T>
quat<T> quat<T>::from_matrix(const mat3<T>& _m)
{
    quat<T> res;
    T s  =  0.0;
    T t  =  _m._11 + _m._22 + _m._33 + 1;
    if(t > 0.0){
        s = 0.5 / sqrt(t);
        res.w = 0.25 / s;
        res.x = (_m._32 - _m._23) * s;
        res.y = (_m._13 - _m._31) * s;
        res.z = (_m._21 - _m._12) * s;
    }
    else{
        if(_m._11 > _m._22 && _m._11 > _m._33){
            s = sqrt(1.0 + _m._11 - _m._22 - _m._33) * 2.0;
            res.x = 0.5 / s;
            res.y = (_m._12 + _m._21) / s;
            res.z = (_m._13 + _m._31) / s;
            res.w = (_m._23 + _m._32) / s;
        }else if(_m._22 > _m._11 && _m._22 > _m._33){
            s = sqrt(1.0 + _m._22 - _m._11 - _m._33) * 2.0;
            res.x = (_m._12 + _m._21) / s;
            res.y = 0.5 / s;
            res.z = (_m._23 + _m._32) / s;
            res.w = (_m._13 + _m._31) / s;
        }else if(_m._33 > _m._11 && _m._33 > _m._22){
            s = sqrt(1.0 + _m._33 - _m._11 - _m._22) * 2.0;
            res.x = (_m._13 + _m._31) / s;
            res.y = (_m._23 + _m._32) / s;
            res.z = 0.5 / s;
            res.w = (_m._12 + _m._21) / s;
        }
    }
    return res;
}

template <class T>
quat<T> quat<T>::from_matrix(const mat4<T>& _m)
{
    quat<T> res;
    T s  =  0.0;
    T t  =  _m._11 + _m._22 + _m._33 + 1;
    if(t > 0.0){
        s = 0.5 / sqrt(t);
        res.w = 0.25 / s;
        res.x = (_m._32 - _m._23) * s;
        res.y = (_m._13 - _m._31) * s;
        res.z = (_m._21 - _m._12) * s;
    }
    else{
        if(_m._11 > _m._22 && _m._11 > _m._33){
            s = sqrt(1.0 + _m._11 - _m._22 - _m._33) * 2.0;
            res.x = 0.5 / s;
            res.y = (_m._12 + _m._21) / s;
            res.z = (_m._13 + _m._31) / s;
            res.w = (_m._23 + _m._32) / s;
        }else if(_m._22 > _m._11 && _m._22 > _m._33){
            s = sqrt(1.0 + _m._22 - _m._11 - _m._33) * 2.0;
            res.x = (_m._12 + _m._21) / s;
            res.y = 0.5 / s;
            res.z = (_m._23 + _m._32) / s;
            res.w = (_m._13 + _m._31) / s;
        }else if(_m._33 > _m._11 && _m._33 > _m._22){
            s = sqrt(1.0 + _m._33 - _m._11 - _m._22) * 2.0;
            res.x = (_m._13 + _m._31) / s;
            res.y = (_m._23 + _m._32) / s;
            res.z = 0.5 / s;
            res.w = (_m._12 + _m._21) / s;
        }
    }
    return res;
}


template <class T>
quat<T> quat<T>::rotation(const T& _x, const T& _y, const T& _z, const T& _angle)
{
    T sina2 = sin(_angle / 2.0);
    T cosa2 = cos(_angle / 2.0);
    
    quat<T> res;
    
    res.x = _x * sina2;
    res.y = _y * sina2;
    res.z = _z * sina2;
    res.w = cosa2;
    
    return res;
}

template <class T>
quat<T> quat<T>::rotation(const vec3<T>& _v, const T& _angle)
{
    return rotation(_v.x, _v.y, _v.z, _angle);
}

template <class T>
quat<T> quat<T>::rotation(const vec3<T>& _v1, const vec3<T>& _v2)
{
    vec3<T> _axis;
    T _angle;
    quat<T> res;
    
    _axis = normalize(cross(_v1, _v2));
    _angle = acos(dot(_v1, _v2));
    
    res = rotation(_axis, _angle);
    
    return res;
}

template <class T>
T norm(const quat<T>& q)
{
    T res = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    return res;
}

template <class T>
double magnitude(const quat<T>& q)
{
    double res = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    return res;
}

template <class T>
quat<T> conjugate(const quat<T>& q)
{
    quat<T> res;
    
    res.x = -q.x;
    res.y = -q.y;
    res.z = -q.z;
    res.w = q.w;
    
    return res;
}

template <class T>
quat<T> invert(const quat<T>& q)
{
    quat<T> res;
    
    res = conjugate(q)/norm(q);
    
    return res;
}

template <class T>
T inner(const quat<T>& q1, const quat<T>& q2)
{
    T res = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
    return res;
}

template <class T>
quat<T> normalize(const quat<T>& q) throw (Exception&)
{
    T l = magnitude(q);
    
    if(l == 0){
        Exception e("Length is equal to zero!");
        throw(e);
    }
    
    quat<T> res(q);
    
    res.x /= l;
    res.y /= l;
    res.z /= l;
    res.w /= l;
    
    return res;
}

template <class T>
quat<T> slerp(const quat<T>& _q1, const quat<T>& _q2, const T& t)
{
    #define SLERP_TO_LERP 0.001
    
    /*
    iq = (q*sin((1-t)*omega) + q'*sin(t*omega))/sin(omega),
    где cos(omega) = inner_product(q,q')
    */
    
    T inner_prod = inner(_q1, _q2);
    if(inner_prod < SLERP_TO_LERP) return lerp(_q1, _q2, t);

    quat<T> res;
    T omega = acos(inner_prod);
    
    res = (_q1 * sin((1.0 - t) * omega) + _q2 * sin(t * omega)) / sin(omega);
    
    return res;
}

template<class U>
vec4<U> operator*(const vec4<U>& _v, const quat<U>& _q)
{
    quat<U> qv(_v);
    
    quat<U> res = _q * qv * invert(_q);
    
    return res.xyzw();
}

template<class U>
vec3<U> operator*(const vec3<U>& _v, const quat<U>& _q)
{
    quat<U> qv(_v, U(0.0));
    
    quat<U> res = _q * qv * invert(_q);
    
    return res.xyz();
}

template<class U>
vec4<U> operator*(const quat<U>& _q, const vec4<U>& _v)
{
    return operator*(_v, _q);
}

template<class U>
vec3<U> operator*(const quat<U>& _q, const vec3<U>& _v)
{
    return operator*(_v, _q);
}

#endif
