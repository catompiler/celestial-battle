#include "gltexture.h"



OPENGL_NAMESPACE_BEGIN


Texture::Texture(GLenum target_)
{
    _target = target_;
    GL::glGenTextures(1, &_id);
}

Texture::Texture(GLenum target_, GLuint id_)
{
    _target = target_;
    _id = id_;
}

Texture::~Texture()
{
    GL::glDeleteTextures(1, &_id);
}

GLenum Texture::target() const
{
    return _target;
}

void Texture::bind()
{
    GL::glBindTexture(_target, _id);
}

void Texture::unbind()
{
    GL::glBindTexture(_target, 0);
}

GLboolean Texture::isValid(GLuint texture_)
{
    return GL::glIsTexture(texture_);
}

void Texture::setActiveTexture(GLenum texture_)
{
    GL::glActiveTexture(texture_);
}

void Texture::setActiveTextureUnit(GLuint texture_unit_)
{
    setActiveTexture(GL_TEXTURE0 + texture_unit_);
}

GLint Texture::getParameteri(GLenum pname_) const
{
    GLint res;
    GL::glGetTexParameteriv(_target, pname_, &res);
    return res;
}

GLfloat Texture::getParameterf(GLenum pname_) const
{
    GLfloat res;
    GL::glGetTexParameterfv(_target, pname_, &res);
    return res;
}

void Texture::setParameteri(GLenum pname_, GLint param_)
{
    GL::glTexParameteri(_target, pname_, param_);
}

void Texture::setParameterf(GLenum pname_, GLfloat param_)
{
    GL::glTexParameterf(_target, pname_, param_);
}

GLint Texture::minFilter() const
{
    return getParameteri(GL_TEXTURE_MIN_FILTER);
}

void Texture::setMinFilter(GLint filter_)
{
    setParameteri(GL_TEXTURE_MIN_FILTER, filter_);
}

GLint Texture::magFilter() const
{
    return getParameteri(GL_TEXTURE_MAG_FILTER);
}

void Texture::setMagFilter(GLint filter_)
{
    setParameteri(GL_TEXTURE_MAG_FILTER, filter_);
}

GLint Texture::minLod() const
{
    return getParameteri(GL_TEXTURE_MIN_LOD);
}

void Texture::setMinLod(GLint lod_)
{
    setParameteri(GL_TEXTURE_MIN_LOD, lod_);
}

GLint Texture::maxLod() const
{
    return getParameteri(GL_TEXTURE_MAX_LOD);
}

void Texture::setMaxLod(GLint lod_)
{
    setParameteri(GL_TEXTURE_MAX_LOD, lod_);
}

GLint Texture::wrapS() const
{
    return getParameteri(GL_TEXTURE_WRAP_S);
}

void Texture::setWrapS(GLint wrap_)
{
    setParameteri(GL_TEXTURE_WRAP_S, wrap_);
}

GLint Texture::wrapT() const
{
    return getParameteri(GL_TEXTURE_WRAP_T);
}

void Texture::setWrapT(GLint wrap_)
{
    setParameteri(GL_TEXTURE_WRAP_T, wrap_);
}

GLint Texture::wrapR() const
{
    return getParameteri(GL_TEXTURE_WRAP_R);
}

void Texture::setWrapR(GLint wrap_)
{
    setParameteri(GL_TEXTURE_WRAP_R, wrap_);
}

void Texture::setWrap(GLint wrap_)
{
    setWrap(wrap_, wrap_, wrap_);
}

void Texture::setWrap(GLint wraps_, GLint wrapt_, GLint wrapr_)
{
    setWrapS(wraps_);
    setWrapT(wrapt_);
    setWrapR(wrapr_);
}

GLint Texture::compareMode() const
{
    return getParameteri(GL_TEXTURE_COMPARE_MODE);
}

void Texture::setCompareMode(GLint mode_)
{
    setParameteri(GL_TEXTURE_COMPARE_MODE, mode_);
}

GLint Texture::compareFunc() const
{
    return getParameteri(GL_TEXTURE_COMPARE_FUNC);
}

void Texture::setCompareFunc(GLint func_)
{
    setParameteri(GL_TEXTURE_COMPARE_FUNC, func_);
}



Texture1D::Texture1D()
        :Texture(GL_TEXTURE_1D)
{
}

Texture1D::Texture1D(GLuint id_)
        :Texture(GL_TEXTURE_1D, id_)
{
}

Texture1D::~Texture1D()
{
}

void Texture1D::setImage(GLint level_, GLint internalFormat_, GLsizei width_,
              GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexImage1D(_target, level_, internalFormat_, width_, 0, format_, type_, data_);
}

void Texture1D::getImage(GLint level_, GLenum format_, GLenum type_, GLvoid* img_) const
{
    GL::glGetTexImage(_target, level_, format_, type_, img_);
}

void Texture1D::setSubImage(GLint level_, GLint xoffset_, GLsizei width_,
                 GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexSubImage1D(_target, level_, xoffset_, width_, format_, type_, data_);
}

void Texture1D::copyImage(GLint level_, GLenum internalformat_, 
               GLint x_, GLint y_, GLsizei width_)
{
    GL::glCopyTexImage1D(_target, level_, internalformat_, x_, y_, width_, 0);
}

void Texture1D::copySubImage(GLint level_, GLint xoffset_,
                  GLint x_, GLint y_, GLsizei width_)
{
    GL::glCopyTexSubImage1D(_target, level_, xoffset_, x_, y_, width_);
}

GLint Texture1D::getLevelParameteri(GLint level_, GLenum pname_) const
{
    GLint res;
    GL::glGetTexLevelParameteriv(_target, level_, pname_, &res);
    return res;
}

GLfloat Texture1D::getLevelParameterf(GLint level_, GLenum pname_) const
{
    GLfloat res;
    GL::glGetTexLevelParameterfv(_target, level_, pname_, &res);
    return res;
}

GLint Texture1D::maxSize()
{
    GLint res;
    GL::glGetIntegerv(GL_MAX_TEXTURE_SIZE, &res);
    return res;
}

GLsizei Texture1D::width(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_WIDTH);
}

GLint Texture1D::internalFormat(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_INTERNAL_FORMAT);
}





Texture2D::Texture2D()
        :Texture(GL_TEXTURE_2D)
{
}

Texture2D::Texture2D(GLuint id_)
        :Texture(GL_TEXTURE_2D, id_)
{
}

Texture2D::~Texture2D()
{
}

void Texture2D::setImage(GLint level_, GLint internalFormat_,
              GLsizei width_, GLsizei height_,
              GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexImage2D(_target, level_, internalFormat_, width_, height_, 0, format_, type_, data_);
}

void Texture2D::getImage(GLint level_, GLenum format_, GLenum type_, GLvoid* img_) const
{
    GL::glGetTexImage(_target, level_, format_, type_, img_);
}

void Texture2D::setSubImage(GLint level_, GLint xoffset_, GLint yoffset_,
                 GLsizei width_, GLsizei height_,
                 GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexSubImage2D(_target, level_, xoffset_, yoffset_, width_, height_,
                        format_, type_, data_);
}

void Texture2D::copyImage(GLint level_, GLenum internalformat_, 
               GLint x_, GLint y_, GLsizei width_, GLsizei height_)
{
    GL::glCopyTexImage2D(_target, level_, internalformat_, x_, y_, width_, height_, 0);
}

void Texture2D::copySubImage(GLint level_, GLint xoffset_, GLint yoffset_,
                  GLint x_, GLint y_, GLsizei width_, GLsizei height_)
{
    GL::glCopyTexSubImage2D(_target, level_, xoffset_, yoffset_, x_, y_, width_, height_);
}

GLint Texture2D::getLevelParameteri(GLint level_, GLenum pname_) const
{
    GLint res;
    GL::glGetTexLevelParameteriv(_target, level_, pname_, &res);
    return res;
}

GLfloat Texture2D::getLevelParameterf(GLint level_, GLenum pname_) const
{
    GLfloat res;
    GL::glGetTexLevelParameterfv(_target, level_, pname_, &res);
    return res;
}

GLint Texture2D::maxSize()
{
    GLint res;
    GL::glGetIntegerv(GL_MAX_TEXTURE_SIZE, &res);
    return res;
}

GLsizei Texture2D::width(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_WIDTH);
}

GLsizei Texture2D::height(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_HEIGHT);
}

GLint Texture2D::internalFormat(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_INTERNAL_FORMAT);
}





TextureCube::TextureCube()
        :Texture(GL_TEXTURE_CUBE_MAP)
{
}

TextureCube::TextureCube(GLuint id_)
        :Texture(GL_TEXTURE_CUBE_MAP, id_)
{
}

TextureCube::~TextureCube()
{
}

void TextureCube::setImage(GLenum face_, GLint level_, GLint internalFormat_,
              GLsizei width_, GLsizei height_, GLenum format_, GLenum type_,
              const GLvoid* data_)
{
    GL::glTexImage2D(face_, level_, internalFormat_, width_, height_, 0, format_, type_, data_);
}


void TextureCube::getImage(GLenum face_, GLint level_, GLenum format_, GLenum type_, GLvoid* img_) const
{
    GL::glGetTexImage(face_, level_, format_, type_, img_);
}

void TextureCube::setSubImage(GLenum face_, GLint level_, GLint xoffset_, GLint yoffset_,
                 GLsizei width_, GLsizei height_, 
                 GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexSubImage2D(face_, level_, xoffset_, yoffset_, width_, height_,
                        format_, type_, data_);
}

void TextureCube::copyImage(GLenum face_, GLint level_, GLenum internalformat_, 
               GLint x_, GLint y_, GLsizei width_, GLsizei height_)
{
    GL::glCopyTexImage2D(face_, level_, internalformat_, x_, y_, width_, height_, 0);
}

void TextureCube::copySubImage(GLenum face_, GLint level_, GLint xoffset_, GLint yoffset_, 
                  GLint x_, GLint y_, GLsizei width_, GLsizei height_)
{
    GL::glCopyTexSubImage2D(face_, level_, xoffset_, yoffset_, x_, y_, width_, height_);
}

GLint TextureCube::getLevelParameteri(GLenum face_, GLint level_, GLenum pname_) const
{
    GLint res;
    GL::glGetTexLevelParameteriv(face_, level_, pname_, &res);
    return res;
}

GLfloat TextureCube::getLevelParameterf(GLenum face_, GLint level_, GLenum pname_) const
{
    GLfloat res;
    GL::glGetTexLevelParameterfv(face_, level_, pname_, &res);
    return res;
}

GLint TextureCube::maxSize()
{
    GLint res;
    GL::glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &res);
    return res;
}

GLsizei TextureCube::width(GLenum face_, GLint level_) const
{
    return getLevelParameteri(face_, level_, GL_TEXTURE_WIDTH);
}

GLsizei TextureCube::height(GLenum face_, GLint level_) const
{
    return getLevelParameteri(face_, level_, GL_TEXTURE_HEIGHT);
}

GLint TextureCube::internalFormat(GLenum face_, GLint level_) const
{
    return getLevelParameteri(face_, level_, GL_TEXTURE_INTERNAL_FORMAT);
}





Texture3D::Texture3D()
        :Texture(GL_TEXTURE_3D)
{
}

Texture3D::Texture3D(GLuint id_)
        :Texture(GL_TEXTURE_3D, id_)
{
}

Texture3D::~Texture3D()
{
}

void Texture3D::setImage(GLint level_, GLint internalFormat_,
              GLsizei width_, GLsizei height_, GLsizei depth_,
              GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexImage3D(_target, level_, internalFormat_, width_, height_, depth_, 0, format_, type_, data_);
}

void Texture3D::getImage(GLint level_, GLenum format_, GLenum type_, GLvoid* img_) const
{
    GL::glGetTexImage(_target, level_, format_, type_, img_);
}

void Texture3D::setSubImage(GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, 
                 GLsizei width_, GLsizei height_, GLsizei depth_, 
                 GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexSubImage3D(_target, level_, xoffset_, yoffset_, zoffset_,
                        width_, height_, depth_, format_, type_, data_);
}

void Texture3D::copySubImage(GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, 
                  GLint x_, GLint y_, GLsizei width_, GLsizei height_)
{
    GL::glCopyTexSubImage3D(_target, level_, xoffset_, yoffset_, zoffset_,
                            x_, y_, width_, height_);
}

GLint Texture3D::getLevelParameteri(GLint level_, GLenum pname_) const
{
    GLint res;
    GL::glGetTexLevelParameteriv(_target, level_, pname_, &res);
    return res;
}

GLfloat Texture3D::getLevelParameterf(GLint level_, GLenum pname_) const
{
    GLfloat res;
    GL::glGetTexLevelParameterfv(_target, level_, pname_, &res);
    return res;
}

GLint Texture3D::maxSize()
{
    GLint res;
    GL::glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &res);
    return res;
}

GLsizei Texture3D::width(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_WIDTH);
}

GLsizei Texture3D::height(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_HEIGHT);
}

GLsizei Texture3D::depth(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_DEPTH);
}

GLint Texture3D::internalFormat(GLint level_) const
{
    return getLevelParameteri(level_, GL_TEXTURE_INTERNAL_FORMAT);
}






TextureRect::TextureRect()
        :Texture(GL_TEXTURE_RECTANGLE)
{
}

TextureRect::TextureRect(GLuint id_)
        :Texture(GL_TEXTURE_RECTANGLE, id_)
{
}

TextureRect::~TextureRect()
{
}

void TextureRect::setImage(GLint internalFormat_,
              GLsizei width_, GLsizei height_,
              GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexImage2D(_target, 0, internalFormat_, width_, height_, 0, format_, type_, data_);
}

void TextureRect::getImage(GLenum format_, GLenum type_, GLvoid* img_) const
{
    GL::glGetTexImage(_target, 0, format_, type_, img_);
}

void TextureRect::setSubImage(GLint xoffset_, GLint yoffset_,
                 GLsizei width_, GLsizei height_,
                 GLenum format_, GLenum type_, const GLvoid* data_)
{
    GL::glTexSubImage2D(_target, 0, xoffset_, yoffset_, width_, height_,
                        format_, type_, data_);
}

void TextureRect::copyImage(GLenum internalformat_, 
               GLint x_, GLint y_, GLsizei width_, GLsizei height_)
{
    GL::glCopyTexImage2D(_target, 0, internalformat_, x_, y_, width_, height_, 0);
}

void TextureRect::copySubImage(GLint xoffset_, GLint yoffset_,
                  GLint x_, GLint y_, GLsizei width_, GLsizei height_)
{
    GL::glCopyTexSubImage2D(_target, 0, xoffset_, yoffset_, x_, y_, width_, height_);
}

GLint TextureRect::getLevelParameteri(GLenum pname_) const
{
    GLint res;
    GL::glGetTexLevelParameteriv(_target, 0, pname_, &res);
    return res;
}

GLfloat TextureRect::getLevelParameterf(GLenum pname_) const
{
    GLfloat res;
    GL::glGetTexLevelParameterfv(_target, 0, pname_, &res);
    return res;
}

GLint TextureRect::maxSize()
{
    GLint res;
    GL::glGetIntegerv(GL_MAX_TEXTURE_SIZE, &res);
    return res;
}

GLsizei TextureRect::width() const
{
    return getLevelParameteri(GL_TEXTURE_WIDTH);
}

GLsizei TextureRect::height() const
{
    return getLevelParameteri(GL_TEXTURE_HEIGHT);
}

GLint TextureRect::internalFormat() const
{
    return getLevelParameteri(GL_TEXTURE_INTERNAL_FORMAT);
}






OPENGL_NAMESPACE_END
