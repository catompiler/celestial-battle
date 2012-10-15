#ifndef _GLSAMPLER_H_ 
#define _GLSAMPLER_H_

#include "opengl/opengl.h"
#include "glresource/glresource.h"


OPENGL_NAMESPACE_BEGIN


class Sampler
    :public Resource
{
public:
    Sampler();
    Sampler(GLuint id_);
    ~Sampler();
    
    bool isSampler() const;
    
    void bind(GLuint unit_);
    
    GLint getParameteri(GLenum pname_) const;
    GLfloat getParameterf(GLenum pname_) const;
    void setParameteri(GLenum pname_, GLint param_);
    void setParameterf(GLenum pname_, GLfloat param_);
    
    GLint minFilter() const;
    void setMinFilter(GLint filter_);
    
    GLint magFilter() const;
    void setMagFilter(GLint filter_);
    
    GLint minLod() const;
    void setMinLod(GLint lod_);
    
    GLint maxLod() const;
    void setMaxLod(GLint lod_);
    
    GLint wrapS() const;
    void setWrapS(GLint wrap_);
    
    GLint wrapT() const;
    void setWrapT(GLint wrap_);
    
    GLint wrapR() const;
    void setWrapR(GLint wrap_);
    
    void setWrap(GLint wrap_);
    void setWrap(GLint wraps_, GLint wrapt_, GLint wrapr_);
    
    GLint compareMode() const;
    void setCompareMode(GLint mode_);
    
    GLint compareFunc() const;
    void setCompareFunc(GLint func_);
};





OPENGL_NAMESPACE_END

#endif  //_GLSAMPLER_H_
