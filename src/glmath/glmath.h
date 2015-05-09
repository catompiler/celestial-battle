#ifndef _GLMATH_H_
#define _GLMATH_H_

#include <math.h>
//#include "../exception/exception.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include "mat2.h"
#include "mat3.h"
#include "mat4.h"

#include "quat.h"

#include "line.h"

#include "plane.h"

#include "functions.h"

#include "utils.h"

typedef vec2<float> vec2_t;
typedef vec3<float> vec3_t;
typedef vec4<float> vec4_t;

typedef vec2<int> ivec2_t;
typedef vec3<int> ivec3_t;
typedef vec4<int> ivec4_t;

typedef mat2<float> mat2_t;
typedef mat3<float> mat3_t;
typedef mat4<float> mat4_t;

typedef quat<float> quat_t;

typedef line<vec3_t> line_t;

typedef plane<float> plane_t;

#endif
