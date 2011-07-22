#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "glmath/glmath.h"
#include "engine/engine.h"
#include <ostream>

ENGINE_NAMESPACE_BEGIN


struct Transform{

    Transform();
    Transform(const vec3_t& position_);
    Transform(const vec3_t& position_,
              const quat_t& rotation_);
    Transform(const vec3_t& position_,
              const quat_t& rotation_,
              const vec3_t& scaling_);
    Transform(const Transform& transform_);
    
    void set(const vec3_t& position_, const quat_t& rotation_, const vec3_t& scaling_);
    
    mat4_t matrixPos() const;
    mat4_t matrixRot() const;
    mat4_t matrixScale() const;
    mat4_t matrixPosRot() const;
    mat4_t matrix() const;
    
    Transform& operator=(const Transform& transform_);
    Transform& operator+=(const Transform& transform_);
    Transform& operator-=(const Transform& transform_);
    friend Transform operator+(const Transform& t1_, const Transform& t2_);
    friend Transform operator-(const Transform& t1_, const Transform& t2_);
    
    vec3_t position;
    quat_t rotation;
    vec3_t scaling;
};


Transform operator+(const Transform& t1_, const Transform& t2_);
Transform operator-(const Transform& t1_, const Transform& t2_);


ENGINE_NAMESPACE_END

#endif  //_TRANSFORM_H_
