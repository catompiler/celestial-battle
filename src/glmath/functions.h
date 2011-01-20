#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <math.h>
#include <algorithm>
/*#include "../exception/exception.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"*/

/*template <class T, class U>
vec4<T> operator*(const U& n, const vec4<T>& _v)
{
    return _v * n;
}*/

template <class T>
T radians(const T& degr)
{
    return M_PI / 180.0 * degr;
}

template <class T>
T degrees(const T& rads)
{
    return 180.0 / M_PI * rads;
}

template <class T>
T fract(const T& n)
{
    return n - floor(n);
}

template <class T>
T clamp(const T& x, const T& minVal, const T& maxVal)
{
    return std::min(std::max(x, minVal), maxVal);
}

template <class T, class U>
quat<T> lerp(const T& _i1, const T& _i2, const U& t)
{
    T res;
    
    res = _i1 * (1.0 - t) + _i2 * t;
    
    return res;
}

template <class T, class U>
inline T mix(const T& _i1, const T& _i2, const U& t)
{
    return lerp(_i1, _i2, t);
}

template <class T>
T faceforward(const T& N, const T& I, const T& Nref)
{
    if(dot(Nref, I) < 0.0)
        return N;
    else
        return -N;
}

template <class T>
T reflect(const T& I, const T& N)
{
        T res = I - 2.0 * dot(N, I) * N;
        return res;
}

template <class T, class U>
T refract(const T& I, const T& N, const U& eta)
{
        T res;
        
        U NdI = dot(N, I);
        U k = 1.0 - eta * eta * (1.0 - NdI * NdI);
        
        if(k < 0.0)
            res = T(0.0);
        else
            res = eta * I - (eta * NdI + sqrt(k)) * N;
        
        return res;
}

#endif
