#ifndef _GLRENDERBUFFER_H_
#define _GLRENDERBUFFER_H_

#include "opengl/opengl.h"
#include "glresource/glresource.h"


OPENGL_NAMESPACE_BEGIN


class RenderBuffer
        :public Resource
{
public:
    RenderBuffer();
    RenderBuffer(GLuint id_);
    ~RenderBuffer();
    
    void bind();
    void unbind();
    
    void setStorage(GLenum internalformat_, GLsizei width_, GLsizei height_);
    
    static bool isValid(GLuint id_);
    
    GLint getParameteri(GLenum pname_) const;
    
    static GLint maxSize();
    
    GLsizei width() const;
    GLsizei height() const;
    
    GLint internalFormat() const;
};


OPENGL_NAMESPACE_END

#endif  //_GLRENDERBUFFER_H_
