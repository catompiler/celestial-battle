#include "glpatch.h"

OPENGL_NAMESPACE_BEGIN


void Patch::setVertices(size_t count_)
{
    GL::glPatchParameteri(GL_PATCH_VERTICES, static_cast<GLint>(count_));
}
void Patch::setInnerLevels(float lvl0_number_, float lvl1_number_)
{
    float numbers[2] = {lvl0_number_, lvl1_number_};
    GL::glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, numbers);
}
void Patch::setOuterLevels(float lvl0_number_, float lvl1_number_,
                       float lvl2_number_, float lvl3_number_)
{
    float numbers[4] = {lvl0_number_, lvl1_number_,
                        lvl2_number_, lvl3_number_};
    GL::glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, numbers);
}


OPENGL_NAMESPACE_END
