#ifndef _MAT4_H_
#define _MAT4_H_

#include <math.h>
#include "../exception/exception.h"

#include "vec4.h"
#include "quat.h"

template <class T> class quat;

#pragma pack(push, 1)

template <class T>
class mat4{
public:
    
    static const size_t components_count = 16;
    static const size_t columns_count = 4;
    static const size_t rows_count = 4;
    
    mat4();
    explicit mat4(const T& a);
    mat4(const T& _a11, const T& _a12, const T& _a13, const T& _a14,
         const T& _a21, const T& _a22, const T& _a23, const T& _a24,
         const T& _a31, const T& _a32, const T& _a33, const T& _a34,
         const T& _a41, const T& _a42, const T& _a43, const T& _a44);
    explicit mat4(T _m[components_count]);
    mat4(const vec4<T>& v1, const vec4<T>& v2, const vec4<T>& v3, const vec4<T>& v4);
    template <class U> mat4(const mat4<U>& _m);
    
    inline void set(const T& _a11, const T& _a12, const T& _a13, const T& _a14,
                    const T& _a21, const T& _a22, const T& _a23, const T& _a24,
                    const T& _a31, const T& _a32, const T& _a33, const T& _a34,
                    const T& _a41, const T& _a42, const T& _a43, const T& _a44);
    
    operator T*();
    operator const T*() const;
    T& operator[] (int index) throw(Exception&);
    const T& operator[] (int index) const throw(Exception&);
    bool operator==(const mat4<T>& _m) const;
    mat4<T>& operator=(const mat4<T>& _m);

    mat4<T>& operator+=(const mat4<T>& _m);
    mat4<T>& operator-=(const mat4<T>& _m);
    mat4<T>& operator*=(const mat4<T>& _m);
    mat4<T>& operator*=(const T& n);
    mat4<T>& operator/=(const T& n);
    template <class U> friend mat4<U> operator+(const mat4<U>& _m1, const mat4<U>& _m2);
    template <class U> friend mat4<U> operator-(const mat4<U>& _m1, const mat4<U>& _m2);
    template <class U> friend mat4<U> operator*(const mat4<U>& _m1, const mat4<U>& _m2);
    template <class U, class N> friend mat4<U> operator*(const mat4<U>& _m, const N& n);
    template <class U, class N> friend mat4<U> operator/(const mat4<U>& _m, const N& n);
    
    template <class U> friend vec4<U>& operator*=(vec4<U>& _v, const mat4<U>& _m);
    template <class U> friend vec4<U> operator*(const vec4<U>& _v, const mat4<U>& _m);
    template <class U> friend vec4<U> operator*(const mat4<U>& _m, const vec4<U>& _v);
    
    static mat4<T> identity();
    static mat4<T> translation(const vec3<T>& _v);
    static mat4<T> rotation(const quat<T>& _q);
    static mat4<T> from_quaternion(const quat<T>& _q);
    static mat4<T> rotationx(const T& angle);
    static mat4<T> rotationy(const T& angle);
    static mat4<T> rotationz(const T& angle);
    static mat4<T> scaling(const vec3<T>& _v);
    static mat4<T> scaling(const T& scalex, const T& scaley, const T& scalez);
    static mat4<T> perspective(const T& fovy, const T& aspect, const T& znear, const T& zfar);
    static mat4<T> ortho(const T& left_, const T& right_, const T& bottom_, const T& top_, const T& near_, const T& far_);
    static mat4<T> viewport(const T& x, const T& y, const T& width, const T& height, const T& zmin, const T& zmax);
    static mat4<T> lookat(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up);
    
    union{
        T mv[components_count];
        T m[rows_count][columns_count];
        struct {
            T _11, _12, _13, _14,
              _21, _22, _23, _24,
              _31, _32, _33, _34,
              _41, _42, _43, _44;
        };
    };
};

#pragma pack(pop)

template <class T>
mat4<T>::mat4()
{
    set(T(), T(), T(), T(),
        T(), T(), T(), T(),
        T(), T(), T(), T(),
        T(), T(), T(), T());
}

template <class T>
mat4<T>::mat4(const T& a)
{
    set(a, a, a, a,
        a, a, a, a,
        a, a, a, a,
        a, a, a, a);
}

template <class T>
mat4<T>::mat4(const T& _a11, const T& _a12, const T& _a13, const T& _a14,
              const T& _a21, const T& _a22, const T& _a23, const T& _a24,
              const T& _a31, const T& _a32, const T& _a33, const T& _a34,
              const T& _a41, const T& _a42, const T& _a43, const T& _a44)
{
    set(_a11, _a12, _a13, _a14,
        _a21, _a22, _a23, _a24,
        _a31, _a32, _a33, _a34,
        _a41, _a42, _a43, _a44);
}

template <class T>
mat4<T>::mat4(T _m[components_count])
{
    set(_m[0],  _m[1],  _m[2],  _m[3],
        _m[4],  _m[5],  _m[6],  _m[7],
        _m[8],  _m[9],  _m[10], _m[11],
        _m[12], _m[13], _m[14], _m[15]);
}

template <class T>
mat4<T>::mat4(const vec4<T>& v1, const vec4<T>& v2, const vec4<T>& v3, const vec4<T>& v4)
{
    set(v1.x, v1.y, v1.z, v1.w,
        v2.x, v2.y, v2.z, v2.w,
        v3.x, v3.y, v3.z, v3.w,
        v4.x, v4.y, v4.z, v4.w);
}

template <class T>
template <class U>
mat4<T>::mat4(const mat4<U>& _m)
{
    set(T(_m._11), T(_m._12), T(_m._13), T(_m._14),
        T(_m._21), T(_m._22), T(_m._23), T(_m._24),
        T(_m._31), T(_m._32), T(_m._33), T(_m._34),
        T(_m._41), T(_m._42), T(_m._43), T(_m._44));
}

template <class T>
void mat4<T>::set(const T& _a11, const T& _a12, const T& _a13, const T& _a14,
                         const T& _a21, const T& _a22, const T& _a23, const T& _a24,
                         const T& _a31, const T& _a32, const T& _a33, const T& _a34,
                         const T& _a41, const T& _a42, const T& _a43, const T& _a44)
{
    _11 = _a11;
    _12 = _a12;
    _13 = _a13;
    _14 = _a14;
    
    _21 = _a21;
    _22 = _a22;
    _23 = _a23;
    _24 = _a24;
    
    _31 = _a31;
    _32 = _a32;
    _33 = _a33;
    _34 = _a34;
    
    _41 = _a41;
    _42 = _a42;
    _43 = _a43;
    _44 = _a44;
}

template <class T>
mat4<T>::operator T*()
{
    return mv;
}

template <class T>
mat4<T>::operator const T*() const
{
    return mv;
}

template <class T>
T& mat4<T>::operator[] (int index) throw(Exception&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (Exception("Index out of range!"));
    return mv[index];
}

template <class T>
const T& mat4<T>::operator[] (int index) const throw(Exception&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (Exception("Index out of range!"));
    return mv[index];
}

template <class T>
bool mat4<T>::operator==(const mat4<T>& _m) const
{
    return _11 == _m._11 && _12 == _m._12 && _13 == _m._13 && _14 == _m._14 &&
           _21 == _m._21 && _22 == _m._22 && _23 == _m._23 && _24 == _m._24 &&
           _31 == _m._31 && _32 == _m._32 && _33 == _m._33 && _34 == _m._34 &&
           _41 == _m._41 && _42 == _m._42 && _43 == _m._43 && _44 == _m._44;
}

template <class T>
mat4<T>& mat4<T>::operator=(const mat4<T>& _m)
{
    set(_m._11, _m._12, _m._13, _m._14,
        _m._21, _m._22, _m._23, _m._24,
        _m._31, _m._32, _m._33, _m._34,
        _m._41, _m._42, _m._43, _m._44);
    
    return *this;
}

template <class T>
mat4<T>& mat4<T>::operator+=(const mat4<T>& _m)
{
    _11 += _m._11; _12 += _m._12; _13 += _m._13; _14 += _m._14;
    _21 += _m._21; _22 += _m._22; _23 += _m._23; _24 += _m._24;
    _31 += _m._31; _32 += _m._32; _33 += _m._33; _34 += _m._34;
    _41 += _m._41; _42 += _m._42; _43 += _m._43; _44 += _m._44;
    
    return *this;
}

template <class T>
mat4<T>& mat4<T>::operator-=(const mat4<T>& _m)
{
    _11 -= _m._11; _12 -= _m._12; _13 -= _m._13; _14 -= _m._14;
    _21 -= _m._21; _22 -= _m._22; _23 -= _m._23; _24 -= _m._24;
    _31 -= _m._31; _32 -= _m._32; _33 -= _m._33; _34 -= _m._34;
    _41 -= _m._41; _42 -= _m._42; _43 -= _m._43; _44 -= _m._44;
    
    return *this;
}

template <class T>
mat4<T>& mat4<T>::operator*=(const mat4<T>& _m)
{
    T a11, a12, a13, a14,
      a21, a22, a23, a24,
      a31, a32, a33, a34,
      a41, a42, a43, a44;
    
    a11 = _11 * _m._11 + _12 * _m._21 + _13 * _m._31 + _14 * _m._41;
    a12 = _11 * _m._12 + _12 * _m._22 + _13 * _m._32 + _14 * _m._42;
    a13 = _11 * _m._13 + _12 * _m._23 + _13 * _m._33 + _14 * _m._43;
    a14 = _11 * _m._14 + _12 * _m._24 + _13 * _m._34 + _14 * _m._44;
    
    a21 = _21 * _m._11 + _22 * _m._21 + _23 * _m._31 + _24 * _m._41;
    a22 = _21 * _m._12 + _22 * _m._22 + _23 * _m._32 + _24 * _m._42;
    a23 = _21 * _m._13 + _22 * _m._23 + _23 * _m._33 + _24 * _m._43;
    a24 = _21 * _m._14 + _22 * _m._24 + _23 * _m._34 + _24 * _m._44;
    
    a31 = _31 * _m._11 + _32 * _m._21 + _33 * _m._31 + _34 * _m._41;
    a32 = _31 * _m._12 + _32 * _m._22 + _33 * _m._32 + _34 * _m._42;
    a33 = _31 * _m._13 + _32 * _m._23 + _33 * _m._33 + _34 * _m._43;
    a34 = _31 * _m._14 + _32 * _m._24 + _33 * _m._34 + _34 * _m._44;
    
    a41 = _41 * _m._11 + _42 * _m._21 + _43 * _m._31 + _44 * _m._41;
    a42 = _41 * _m._12 + _42 * _m._22 + _43 * _m._32 + _44 * _m._42;
    a43 = _41 * _m._13 + _42 * _m._23 + _43 * _m._33 + _44 * _m._43;
    a44 = _41 * _m._14 + _42 * _m._24 + _43 * _m._34 + _44 * _m._44;
    
    set(a11, a12, a13, a14,
        a21, a22, a23, a24,
        a31, a32, a33, a34,
        a41, a42, a43, a44);
        
    return *this;
}

template <class T>
mat4<T>& mat4<T>::operator*=(const T& n)
{
    _11 *= n; _12 *= n; _13 *= n; _14 *= n;
    _21 *= n; _22 *= n; _23 *= n; _24 *= n;
    _31 *= n; _32 *= n; _33 *= n; _34 *= n;
    _41 *= n; _42 *= n; _43 *= n; _44 *= n;
    
    return *this;
}

template <class T>
mat4<T>& mat4<T>::operator/=(const T& n)
{
    _11 /= n; _12 /= n; _13 /= n; _14 /= n;
    _21 /= n; _22 /= n; _23 /= n; _24 /= n;
    _31 /= n; _32 /= n; _33 /= n; _34 /= n;
    _41 /= n; _42 /= n; _43 /= n; _44 /= n;
    
    return *this;
}

template <class U>
mat4<U> operator+(const mat4<U>& _m1, const mat4<U>& _m2)
{
    mat4<U> res(_m1);
    res += _m2;
    return res;
}

template <class U>
mat4<U> operator-(const mat4<U>& _m1, const mat4<U>& _m2)
{
    mat4<U> res(_m1);
    res -= _m2;
    return res;
}

template <class U>
mat4<U> operator*(const mat4<U>& _m1, const mat4<U>& _m2)
{
    mat4<U> res(_m1);
    res *= _m2;
    return res;
}

template <class U, class N>
mat4<U> operator*(const mat4<U>& _m, const N& n)
{
    mat4<U> res(_m);
    res *= n;
    return res;
}

template <class U, class N>
mat4<U> operator/(const mat4<U>& _m, const N& n)
{
    mat4<U> res(_m);
    res /= n;
    return res;
}


template <class T>
mat4<T> mat4<T>::identity()
{
    mat4<T> res;
    
    res._11 = res._22 = res._33 = res._44 = T(1.0);
    
    return res;
}

template <class T>
mat4<T> mat4<T>::translation(const vec3<T>& _v)
{
    mat4<T> res = mat4<T>::identity();

    res._41 = _v.x;
    res._42 = _v.y;
    res._43 = _v.z;
    
    return res;
}

template <class T>
mat4<T> mat4<T>::rotation(const quat<T>& _q)
{
    return from_quaternion(_q);
}

template <class T>
mat4<T> mat4<T>::from_quaternion(const quat<T>& _q)
{
    mat4<T> res;
    T xx,yy,zz,ww;
    T xy,yz,wz,wx;
    T xz,yw;

    xx=_q.x*_q.x; yy=_q.y*_q.y; zz=_q.z*_q.z; ww=_q.w*_q.w;
    xy=_q.x*_q.y; yz=_q.y*_q.z; wz=_q.w*_q.z; wx=_q.w*_q.x;
    xz=_q.x*_q.z; yw=_q.y*_q.w;

    /*xx=x*x; yy=y*y; zz=z*z; ww=w*w;
    xy=x*y; yz=y*z; wz=w*z; wx=w*x;
    xz=x*z; yw=y*w;*/

    res._11=1.0-2.0*(zz+yy); res._12=2.0*(xy-wz);     res._13=2.0*(yw+xz);      res._14=0.0;
    res._21=2.0*(xy+wz);     res._22=1.0-2.0*(zz+xx); res._23=2.0*(yz-wx);      res._24=0.0;
    res._31=2.0*(xz-yw);     res._32=2.0*(yz+wx);     res._33=1.0-2.0*(yy+xx);  res._34=0.0;
    res._41=0.0;             res._42=0.0;             res._43=0.0;              res._44=1.0;

    return res;
}

template <class T>
mat4<T> mat4<T>::rotationx(const T& angle)
{
    mat4<T> res;
    
    T cosa = cos(angle);
    T sina = sin(angle);
    
    res._22 = cosa; res._23 = -sina;
    res._32 = sina; res._33 = cosa;
    
    res._11 = res._44 = T(1.0);
    
    return res;
}

template <class T>
mat4<T> mat4<T>::rotationy(const T& angle)
{
    mat4<T> res;
    
    T cosa = cos(angle);
    T sina = sin(angle);
    
    res._11 = cosa;  res._13 = sina;
    res._31 = -sina; res._33 = cosa;
    
    res._22 = res._44 = T(1.0);
    
    return res;
}

template <class T>
mat4<T> mat4<T>::rotationz(const T& angle)
{
    mat4<T> res;
    
    T cosa = cos(angle);
    T sina = sin(angle);
    
    res._11 = cosa; res._12 = -sina;
    res._21 = sina; res._22 = cosa;
    
    res._33 = res._44 = T(1.0);
    
    return res;
}

template <class T>
mat4<T> mat4<T>::scaling(const vec3<T>& _v)
{
    return scaling(_v.x, _v.y, _v.z);
}

template <class T>
mat4<T> mat4<T>::scaling(const T& scalex, const T& scaley, const T& scalez)
{
    mat4<T> res;
    
    res._11 = scalex;
    res._22 = scaley;
    res._33 = scalez;
    
    res._44 = T(1.0);
    
    return res;
}

template <class T>
mat4<T> mat4<T>::perspective(const T& fovy, const T& aspect, const T& znear, const T& zfar)
{
    //http://www.opengl.org/sdk/docs/man/xhtml/gluPerspective.xml
    
    mat4<T> res;

    T f = 1.0 / tan(fovy * 0.5);
    T n_f = znear - zfar;

                   res._12 = 0.0; res._13 = 0.0; res._14 = 0.0;
    res._21 = 0.0;                res._23 = 0.0; res._24 = 0.0;
    res._31 = 0.0; res._32 = 0.0;
    res._41 = 0.0; res._42 = 0.0;                res._44 = 0.0;

    res._11 = f / aspect;
    res._22 = f;
    res._33 = (zfar + znear) / n_f;
    res._34 = -1.0;
    res._43 = (2.0 * zfar * znear) / n_f;
    
    return res;
}

template <class T>
mat4<T> mat4<T>::ortho(const T& left_, const T& right_, const T& bottom_, const T& top_, const T& near_, const T& far_)
{
    //http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
    
    mat4<T> res;

    T r_l = right_ - left_;
    T t_b = top_ - bottom_;
    T f_n = far_ - near_;

                   res._12 = 0.0; res._13 = 0.0; res._14 = 0.0;
    res._21 = 0.0;                res._23 = 0.0; res._24 = 0.0;
    res._31 = 0.0; res._32 = 0.0;                res._34 = 0.0;
                                                 res._44 = 1.0;

    res._11 = 2.0/r_l;
    res._22 = 2.0/t_b;
    res._33 = -2.0/f_n;

    res._41 = -(right_ + left_) / r_l;
    res._42 = -(top_ + bottom_) / t_b;
    res._43 = -(far_ + near_) / f_n;
    
    return res;
}

template <class T>
mat4<T> mat4<T>::viewport(const T& x, const T& y, const T& width, const T& height, const T& zmin, const T& zmax)
{
    mat4<T> res;
    
    T w2 = width * 0.5;
    T h2 = height * 0.5;

                   res._12 = 0.0; res._13 = 0.0; res._14 = 0.0;
    res._21 = 0.0;                res._23 = 0.0; res._24 = 0.0;
    res._31 = 0.0; res._32 = 0.0;                res._34 = 0.0;
                                                 res._44 = 1.0;

    res._11 = w2;
    res._22 = -h2;
    res._33 = zmax - zmin;
    res._41 = x + w2;
    res._42 = y + h2;
    res._43 = zmin;
    
    return res;
}

template <class T>
mat4<T> mat4<T>::lookat(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up)
{
    //http://www.opengl.org/sdk/docs/man/xhtml/gluLookAt.xml
    
    mat4<T> res;

    vec3<T> f = normalize(center - eye);
    vec3<T> up2 = normalize(up);
    vec3<T> s = cross(f, up2);
    
    up2 = cross(s, f);

                                                    res._14 = 0.0f;
                                                    res._24 = 0.0f;
                                                    res._34 = 0.0f;
    res._41 = 0.0f; res._42 = 0.0f; res._43 = 0.0f; res._44 = 1.0f;

    res._11 = s.x;
    res._12 = up2.x;
    res._13 = -f.x;

    res._21 = s.y;
    res._22 = up2.y;
    res._23 = -f.y;

    res._31 = s.z;
    res._32 = up2.z;
    res._33 = -f.z;
    
    return res;
}



template <class U>
vec4<U>& operator*=(vec4<U>& _v, const mat4<U>& _m)
{
    U x = _v.x * _m._11 + _v.y * _m._21 + _v.z * _m._31 + _v.w * _m._41;
    U y = _v.x * _m._12 + _v.y * _m._22 + _v.z * _m._32 + _v.w * _m._42;
    U z = _v.x * _m._13 + _v.y * _m._23 + _v.z * _m._33 + _v.w * _m._43;
    U w = _v.x * _m._14 + _v.y * _m._24 + _v.z * _m._34 + _v.w * _m._44;
    
    _v.x = x;
    _v.y = y;
    _v.z = z;
    _v.w = w;
    
    return _v;
}

template <class U>
vec4<U> operator*(const vec4<U>& _v, const mat4<U>& _m)
{
    vec4<U> res(_v);
    
    res *= _m;
    
    return res;
}

template <class U>
vec4<U> operator*(const mat4<U>& _m, const vec4<U>& _v)
{
    vec4<U> res;
    
    res.x = _m._11 * _v.x + _m._12 * _v.y + _m._13 * _v.z + _m._14 * _v.w;
    res.y = _m._21 * _v.x + _m._22 * _v.y + _m._23 * _v.z + _m._24 * _v.w;
    res.z = _m._31 * _v.x + _m._32 * _v.y + _m._33 * _v.z + _m._34 * _v.w;
    res.w = _m._41 * _v.x + _m._42 * _v.y + _m._43 * _v.z + _m._44 * _v.w;
    
    return res;
}

template <class T>
T determinant(const mat4<T>& _m)
{
//        a11  a12  a13  a14
//        a21  a22  a23  a24
//A  =    a31  a32  a33  a34
//        a41  a42  a43  a44

//          |a22  a23  a24|           |a12  a13  a14|          |a12  a13  a14|            |a12  a13  a14|
//D = a11 * |a32  a33  a34|  -  a21 * |a32  a33  a34|  + a31 * |a22  a23  a24|  -  a41 *  |a22  a23  a24|
//          |a42  a43  a44|           |a42  a43  a44|          |a42  a43  a44|            |a32  a33  a34|
//
    
#define determinant3x3(a11,a12,a13,a21,a22,a23,a31,a32,a33) (a11*a22*a33+a12*a23*a31+a21*a32*a13-a31*a22*a13-a12*a21*a33-a11*a23*a32)

    T res;
    T res1, res2, res3, res4;
    
    res1 = _m._11 * determinant3x3(_m._22,_m._23,_m._24,
                                   _m._32,_m._33,_m._34,
                                   _m._42,_m._43,_m._44);
    res2 = _m._21 * determinant3x3(_m._12,_m._13,_m._14,
                                   _m._32,_m._33,_m._34,
                                   _m._42,_m._43,_m._44);
    res3 = _m._31 * determinant3x3(_m._12,_m._13,_m._14,
                                   _m._22,_m._23,_m._24,
                                   _m._42,_m._43,_m._44);
    res4 = _m._41 * determinant3x3(_m._12,_m._13,_m._14,
                                   _m._22,_m._23,_m._24,
                                   _m._32,_m._33,_m._34);
    res=res1-res2+res3-res4;
    
    return res;
}

template <class T>
mat4<T> invert(const mat4<T>& _m) throw(Exception&)
{
    mat4<T> res;
    //float d=determinant(m);
    T d, invd;
    T res1, res2, res3, res4;

    res1 = determinant3x3(_m._22,_m._23,_m._24,
                          _m._32,_m._33,_m._34,
                          _m._42,_m._43,_m._44);
    res2 = determinant3x3(_m._12,_m._13,_m._14,
                          _m._32,_m._33,_m._34,
                          _m._42,_m._43,_m._44);
    res3 = determinant3x3(_m._12,_m._13,_m._14,
                          _m._22,_m._23,_m._24,
                          _m._42,_m._43,_m._44);
    res4 = determinant3x3(_m._12,_m._13,_m._14,
                          _m._22,_m._23,_m._24,
                          _m._32,_m._33,_m._34);
    d=_m._11 * res1 - _m._21 * res2 + _m._31 * res3 - _m._41 * res4;
    
    if(d == 0.0){
        Exception e("Determinant is zero!");
        throw(e);
    }
    
    invd = 1.0 / d;

    res._11 =  invd * res1;
    res._21 = -invd * determinant3x3(_m._21,_m._23,_m._24,
                                     _m._31,_m._33,_m._34,
                                     _m._41,_m._43,_m._44);
    res._31 =  invd * determinant3x3(_m._21,_m._22,_m._24,
                                     _m._31,_m._32,_m._34,
                                     _m._41,_m._42,_m._44);
    res._41 = -invd * determinant3x3(_m._21,_m._22,_m._23,
                                     _m._31,_m._32,_m._33,
                                     _m._41,_m._42,_m._43);

    res._12 = -invd * res2;
    res._22 =  invd * determinant3x3(_m._11,_m._13,_m._14,
                                     _m._31,_m._33,_m._34,
                                     _m._41,_m._43,_m._44);
    res._32 = -invd * determinant3x3(_m._11,_m._12,_m._14,
                                     _m._31,_m._32,_m._34,
                                     _m._41,_m._42,_m._44);
    res._42 =  invd * determinant3x3(_m._11,_m._12,_m._13,
                                     _m._31,_m._32,_m._33,
                                     _m._41,_m._42,_m._43);

    res._13 =  invd * res3;
    res._23 = -invd * determinant3x3(_m._11,_m._13,_m._14,
                                     _m._21,_m._23,_m._24,
                                     _m._41,_m._43,_m._44);
    res._33 =  invd * determinant3x3(_m._11,_m._12,_m._14,
                                     _m._21,_m._22,_m._24,
                                     _m._41,_m._42,_m._44);
    res._43 = -invd * determinant3x3(_m._11,_m._12,_m._13,
                                     _m._21,_m._22,_m._23,
                                     _m._41,_m._42,_m._43);

    res._14 = -invd * res4;
    res._24 =  invd * determinant3x3(_m._11,_m._13,_m._14,
                                     _m._21,_m._23,_m._24,
                                     _m._31,_m._33,_m._34);
    res._34 = -invd * determinant3x3(_m._11,_m._12,_m._14,
                                     _m._21,_m._22,_m._24,
                                     _m._31,_m._32,_m._34);
    res._44 =  invd * determinant3x3(_m._11,_m._12,_m._13,
                                     _m._21,_m._22,_m._23,
                                     _m._31,_m._32,_m._33);

    return res;
}

template <class T>
mat4<T> transpose(const mat4<T>& _m)
{
    mat4<T> res;
    
    res._11 = _m._11; res._12 = _m._21; res._13 = _m._31; res._14 = _m._41;
    res._21 = _m._12; res._22 = _m._22; res._23 = _m._32; res._24 = _m._42;
    res._31 = _m._13; res._32 = _m._23; res._33 = _m._33; res._34 = _m._43;
    res._41 = _m._14; res._42 = _m._24; res._43 = _m._34; res._14 = _m._44;
    
    return res;
}


#endif
