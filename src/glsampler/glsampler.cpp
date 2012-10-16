#include <GL/gl3.h>

#include "glsampler.h"


OPENGL_NAMESPACE_BEGIN


Sampler::Sampler()
    :Resource()
{
    GL::glGenSamplers(1, &_id);
}

Sampler::Sampler(GLuint id_)
    :Resource(id_)
{
}

Sampler::~Sampler()
{
    GL::glDeleteSamplers(1, &_id);
}

bool Sampler::isSampler() const
{
    return GL::glIsSampler(_id) == GL_TRUE;
}

void Sampler::bind(GLuint unit_)
{
    GL::glBindSampler(unit_, _id);
}

GLint Sampler::getParameteri(GLenum pname_) const
{
    GLint res;
    GL::glGetSamplerParameteriv(_id, pname_, &res);
    return res;
}

GLfloat Sampler::getParameterf(GLenum pname_) const
{
    GLfloat res;
    GL::glGetSamplerParameterfv(_id, pname_, &res);
    return res;
}

void Sampler::setParameteri(GLenum pname_, GLint param_)
{
    GL::glSamplerParameteri(_id, pname_, param_);
}

void Sampler::setParameterf(GLenum pname_, GLfloat param_)
{
    GL::glSamplerParameterf(_id, pname_, param_);
}

GLint Sampler::minFilter() const
{
    return getParameteri(GL_TEXTURE_MIN_FILTER);
}

void Sampler::setMinFilter(GLint filter_)
{
    setParameteri(GL_TEXTURE_MIN_FILTER, filter_);
}

GLint Sampler::magFilter() const
{
    return getParameteri(GL_TEXTURE_MAG_FILTER);
}

void Sampler::setMagFilter(GLint filter_)
{
    setParameteri(GL_TEXTURE_MAG_FILTER, filter_);
}

GLint Sampler::minLod() const
{
    return getParameteri(GL_TEXTURE_MIN_LOD);
}

void Sampler::setMinLod(GLint lod_)
{
    setParameteri(GL_TEXTURE_MIN_LOD, lod_);
}

GLint Sampler::maxLod() const
{
    return getParameteri(GL_TEXTURE_MAX_LOD);
}

void Sampler::setMaxLod(GLint lod_)
{
    setParameteri(GL_TEXTURE_MAX_LOD, lod_);
}

GLint Sampler::wrapS() const
{
    return getParameteri(GL_TEXTURE_WRAP_S);
}

void Sampler::setWrapS(GLint wrap_)
{
    setParameteri(GL_TEXTURE_WRAP_S, wrap_);
}

GLint Sampler::wrapT() const
{
    return getParameteri(GL_TEXTURE_WRAP_T);
}

void Sampler::setWrapT(GLint wrap_)
{
    setParameteri(GL_TEXTURE_WRAP_T, wrap_);
}

GLint Sampler::wrapR() const
{
    return getParameteri(GL_TEXTURE_WRAP_R);
}

void Sampler::setWrapR(GLint wrap_)
{
    setParameteri(GL_TEXTURE_WRAP_R, wrap_);
}

void Sampler::setWrap(GLint wrap_)
{
    setWrap(wrap_, wrap_, wrap_);
}

void Sampler::setWrap(GLint wraps_, GLint wrapt_, GLint wrapr_)
{
    setWrapS(wraps_);
    setWrapT(wrapt_);
    setWrapR(wrapr_);
}

GLint Sampler::compareMode() const
{
    return getParameteri(GL_TEXTURE_COMPARE_MODE);
}

void Sampler::setCompareMode(GLint mode_)
{
    setParameteri(GL_TEXTURE_COMPARE_MODE, mode_);
}

GLint Sampler::compareFunc() const
{
    return getParameteri(GL_TEXTURE_COMPARE_FUNC);
}

void Sampler::setCompareFunc(GLint func_)
{
    setParameteri(GL_TEXTURE_COMPARE_FUNC, func_);
}


OPENGL_NAMESPACE_END
