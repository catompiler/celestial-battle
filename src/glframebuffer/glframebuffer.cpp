#include "glframebuffer.h"
#include "glrenderbuffer/glrenderbuffer.h"
#include "gltexture/gltexture.h"



OPENGL_NAMESPACE_BEGIN


FrameBuffer::FrameBuffer()
        :Resource()
{
    GL::glGenFramebuffersEXT(1, &_id);
}

FrameBuffer::FrameBuffer(GLuint id_)
        :Resource(id_)
{
}

FrameBuffer::~FrameBuffer()
{
    GL::glDeleteFramebuffersEXT(1, &_id);
}

void FrameBuffer::bind()
{
    GL::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _id);
}

void FrameBuffer::unbind()
{
    GL::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

bool FrameBuffer::isValid(GLuint fb_)
{
    return GL::glIsFramebufferEXT(fb_);
}

GLenum FrameBuffer::status() const
{
    return GL::glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
}

void FrameBuffer::attach(GLenum attachment_, RenderBuffer* rb_)
{
    GL::glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, attachment_, GL_RENDERBUFFER_EXT, rb_->id());
}

void FrameBuffer::attach(GLenum attachment_, Texture1D* tex_, GLint level_)
{
    GL::glFramebufferTexture1DEXT(GL_FRAMEBUFFER_EXT, attachment_, tex_->target(), tex_->id(), level_);
}

void FrameBuffer::attach(GLenum attachment_, Texture2D* tex_, GLint level_)
{
    GL::glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attachment_, tex_->target(), tex_->id(), level_);
}

void FrameBuffer::attach(GLenum attachment_, TextureCube* tex_, GLenum face_, GLint level_)
{
    GL::glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attachment_, face_, tex_->id(), level_);
}

void FrameBuffer::attach(GLenum attachment_, Texture3D* tex_, GLint layer_, GLint level_)
{
    GL::glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, attachment_, tex_->target(), tex_->id(), level_, layer_);
}

void FrameBuffer::detach(GLenum attachment_)
{
    GLint objtype = getAttachmentParameteri(attachment_, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT);
    switch(objtype){
        case GL_RENDERBUFFER_EXT:
            GL::glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, attachment_, 0, 0);
            break;
        case GL_TEXTURE:
            GL::glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, attachment_, 0, 0, 0);
            break;
        default:
            break;
    }
}

GLint FrameBuffer::getAttachmentParameteri(GLenum attachment_, GLenum pname_) const
{
    GLint res;
    GL::glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT, attachment_, pname_, &res);
    return res;
}

GLint FrameBuffer::maxColorAttachments()
{
    GLint res;
    GL::glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &res);
    return res;
}


OPENGL_NAMESPACE_END

