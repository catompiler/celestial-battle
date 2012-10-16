#include "glrenderbuffer.h"


OPENGL_NAMESPACE_BEGIN

RenderBuffer::RenderBuffer()
        :Resource()
{
    GL::glGenRenderbuffersEXT(1, &_id);
}

RenderBuffer::RenderBuffer(GLuint id_)
        :Resource(id_)
{
}

RenderBuffer::~RenderBuffer()
{
    GL::glDeleteRenderbuffersEXT(1, &_id);
}

void RenderBuffer::bind()
{
    GL::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _id);
}

void RenderBuffer::unbind()
{
    GL::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
}

void setStorage(GLenum internalformat_, GLsizei width_, GLsizei height_)
{
    GL::glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, internalformat_, width_, height_);
}

bool RenderBuffer::isValid(GLuint id_)
{
    GL::glIsRenderbufferEXT(id_);
}

GLint RenderBuffer::getParameteri(GLenum pname_) const
{
    GLint res;
    GL::glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT, pname_, &res);
    return res;
}

GLint RenderBuffer::maxSize()
{
    GLint res;
    GL::glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &res);
    return res;
}

GLsizei RenderBuffer::width() const
{
    return getParameteri(GL_RENDERBUFFER_WIDTH_EXT);
}

GLsizei RenderBuffer::height() const
{
    return getParameteri(GL_RENDERBUFFER_HEIGHT_EXT);
}

GLint RenderBuffer::internalFormat() const
{
    return getParameteri(GL_RENDERBUFFER_INTERNAL_FORMAT_EXT);
}


OPENGL_NAMESPACE_END

