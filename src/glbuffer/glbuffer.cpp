#include "glbuffer.h"


OPENGL_NAMESPACE_BEGIN


Buffer::Buffer()
        :Resource()
{
    GL::glGenBuffers(1, &_id);
}

Buffer::Buffer(GLuint id_)
        :Resource(id_)
{
}

Buffer::~Buffer()
{
    GL::glDeleteBuffers(1, &_id);
}

void Buffer::bind(GLenum target_)
{
    GL::glBindBuffer(target_, _id);
}

void Buffer::unbind(GLenum target_)
{
    GL::glBindBuffer(target_, 0);
}

void Buffer::setData(GLenum target_, GLsizeiptr size_, const GLvoid* data_, GLenum usage_)
{
    GL::glBufferData(target_, size_, data_, usage_);
}

void Buffer::setSubData(GLenum target_, GLintptr offset_, GLsizeiptr size_, const GLvoid* data_)
{
    GL::glBufferSubData(target_, offset_, size_, data_);
}

void Buffer::getSubData(GLenum target_, GLintptr offset_, GLsizeiptr size_, GLvoid* data_)
{
    GL::glGetBufferSubData(target_, offset_, size_, data_);
}

void* Buffer::map(GLenum target_, GLenum access_)
{
    return GL::glMapBuffer(target_, access_);
}

void* Buffer::mapRange(GLenum target_, GLintptr offset_, GLsizeiptr length_, GLbitfield access_)
{
    return GL::glMapBufferRange(target_, offset_, length_, access_);
}

void* Buffer::pointer(GLenum target_)
{
    void* ptr_res;
    GL::glGetBufferPointerv(target_, GL_BUFFER_MAP_POINTER, &ptr_res);
    return ptr_res;
}

void Buffer::flushRange(GLenum target_, GLintptr offset_, GLsizeiptr length_)
{
    GL::glFlushMappedBufferRange(target_, offset_, length_);
}

GLboolean Buffer::unmap(GLenum target_)
{
    return GL::glUnmapBuffer(target_);
}

GLboolean Buffer::isValid(GLuint buffer_)
{
    return GL::glIsBuffer(buffer_);
}

GLenum Buffer::access(GLenum target_)
{
    return getParameter(target_, GL_BUFFER_ACCESS);
}

GLboolean Buffer::mapped(GLenum target_)
{
    return getParameter(target_, GL_BUFFER_MAPPED);
}

GLsizeiptr Buffer::size(GLenum target_)
{
    return getParameter(target_, GL_BUFFER_SIZE);
}

GLenum Buffer::usage(GLenum target_)
{
    return getParameter(target_, GL_BUFFER_USAGE);
}


GLint Buffer::getParameter(GLenum target_, GLenum value_)
{
    GLint res;
    GL::glGetBufferParameteriv(target_, value_, &res);
    return res;
}



OPENGL_NAMESPACE_END

