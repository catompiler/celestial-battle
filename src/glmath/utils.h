#ifndef _GLUTILS_H_
#define _GLUTILS_H_

#include <math.h>


template<class T>
vec3<T> normal(const vec3<T>& v0_, const vec3<T>& v1_, const vec3<T>& v2_)
{
    return cross(v1_ - v0_, v2_ - v0_);
}

//from http://steps3d.narod.ru/tutorials/advanced-bumpmapping-tutorial.html
template<class T>
vec3<T> tangent(const vec3<T>& v0_, const vec3<T>& v1_, const vec3<T>& v2_,
                //const vec3<T>& n0_, const vec3<T>& n1_, const vec3<T>& n2_,
                const vec2<T>& t0_, const vec2<T>& t1_, const vec2<T>& t2_,
                vec3<T>* res_tangent_ = NULL, vec3<T>* res_binormal_ = NULL)
{
#define EPS 1E-6
    
    vec3<T> t, b;
    
    vec3<T> e0 ( v1_.x - v0_.x, t1_.x - t0_.x, t1_.y - t0_.y );
    vec3<T> e1 ( v2_.x - v0_.x, t2_.x - t0_.x, t2_.y - t0_.y );
    vec3<T> cp = cross(e0, e1);

    if ( fabs ( cp.x ) > EPS ){
        t.x = -cp.y / cp.x;
        b.x = -cp.z / cp.x;
    }else{
        t.x = 0;
        b.x = 0;
    }

    e0.x = v1_.y - v0_.y;
    e1.x = v2_.y - v0_.y;
    cp   = cross(e0, e1);

    if ( fabs ( cp.x ) > EPS ){
        t.y = -cp.y / cp.x;
        b.y = -cp.z / cp.x;
    }else{
        t.y = 0;
        b.y = 0;
    }

    e0.x = v1_.z - v0_.z;
    e1.x = v2_.z - v0_.z;
    cp   = cross(e0, e1);

    if ( fabs ( cp.x ) > EPS ){
        t.z = -cp.y / cp.x;
        b.z = -cp.z / cp.x;
    }else{
        t.z = 0;
        b.z = 0;
    }

    if (dot(cross(t, b), normal(v0_, v1_, v2_)) < 0){
        t = -t;
    }
    
    if(res_tangent_) *res_tangent_ = t;
    if(res_binormal_) *res_binormal_ = b;
    
    return t;
}

#endif  //_GLUTILS_H_
