#ifndef _GLTEXTURE_H_
#define _GLTEXTURE_H_

#include "opengl/opengl.h"
#include "glresource/glresource.h"


OPENGL_NAMESPACE_BEGIN


class Texture
        :public Resource
{
public:
    
    explicit Texture(GLenum target_);
    explicit Texture(GLenum target_, GLuint id_);
    ~Texture();
    
    GLenum target() const;
    
    void bind();
    void unbind();
    
    static GLboolean isValid(GLuint texture_);
    
    static void setActiveTexture(GLenum texture_);
    static void setActiveTextureUnit(GLuint texture_unit_);//same, but 0...N
    
    GLint getParameteri(GLenum pname_) const;
    GLfloat getParameterf(GLenum pname_) const;
    void setParameteri(GLenum pname_, GLint param_);
    void setParameterf(GLenum pname_, GLfloat param_);
    
protected:
    GLenum _target;
};


class Texture1D
        :public Texture
{
public:
    Texture1D();
    explicit Texture1D(GLuint id_);
    ~Texture1D();
    
    void setImage(GLint level_, GLint internalFormat_, GLsizei width_,
                  GLenum format_, GLenum type_, const GLvoid* data_);
    
    void getImage(GLint level_, GLenum format_, GLenum type_, GLvoid* img_) const;
    
    void setSubImage(GLint level_, GLint xoffset_, GLsizei width_,
                     GLenum format_, GLenum type_, const GLvoid* data_);
    
    void copyImage(GLint level_, GLenum internalformat_, 
                   GLint x_, GLint y_, GLsizei width_);
    
    void copySubImage(GLint level_, GLint xoffset_,
                      GLint x_, GLint y_, GLsizei width_);
   
    GLint getLevelParameteri(GLint level_, GLenum pname_) const;
    GLfloat getLevelParameterf(GLint level_, GLenum pname_) const;
    
    static GLint maxSize();
    
    GLsizei width(GLint level_ = 0) const;
    
    GLint internalFormat(GLint level_ = 0) const;
};

class Texture2D
        :public Texture
{
public:
    Texture2D();
    explicit Texture2D(GLuint id_);
    ~Texture2D();
    
    void setImage(GLint level_, GLint internalFormat_,
                  GLsizei width_, GLsizei height_,
                  GLenum format_, GLenum type_, const GLvoid* data_);
    
    void getImage(GLint level_, GLenum format_, GLenum type_, GLvoid* img_) const;
    
    void setSubImage(GLint level_, GLint xoffset_, GLint yoffset_,
                     GLsizei width_, GLsizei height_,
                     GLenum format_, GLenum type_, const GLvoid* data_);
    
    void copyImage(GLint level_, GLenum internalformat_, 
                   GLint x_, GLint y_, GLsizei width_, GLsizei height_);
    
    void copySubImage(GLint level_, GLint xoffset_, GLint yoffset_,
                      GLint x_, GLint y_, GLsizei width_, GLsizei height_);
   
    GLint getLevelParameteri(GLint level_, GLenum pname_) const;
    GLfloat getLevelParameterf(GLint level_, GLenum pname_) const;
    
    static GLint maxSize();
    
    GLsizei width(GLint level_ = 0) const;
    GLsizei height(GLint level_ = 0) const;
    
    GLint internalFormat(GLint level_ = 0) const;
};

class TextureCube
        :public Texture
{
public:
    TextureCube();
    explicit TextureCube(GLuint id_);
    ~TextureCube();
    
    void setImage(GLenum face_, GLint level_, GLint internalFormat_,
                  GLsizei width_, GLsizei height_, GLenum format_, GLenum type_,
                  const GLvoid* data_);
    
    void getImage(GLenum face_, GLint level_, GLenum format_, GLenum type_, GLvoid* img_) const;
    
    void setSubImage(GLenum face_, GLint level_, GLint xoffset_, GLint yoffset_,
                     GLsizei width_, GLsizei height_, 
                     GLenum format_, GLenum type_, const GLvoid* data_);
    
    void copyImage(GLenum face_, GLint level_, GLenum internalformat_, 
                   GLint x_, GLint y_, GLsizei width_, GLsizei height_);
    
    void copySubImage(GLenum face_, GLint level_, GLint xoffset_, GLint yoffset_, 
                      GLint x_, GLint y_, GLsizei width_, GLsizei height_);

    GLint getLevelParameteri(GLenum face_, GLint level_, GLenum pname_) const;
    GLfloat getLevelParameterf(GLenum face_, GLint level_, GLenum pname_) const;
    
    static GLint maxSize();
    
    GLsizei width(GLenum face_, GLint level_ = 0) const;
    GLsizei height(GLenum face_, GLint level_ = 0) const;
    
    GLint internalFormat(GLenum face_, GLint level_ = 0) const;
};

class Texture3D
        :public Texture
{
public:
    Texture3D();
    explicit Texture3D(GLuint id_);
    ~Texture3D();
    
    void setImage(GLint level_, GLint internalFormat_,
                  GLsizei width_, GLsizei height_, GLsizei depth_,
                  GLenum format_, GLenum type_, const GLvoid* data_);
    
    void getImage(GLint level_, GLenum format_, GLenum type_, GLvoid* img_) const;
    
    void setSubImage(GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, 
                     GLsizei width_, GLsizei height_, GLsizei depth_, 
                     GLenum format_, GLenum type_, const GLvoid* data_);
    
    void copySubImage(GLint level_, GLint xoffset_, GLint yoffset_, GLint zoffset_, 
                      GLint x_, GLint y_, GLsizei width_, GLsizei height_);
   
    GLint getLevelParameteri(GLint level_, GLenum pname_) const;
    GLfloat getLevelParameterf(GLint level_, GLenum pname_) const;
    
    static GLint maxSize();
    
    GLsizei width(GLint level_ = 0) const;
    GLsizei height(GLint level_ = 0) const;
    GLsizei depth(GLint level_ = 0) const;
    
    GLint internalFormat(GLint level_ = 0) const;
};



OPENGL_NAMESPACE_END

#endif  //_GLTEXTURE_H_
