#ifndef _GLPATCH_H_
#define _GLPATCH_H_


#include "opengl/opengl.h"
#include <stddef.h>


OPENGL_NAMESPACE_BEGIN

class Patch
{
public:
    static void setVertices(size_t count_);
    static void setInnerLevels(float lvl0_number_, float lvl1_number_);
    static void setOuterLevels(float lvl0_number_, float lvl1_number_,
                           float lvl2_number_, float lvl3_number_);
};

OPENGL_NAMESPACE_END


#endif  //_GLPATCH_H_
