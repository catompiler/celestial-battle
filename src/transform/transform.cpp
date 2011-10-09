#include "transform.h"

ENGINE_NAMESPACE_BEGIN



Transform::Transform()
{
    position = vec3_t(0.0, 0.0, 0.0);
    rotation = quat_t::identity();
    scaling = vec3_t(1.0, 1.0, 1.0);
}

Transform::Transform(const vec3_t& position_)
{
    position = position_;
    rotation = quat_t::identity();
    scaling = vec3_t(1.0, 1.0, 1.0);
}

Transform::Transform(const quat_t& rotation_)
{
    position = vec3_t(0.0, 0.0, 0.0);
    rotation = rotation_;
    scaling = vec3_t(1.0, 1.0, 1.0);
}

Transform::Transform(const vec3_t& position_,
                     const quat_t& rotation_)
{
    position = position_;
    rotation = rotation_;
    scaling = vec3_t(1.0, 1.0, 1.0);
}

Transform::Transform(const vec3_t& position_,
                     const quat_t& rotation_,
                     const vec3_t& scaling_)
{
    position = position_;
    rotation = rotation_;
    scaling = scaling_;
}

Transform::Transform(const Transform& transform_)
{
    position = transform_.position;
    rotation = transform_.rotation;
    scaling = transform_.scaling;
}

void Transform::set(const vec3_t& position_, const quat_t& rotation_, const vec3_t& scaling_)
{
    position = position_;
    rotation = rotation_;
    scaling = scaling_;
}

mat4_t Transform::matrixPos() const
{
    return mat4_t::translation(position);
}

mat4_t Transform::matrixRot() const
{
    return mat4_t::rotation(rotation);
}

mat4_t Transform::matrixScale() const
{
    return mat4_t::scaling(scaling);
}

mat4_t Transform::matrixPosRot() const
{
    mat4_t res = mat4_t::translation(position) *
                 mat4_t::rotation(rotation);
    return res;
}

mat4_t Transform::matrix() const
{
    mat4_t res = mat4_t::translation(position) *
                 mat4_t::rotation(rotation) *
                 mat4_t::scaling(scaling);
    return res;
}

bool Transform::operator==(const Transform& transform_)
{
    return position == transform_.position &&
           rotation == transform_.rotation &&
           scaling == transform_.scaling;
}

bool Transform::operator!=(const Transform& transform_)
{
    return !operator==(transform_);
}

Transform& Transform::operator=(const Transform& transform_)
{
    position = transform_.position;
    rotation = transform_.rotation;
    scaling = transform_.scaling;
}

Transform& Transform::operator+=(const Transform& transform_)
{
    position += rotation * transform_.position;
    rotation *= transform_.rotation;
    scaling *= transform_.scaling;
    
    return *this;
}

Transform& Transform::operator-=(const Transform& transform_)
{
    try{
        scaling /= transform_.scaling;
    }catch(...){
        scaling = vec3_t(1.0, 1.0, 1.0);
    }
    
    rotation *= conjugate(transform_.rotation);
    position -= rotation * transform_.position;
    
    return *this;
}

Transform operator+(const Transform& t1_, const Transform& t2_)
{
    Transform res(t1_);
    
    res += t2_;
    
    return res;
}

Transform operator-(const Transform& t1_, const Transform& t2_)
{
    Transform res(t1_);
    
    res -= t2_;
    
    return res;
}


ENGINE_NAMESPACE_END
