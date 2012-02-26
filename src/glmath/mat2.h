#ifndef _MAT2_H_
#define _MAT2_H_

#include <math.h>
#include "exception/badindexexception.h"

#include "vec2.h"

#pragma pack(push, 1)

template <class T>
class mat2{
public:
    
    static const size_t components_count = 4;
    static const size_t columns_count = 2;
    static const size_t rows_count = 2;
    
    mat2();
    explicit mat2(const T& a);
    mat2(const T& _a11, const T& _a12,
         const T& _a21, const T& _a22);
    explicit mat2(T _m[components_count]);
    mat2(const vec2<T>& v1, const vec2<T>& v2);
    template <class U> mat2(const mat2<U>& _m);
    
    inline void set(const T& _a11, const T& _a12,
                    const T& _a21, const T& _a22);
    
    operator T*();
    operator const T*() const;
    T& operator[] (int index) throw(BadIndexException&);
    const T& operator[] (int index) const throw(BadIndexException&);
    bool operator==(const mat2<T>& _m) const;
    mat2<T>& operator=(const mat2<T>& _m);

    mat2<T>& operator+=(const mat2<T>& _m);
    mat2<T>& operator-=(const mat2<T>& _m);
    mat2<T>& operator*=(const mat2<T>& _m);
    mat2<T>& operator*=(const T& n);
    mat2<T>& operator/=(const T& n);
    template <class U> friend mat2<U> operator+(const mat2<U>& _m1, const mat2<U>& _m2);
    template <class U> friend mat2<U> operator-(const mat2<U>& _m1, const mat2<U>& _m2);
    template <class U> friend mat2<U> operator*(const mat2<U>& _m1, const mat2<U>& _m2);
    template <class U, class N> friend mat2<U> operator*(const mat2<U>& _m, const N& n);
    template <class U, class N> friend mat2<U> operator/(const mat2<U>& _m, const N& n);
    
    template <class U> friend vec2<U>& operator*=(vec2<U>& _v, const mat2<U>& _m);
    template <class U> friend vec2<U> operator*(const vec2<U>& _v, const mat2<U>& _m);
    template <class U> friend vec2<U> operator*(const mat2<U>& _m, const vec2<U>& _v);
    
    static mat2<T> identity();
    static mat2<T> rotation(const T& angle);
    static mat2<T> scaling(const T& scalex, const T& scaley);
    
    union{
        T mv[components_count];
        T m[rows_count][columns_count];
        struct {
            T _11, _12,
              _21, _22;
        };
    };
};

#pragma pack(pop)

template <class T>
mat2<T>::mat2()
{
    set(T(), T(), T(), T());
}

template <class T>
mat2<T>::mat2(const T& a)
{
    set(a, a, a, a);
}

template <class T>
mat2<T>::mat2(const T& _a11, const T& _a12,
     const T& _a21, const T& _a22)
{
    set(_a11, _a12,
        _a21, _a22);
}

template <class T>
mat2<T>::mat2(T _m[components_count])
{
    set(_m[0], _m[1],
        _m[2], _m[3]);
}

template <class T>
mat2<T>::mat2(const vec2<T>& v1, const vec2<T>& v2)
{
    set(v1.x, v1.y,
        v2.x, v2.y);
}

template <class T>
template <class U>
mat2<T>::mat2(const mat2<U>& _m)
{
    set(T(_m._11), T(_m._12),
        T(_m._21), T(_m._22));
}

template <class T>
void mat2<T>::set(const T& _a11, const T& _a12,
                const T& _a21, const T& _a22)
{
    _11 = _a11;
    _12 = _a12;
    _21 = _a21;
    _22 = _a22;
}

template <class T>
mat2<T>::operator T*()
{
    return mv;
}

template <class T>
mat2<T>::operator const T*() const
{
    return mv;
}

template <class T>
T& mat2<T>::operator[] (int index) throw(BadIndexException&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (BadIndexException("Index out of range!"));
    return mv[index];
}

template <class T>
const T& mat2<T>::operator[] (int index) const throw(BadIndexException&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (BadIndexException("Index out of range!"));
    return mv[index];
}

template <class T>
bool mat2<T>::operator==(const mat2<T>& _m) const
{
    return _11 == _m._11 && _12 == _m._12 &&
           _21 == _m._21 && _22 == _m._22;
}

template <class T>
mat2<T>& mat2<T>::operator=(const mat2<T>& _m)
{
    set(_m._11, _m._12,
        _m._21, _m._22);
    
    return *this;
}

template <class T>
mat2<T>& mat2<T>::operator+=(const mat2<T>& _m)
{
    _11 += _m._11; _12 += _m._12;
    _21 += _m._21; _22 += _m._22;
    
    return *this;
}

template <class T>
mat2<T>& mat2<T>::operator-=(const mat2<T>& _m)
{
    _11 -= _m._11; _12 -= _m._12;
    _21 -= _m._21; _22 -= _m._22;
    
    return *this;
}

template <class T>
mat2<T>& mat2<T>::operator*=(const mat2<T>& _m)
{
    T a11, a12, a21, a22;
    
    a11 = _11 * _m._11 + _12 * _m._21;
    a12 = _11 * _m._12 + _12 * _m._22;
    a21 = _21 * _m._11 + _22 * _m._21;
    a22 = _21 * _m._12 + _22 * _m._22;
    
    set(a11, a12,
        a21, a22);
    
    return *this;
}

template <class T>
mat2<T>& mat2<T>::operator*=(const T& n)
{
    _11 *= n; _12 *= n;
    _21 *= n; _22 *= n;
    
    return *this;
}

template <class T>
mat2<T>& mat2<T>::operator/=(const T& n)
{
    _11 /= n; _12 /= n;
    _21 /= n; _22 /= n;
    
    return *this;
}

template <class U>
mat2<U> operator+(const mat2<U>& _m1, const mat2<U>& _m2)
{
    mat2<U> res(_m1);
    res += _m2;
    return res;
}

template <class U>
mat2<U> operator-(const mat2<U>& _m1, const mat2<U>& _m2)
{
    mat2<U> res(_m1);
    res -= _m2;
    return res;
}

template <class U>
mat2<U> operator*(const mat2<U>& _m1, const mat2<U>& _m2)
{
    mat2<U> res(_m1);
    res *= _m2;
    return res;
}

template <class U, class N>
mat2<U> operator*(const mat2<U>& _m, const N& n)
{
    mat2<U> res(_m);
    res *= n;
    return res;
}

template <class U, class N>
mat2<U> operator/(const mat2<U>& _m, const N& n)
{
    mat2<U> res(_m);
    res /= n;
    return res;
}



template <class T>
mat2<T> mat2<T>::identity()
{
    mat2<T> res;
    
    res._11 = res._22 = T(1.0);
    
    return res;
}

template <class T>
mat2<T> mat2<T>::rotation(const T& angle)
{
    mat2<T> res;
    
    T cosa = cos(angle);
    T sina = sin(angle);
    
    res._11 = cosa; res._12 = -sina;
    res._21 = sina; res._22 = cosa;
    
    return res;
}

template <class T>
mat2<T> mat2<T>::scaling(const T& scalex, const T& scaley)
{
    mat2<T> res;
    
    res._11 = scalex;
    res._22 = scaley;
    
    return res;
}



template <class U>
vec2<U>& operator*=(vec2<U>& _v, const mat2<U>& _m)
{
    U x = _v.x * _m._11 + _v.y * _m._21;
    U y = _v.x * _m._12 + _v.y * _m._22;
    
    _v.x = x;
    _v.y = y;
    
    return _v;
}

template <class U>
vec2<U> operator*(const vec2<U>& _v, const mat2<U>& _m)
{
    vec2<U> res(_v);
    
    res *= _m;
    
    return res;
}

template <class U>
vec2<U> operator*(const mat2<U>& _m, const vec2<U>& _v)
{
    vec2<U> res;
    
    res.x = _m._11 * _v.x + _m._12 * _v.y;
    res.y = _m._21 * _v.x + _m._22 * _v.y;
    
    return res;
}

template <class T>
T determinant(const mat2<T>& _m)
{
    T res = _m._11 * _m._22 - _m._12 * _m._21;
    return res;
}

template <class T>
mat2<T> invert(const mat2<T>& _m) throw(BadIndexException&)
{
    T d = determinant(_m);
    
    if(d == 0.0){
        BadIndexException e("Determinant is zero!");
        throw(e);
    }
    
    T invd = 1.0 / d;
    
    mat2<T> res;
    
    res._11 =  invd * _m._22;
    res._12 = -invd * _m._21;
    res._21 = -invd * _m._12;
    res._22 =  invd * _m._11;
    
    return res;
}

template <class T>
mat2<T> transpose(const mat2<T>& _m)
{
    mat2<T> res;
    
    res._11 = _m._11; res._12 = _m._21;
    res._21 = _m._12; res._22 = _m._22;
    
    return res;
}

#endif
