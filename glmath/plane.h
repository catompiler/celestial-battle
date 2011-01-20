#ifndef _PLANE_H_
#define _PLANE_H_

#include <math.h>
#include "../exception/exception.h"

#include "vec3.h"

#pragma pack(push, 1)

template <class T>
class plane{
public:

    static const size_t components_count = 4;

    plane();
    plane(const T& _a, const T& _b, const T& _c, const T& _d);
    plane(const vec3<T>& P, const vec3<T>& N);
    template <class U> plane(const plane<U>& _p);

    inline void set(const T& _a, const T& _b, const T& _c, const T& _d);

    operator T*();
    operator const T*() const;
    T& operator[] (int index) throw(Exception&);
    const T& operator[] (int index) const throw(Exception&);
    bool operator==(const plane<T>& _p) const;
    plane<T>& operator=(const plane<T>& _p);

    union{
        T p[components_count];
        struct{
            T a;
            T b;
            T c;
            T d;
        };
    };
};

#pragma pack(pop)

template <class T>
plane<T>::plane()
{
    set(T(), T(), T(), T());
}

template <class T>
plane<T>::plane(const T& _a, const T& _b, const T& _c, const T& _d)
{
    set(_a, _b, _c, _d);
}

template <class T>
plane<T>::plane(const vec3<T>& N, const vec3<T>& P)
{
    T _d = dot(N,-P);
    set(N.x, N.y, N.z, _d);
}

template <class T>
template <class U>
plane<T>::plane(const plane<U>& _p)
{
    set(T(_p.a), T(_p.b), T(_p.c), T(_p.d));
}

template <class T>
void plane<T>::set(const T& _a, const T& _b, const T& _c, const T& _d)
{
    a = _a, b = _b, c = _c, d = _d;
}

template <class T>
plane<T>::operator T*()
{
    return p;
}

template <class T>
plane<T>::operator const T*() const
{
    return p;
}

template <class T>
T& plane<T>::operator[](int index) throw(Exception&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (Exception("Index out of range!"));
    return p[index];
}

template <class T>
const T& plane<T>::operator[](int index) const throw(Exception&)
{
    if(index < 0 || static_cast<size_t>(index) >= components_count) throw (Exception("Index out of range!"));
    return p[index];
}

template <class T>
bool plane<T>::operator==(const plane<T>& _p) const
{
    return a == _p.a && b == _p.b && c == _p.c && d == _p.d;
}

template <class T>
plane<T>& plane<T>::operator=(const plane<T>& _p)
{
    set(T(_p.a), T(_p.b), T(_p.c), T(_p.d));
    return *this;
}



template <class T>
bool parallel(const plane<T>& p1, const plane<T>& p2)
{
    #define pdiv(a,b) (a == b ? 1.0 : a / b)
    #define ptest(a,b) (a != 0.0 && b == 0.0)
    
    if(ptest(p1.a, p2.a)) return false;
    if(ptest(p1.b, p2.b)) return false;
    if(ptest(p1.c, p2.c)) return false;
    
    T resa = pdiv(p1.a, p2.a);
    T resb = pdiv(p1.b, p2.b);
    T resc = pdiv(p1.c, p2.c);
    
    return resa == resb && resb == resc;
}

template <class T>
bool perpendicular(const plane<T>& p1, const plane<T>& p2)
{
    return (p1.a * p2.a + p1.b * p2.b + p1.c * p2.c) == 0;
}

template <class T>
T angle(const plane<T>& p1, const plane<T>& p2)
{
    vec3<T> p1n = vec3<T>(p1.a, p1.b, p1.c);
    vec3<T> p2n = vec3<T>(p2.a, p2.b, p2.c);
    
    T res = dot(p1n, p2n) / (length(p1n) * length(p2n));
    
    return res;
}

template <class T>
T distance(const plane<T>& p, const vec3<T>& v)
{
    vec3<T> pn = vec3<T>(p.a, p.b, p.c);
    
    T res = (dot(pn, v) + p.d) / length(pn);
    
    return res;
}

template <class T>
T distance(const plane<T>& p1, const plane<T>& p2)
{
    if(parallel(p1, p2) == false) return T(0.0);
    
    vec3<T> p1n = vec3<T>(p1.a, p1.b, p1.c);
    vec3<T> p2n = vec3<T>(p2.a, p2.b, p2.c);
    
    //T res = p2.d / length(p2n) - p1.d / length(p1n);
    T res = p1.d / length(p1n) - p2.d / length(p2n);
    
    return res;
}

#endif
