#include "glshader.h" 
#include <vector>



OPENGL_NAMESPACE_BEGIN


Shader::Shader(GLenum type_)
        :Resource()
{
    _id = GL::glCreateShader(type_);
}

Shader::Shader(GLuint id_, int)
        :Resource(id_)
{
}

Shader::~Shader()
{
    GL::glDeleteShader(_id);
}

bool Shader::isValid(GLuint shader_)
{
    return GL::glIsShader(shader_);
}

GLenum Shader::type() const
{
    return getParameteri(GL_SHADER_TYPE);
}

void Shader::setSource(const std::string& source_)
{
    const GLchar* src = source_.c_str();
    GL::glShaderSource(_id, 1, &src, NULL);
}

std::string Shader::source() const
{
    std::string res;
    std::vector<char> src_str;
    
    GLint len = getParameteri(GL_SHADER_SOURCE_LENGTH);
    src_str.resize(len);
    GL::glGetShaderSource(_id, len, NULL, &src_str[0]);
    res = &src_str[0];
    
    return res;
}

bool Shader::compile()
{
    GL::glCompileShader(_id);
    return compileStatus();
}

bool Shader::compileStatus() const
{
    return getParameteri(GL_COMPILE_STATUS);
}

std::string Shader::infoLog() const
{
    std::string res;
    std::vector<char> log_str;
    
    GLint len = getParameteri(GL_INFO_LOG_LENGTH);
    log_str.resize(len);
    GL::glGetShaderInfoLog(_id, len, NULL, &log_str[0]);
    res = &log_str[0];
    
    return res;
}

GLint Shader::getParameteri(GLenum pname_) const
{
    GLint res;
    GL::glGetShaderiv(_id, pname_, &res);
    return res;
}

void Shader::releaseCompiler()
{
    GL::glReleaseShaderCompiler();
}



VertexShader::VertexShader()
        :Shader(GL_VERTEX_SHADER)
{
}

VertexShader::VertexShader(GLuint id_)
        :Shader(id_, 0)
{
}

VertexShader::~VertexShader()
{
}



FragmentShader::FragmentShader()
        :Shader(GL_FRAGMENT_SHADER)
{
}

FragmentShader::FragmentShader(GLuint id_)
        :Shader(id_, 0)
{
}

FragmentShader::~FragmentShader()
{
}



GeometryShader::GeometryShader()
        :Shader(GL_GEOMETRY_SHADER)
{
}

GeometryShader::GeometryShader(GLuint id_)
        :Shader(id_, 0)
{
}

GeometryShader::~GeometryShader()
{
}



TessControlShader::TessControlShader()
        :Shader(GL_TESS_CONTROL_SHADER)
{
}

TessControlShader::TessControlShader(GLuint id_)
        :Shader(id_, 0)
{
}

TessControlShader::~TessControlShader()
{
}



TessEvalShader::TessEvalShader()
        :Shader(GL_TESS_EVALUATION_SHADER)
{
}

TessEvalShader::TessEvalShader(GLuint id_)
        :Shader(id_, 0)
{
}

TessEvalShader::~TessEvalShader()
{
}



ComputeShader::ComputeShader()
        :Shader(GL_COMPUTE_SHADER)
{
}

ComputeShader::ComputeShader(GLuint id_)
        :Shader(id_, 0)
{
}

ComputeShader::~ComputeShader()
{
}



OPENGL_NAMESPACE_END
