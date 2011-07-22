#ifndef _GLFRAMEBUFFER_H_
#define _GLFRAMEBUFFER_H_

#include "opengl/opengl.h"
#include "glresource/glresource.h"



OPENGL_NAMESPACE_BEGIN


class Texture1D;
class Texture2D;
class TextureCube;
class Texture3D;
class RenderBuffer;


class FrameBuffer
        :public Resource
{
public:
    FrameBuffer();
    FrameBuffer(GLuint id_);
    ~FrameBuffer();
    
    void bind();
    void unbind();
    
    static bool isValid(GLuint fb_);
    
    GLenum status() const;
    
    void attach(GLenum attachment_, RenderBuffer* rb_);
    void attach(GLenum attachment_, Texture1D* tex_, GLint level_);
    void attach(GLenum attachment_, Texture2D* tex_, GLint level_);
    void attach(GLenum attachment_, TextureCube* tex_, GLenum face_, GLint level_);
    void attach(GLenum attachment_, Texture3D* tex_, GLint layer_, GLint level_);
    void detach(GLenum attachment_);
    
    GLint getAttachmentParameteri(GLenum attachment_, GLenum pname_) const;
    
    static GLint maxColorAttachments();
};


OPENGL_NAMESPACE_END

#endif  //_GLFRAMEBUFFER_H_
