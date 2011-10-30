#ifndef _GLSHADER_H_
#define _GLSHADER_H_

#include "glresource/glresource.h"
#include "opengl/opengl.h"
#include <string>


OPENGL_NAMESPACE_BEGIN


class Shader
        :public Resource
{
public:
    Shader(GLenum type_);
    Shader(GLuint id_, int);
    ~Shader();
    
    static bool isValid(GLuint shader_);
    
    GLenum type() const;
    
    void setSource(const std::string& source_);
    std::string source() const;
    
    bool compile();
    bool compileStatus() const;
    
    std::string infoLog() const;
    
    GLint getParameteri(GLenum pname_) const;
};


class VertexShader
        :public Shader
{
public:
    VertexShader();
    VertexShader(GLuint id_);
    ~VertexShader();
};



class FragmentShader
        :public Shader
{
public:
    FragmentShader();
    FragmentShader(GLuint id_);
    ~FragmentShader();
};


OPENGL_NAMESPACE_END

#endif  //_GLSHADER_H_
