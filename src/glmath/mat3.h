#ifndef _MAT3_H_
#define _MAT3_H_

#include <math.h>
#include "../exception/exception.h"
#include "vec3.h"
#include "quat.h"

template <class T> class quat;

#pragma pack(push, 1)

template <class T>
class mat3{
public:
    
    static const size_t components_count = 9;
    static const size_t columns_count = 3;
    static const size_t rows_count = 3;
    
    mat3();
    explicit mat3(const T& a);
    mat3(const T& _a11, const T& _a12, const T& _a13,
         const T& _a21, const T& _a22, const T& _a23,
         const T& _a31, const T& _a32, const T& _a33);
    explicit mat3(T _m[components_count]);
    mat3(const vec3<T>& v1, const vec3<T>& v2, const vec3<T>& v3);
    template <class U> mat3(const mat3<U>& _m);
    
    inline void set(const T& _a11, const T& _a12, const T& _a13,
                    const T& _a21, const T& _a22, const T& _a23,
                    const T& _a31, const T& _a32, const T& _a33);
    
    operator T*();
    operator const T*() const;
    T& operator[] (int index) throw(Exception&);
    const T& operator[] (int index) const throw(Exception&);
    bool operator==(const mat3<T>& _m) const;
    mat3<T>& operator=(const mat3<T>& _m);

    mat3<T>& operator+=(const mat3<T>& _m);
    mat3<T>& operator-=(const mat3<T>& _m);
    mat3<T>& operator*=(const mat3<T>& _m);
    mat3<T>& operator*=(const T& n);
    mat3<T>& operator/=(const T& n);
    template <class U> friend mat3<U> operator+(const mat3<U>& _m1, const mat3<U>& _m2);
    template <class U> friend mat3<U> operator-(const mat3<U>& _m1, const mat3<U>& _m2);
    template <class U> friend mat3<U> operator*(const mat3<U>& _m1, const mat3<U>& _m2);
    template <class U, class N> friend mat3<U> operator*(const mat3<U>& _m, const N& n);
    template <class U, class N> friend mat3<U> operator/(const mat3<U>& _m, const N& n);
    
    template <class U> friend vec3<U>& operator*=(vec3<U>& _v, const mat3<U>& _m);
    template <class U> friend vec3<U> operator*(const vec3<U>& _v, const mat3<U>& _m);
    template <class U> friend vec3<U> operator*(const mat3<U>& _m, const vec3<U>& _v);
    
    static mat3<T> identity();
    static mat3<T> from_quaternion(const quat<T>& _q);
    static mat3<T> rotationx(const T& angle);
    static mat3<T> rotationy(const T& angle);
    static mat3<T> rotationz(const T& angle);
    static mat3<T> scaling(const T& scalex, const T& scaley, const T& scalez);
    
    union{
        T mv[components_count];
        T m[rows_count][columns_count];
        struct {
            T _11, _12, _13,
              _21, _22, _23,
              _31, _32, _33;
        };
    };
};

#pragma pack(pop)

template <class T>
mat3<T>::mat3()
{
    set(T(), T(), T(),
        T(), T(), T(),
        T(), T(), T());
}

template <class T>
mat3<T>::mat3(const T& a)
{
    set(a, a, a,
        a, a, a,
        a, a, a);
}

template <class T>
mat3<T>::mat3(const T& _a11, const T& _a12, const T& _a13,
              const T& _a21, const T& _a22, const T& _a23,
              const T& _a31, const T& _a32, const T& _a33)
{
    set(_a11, _a12, _a13,
        _a21, _a22, _a23,
        _a31, _a32, _a33);
}

template <class T>
mat3<T>::mat3(T _m[components_count])
{
    set(_m[0], _m[1], _m[2],
        _m[3], _m[4], _m[5],
        _m[6], _m[7], _m[8]);
}

template <class T>
mat3<T>::mat3(const vec3<T>& v1, const vec3<T>& v2, const vec3<T>& v3)
{
    set(v1.x, v1.y, v1.z,
        v2.x, v2.y, v2.z,
        v3.x, v3.y, v3.z);
}

template <class T>
template <class U>
mat3<T>::mat3(const mat3<U>& _m)
{
    set(T(_m._11), T(_m._12), T(_m._13),
        T(_m._21), T(_m._22), T(_m._23),
        T(_m._31), T(_m._32), T(_m._33));
}

template <class T>
void mat3<T>::set(const T& _a11, const T& _a12, const T& _a13,
                         const T& _a21, const T& _a22, const T& _a23,
                         const T& _a31, const T& _a32, const T& _a33)
{
    _11 = _a11;
    _12 = _a12;
    _13 = _a13;
    
    _21 = _a21;
    _22 = _a22;
    _23 = _a23;
    
    _31 = _a31;
    _32 = _a32;
    _33 = _a33;
}

template <class T>
mat3<T>::operator T*()
{
    return mv;
}

template <class T>
mat3<T>::operator const T*() const
{
    return mv;
}

template <class T>
T& mat3<T>::operator[] (int index) throw(Exception&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (Exception("Index out of range!"));
    return mv[index];
}

template <class T>
const T& mat3<T>::operator[] (int index) const throw(Exception&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (Exception("Index out of range!"));
    return mv[index];
}

template <class T>
bool mat3<T>::operator==(const mat3<T>& _m) const
{
    return _11 == _m._11 && _12 == _m._12 && _13 == _m._13 &&
           _21 == _m._21 && _22 == _m._22 && _23 == _m._23 &&
           _31 == _m._31 && _32 == _m._32 && _33 == _m._33;
}

template <class T>
mat3<T>& mat3<T>::operator=(const mat3<T>& _m)
{
    set(_m._11, _m._12, _m._13,
        _m._21, _m._22, _m._23,
        _m._31, _m._32, _m._33);
    
    return *this;
}

template <class T>
mat3<T>& mat3<T>::operator+=(const mat3<T>& _m)
{
    _11 += _m._11; _12 += _m._12; _13 += _m._13;
    _21 += _m._21; _22 += _m._22; _23 += _m._23;
    _31 += _m._31; _32 += _m._32; _33 += _m._33;
    
    return *this;
}

template <class T>
mat3<T>& mat3<T>::operator-=(const mat3<T>& _m)
{
    _11 -= _m._11; _12 -= _m._12; _13 -= _m._13;
    _21 -= _m._21; _22 -= _m._22; _23 -= _m._23;
    _31 -= _m._31; _32 -= _m._32; _33 -= _m._33;
    
    return *this;
}

template <class T>
mat3<T>& mat3<T>::operator*=(const mat3<T>& _m)
{
    T a11, a12, a13,
      a21, a22, a23,
      a31, a32, a33;
    
    a11 = _11 * _m._11 + _12 * _m._21 + _13 * _m._31;
    a12 = _11 * _m._12 + _12 * _m._22 + _13 * _m._32;
    a13 = _11 * _m._13 + _12 * _m._23 + _13 * _m._33;
    
    a21 = _21 * _m._11 + _22 * _m._21 + _23 * _m._31;
    a22 = _21 * _m._12 + _22 * _m._22 + _23 * _m._32;
    a23 = _21 * _m._13 + _22 * _m._23 + _23 * _m._33;
    
    a31 = _31 * _m._11 + _32 * _m._21 + _33 * _m._31;
    a32 = _31 * _m._12 + _32 * _m._22 + _33 * _m._32;
    a33 = _31 * _m._13 + _32 * _m._23 + _33 * _m._33;
    
    set(a11, a12, a13,
        a21, a22, a23,
        a31, a32, a33);
    
    return *this;
}

template <class T>
mat3<T>& mat3<T>::operator*=(const T& n)
{
    _11 *= n; _12 *= n; _13 *= n;
    _21 *= n; _22 *= n; _23 *= n;
    _31 *= n; _32 *= n; _33 *= n;
    
    return *this;
}

template <class T>
mat3<T>& mat3<T>::operator/=(const T& n)
{
    _11 /= n; _12 /= n; _13 /= n;
    _21 /= n; _22 /= n; _23 /= n;
    _31 /= n; _32 /= n; _33 /= n;
    
    return *this;
}

template <class U>
mat3<U> operator+(const mat3<U>& _m1, const mat3<U>& _m2)
{
    mat3<U> res(_m1);
    res += _m2;
    return res;
}

template <class U>
mat3<U> operator-(const mat3<U>& _m1, const mat3<U>& _m2)
{
    mat3<U> res(_m1);
    res -= _m2;
    return res;
}

template <class U>
mat3<U> operator*(const mat3<U>& _m1, const mat3<U>& _m2)
{
    mat3<U> res(_m1);
    res *= _m2;
    return res;
}

template <class U, class N>
mat3<U> operator*(const mat3<U>& _m, const N& n)
{
    mat3<U> res(_m);
    res *= n;
    return res;
}

template <class U, class N>
mat3<U> operator/(const mat3<U>& _m, const N& n)
{
    mat3<U> res(_m);
    res /= n;
    return res;
}



template <class T>
mat3<T> mat3<T>::identity()
{
    mat3<T> res;
    
    res._11 = res._22 = res._33 = T(1.0);
    
    return res;
}

template <class T>
mat3<T> mat3<T>::from_quaternion(const quat<T>& _q)
{
    mat3<T> res;
    T xx,yy,zz,ww;
    T xy,yz,wz,wx;
    T xz,yw;

    xx=_q.x*_q.x; yy=_q.y*_q.y; zz=_q.z*_q.z; ww=_q.w*_q.w;
    xy=_q.x*_q.y; yz=_q.y*_q.z; wz=_q.w*_q.z; wx=_q.w*_q.x;
    xz=_q.x*_q.z; yw=_q.y*_q.w;

    /*xx=x*x; yy=y*y; zz=z*z; ww=w*w;
    xy=x*y; yz=y*z; wz=w*z; wx=w*x;
    xz=x*z; yw=y*w;*/

    res._11=1.0-2.0*(zz+yy); res._12=2.0*(xy-wz);     res._13=2.0*(yw+xz);      //res._14=0.0;
    res._21=2.0*(xy+wz);     res._22=1.0-2.0*(zz+xx); res._23=2.0*(yz-wx);      //res._24=0.0;
    res._31=2.0*(xz-yw);     res._32=2.0*(yz+wx);     res._33=1.0-2.0*(yy+xx);  //res._34=0.0;
    //res._41=0.0;             res._42=0.0;             res._43=0.0;              res._44=1.0;

    return res;
}

template <class T>
mat3<T> mat3<T>::rotationx(const T& angle)
{
    mat3<T> res;
    
    T cosa = cos(angle);
    T sina = sin(angle);
    
    res._22 = cosa; res._23 = -sina;
    res._32 = sina; res._33 = cosa;
    
    res._11 = T(1.0);
    
    return res;
}

template <class T>
mat3<T> mat3<T>::rotationy(const T& angle)
{
    mat3<T> res;
    
    T cosa = cos(angle);
    T sina = sin(angle);
    
    res._11 = cosa;  res._13 = sina;
    res._31 = -sina; res._33 = cosa;
    
    res._22 = T(1.0);
    
    return res;
}

template <class T>
mat3<T> mat3<T>::rotationz(const T& angle)
{
    mat3<T> res;
    
    T cosa = cos(angle);
    T sina = sin(angle);
    
    res._11 = cosa; res._12 = -sina;
    res._21 = sina; res._22 = cosa;
    
    res._33 = T(1.0);
    
    return res;
}

template <class T>
mat3<T> mat3<T>::scaling(const T& scalex, const T& scaley, const T& scalez)
{
    mat3<T> res;
    
    res._11 = scalex;
    res._22 = scaley;
    res._33 = scalez;
    
    return res;
}



template <class U>
vec3<U>& operator*=(vec3<U>& _v, const mat3<U>& _m)
{
    U x = _v.x * _m._11 + _v.y * _m._21 + _v.z * _m._31;
    U y = _v.x * _m._12 + _v.y * _m._22 + _v.z * _m._32;
    U z = _v.x * _m._13 + _v.y * _m._23 + _v.z * _m._33;
    
    _v.x = x;
    _v.y = y;
    _v.z = z;
    
    return _v;
}

template <class U>
vec3<U> operator*(const vec3<U>& _v, const mat3<U>& _m)
{
    vec3<U> res(_v);
    
    res *= _m;
    
    return res;
}

template <class U>
vec3<U> operator*(const mat3<U>& _m, const vec3<U>& _v)
{
    vec3<U> res;
    
    res.x = _m._11 * _v.x + _m._12 * _v.y + _m._13 * _v.z;
    res.y = _m._21 * _v.x + _m._22 * _v.y + _m._23 * _v.z;
    res.z = _m._31 * _v.x + _m._32 * _v.y + _m._33 * _v.z;
    
    return res;
}

template <class T>
T determinant(const mat3<T>& _m)
{
    T res = _m._11*_m._22*_m._33+
          _m._12*_m._23*_m._31+
          _m._21*_m._32*_m._13-
          _m._31*_m._22*_m._13-
          _m._12*_m._21*_m._33-
          _m._11*_m._23*_m._32;
    return res;
}

template <class T>
mat3<T> invert(const mat3<T>& _m) throw(Exception&)
{
    T d = determinant(_m);
    
    if(d == 0.0){
        Exception e("Determinant is zero!");
        throw(e);
    }
    
    T invd = 1.0 / d;
    
    mat3<T> res;
    
    res._11 =  invd * ( _m._22*_m._33 - _m._23*_m._32 );
    res._12 = -invd * ( _m._12*_m._33 - _m._32*_m._13 );
    res._13 =  invd * ( _m._12*_m._23 - _m._22*_m._13 );

    res._21 = -invd * ( _m._21*_m._33 - _m._23*_m._31 );
    res._22 =  invd * ( _m._11*_m._33 - _m._31*_m._13 );
    res._23 = -invd * ( _m._11*_m._23 - _m._21*_m._13 );

    res._31 =  invd * ( _m._21*_m._32 - _m._31*_m._22 );
    res._32 = -invd * ( _m._11*_m._32 - _m._31*_m._12 );
    res._33 =  invd * ( _m._11*_m._22 - _m._12*_m._21 );
    
    return res;
}

template <class T>
mat3<T> transpose(const mat3<T>& _m)
{
    mat3<T> res;
    
    res._11 = _m._11; res._12 = _m._21; res._13 = _m._31;
    res._21 = _m._12; res._22 = _m._22; res._23 = _m._32;
    res._31 = _m._13; res._32 = _m._23; res._33 = _m._33;
    
    return res;
}

#endif
