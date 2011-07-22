#ifndef _GLBUFFER_H_ 
#define _GLBUFFER_H_

#include "glresource/glresource.h"
#include "opengl/opengl.h"

OPENGL_NAMESPACE_BEGIN


class Buffer
        :public Resource
{
public:
    Buffer();
    explicit Buffer(GLuint id_);
    ~Buffer();
    
    void bind(GLenum target_);
    
    static void unbind(GLenum target_);
    
    static void setData(GLenum target_, GLsizeiptr size_, const GLvoid* data_, GLenum usage_);
    static void setSubData(GLenum target_, GLintptr offset_, GLsizeiptr size_, const GLvoid* data_);
    static void getSubData(GLenum target_, GLintptr offset_, GLsizeiptr size_, GLvoid* data_);
    
    static void* map(GLenum target_, GLenum access_);
    static void* mapRange(GLenum target_, GLintptr offset_, GLsizeiptr length_, GLbitfield access_);
    static void* pointer(GLenum target_);
    static void flushRange(GLenum target_, GLintptr offset_, GLsizeiptr length_);
    static GLboolean unmap(GLenum target_);
    
    static GLboolean isValid(GLuint buffer_);
    
    static GLenum access(GLenum target_);
    static GLboolean mapped(GLenum target_);
    static GLsizeiptr size(GLenum target_);
    static GLenum usage(GLenum target_);
    
    static GLint getParameter(GLenum target_, GLenum value_);
};


OPENGL_NAMESPACE_END


#endif  //_GLBUFFER_H_
