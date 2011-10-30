#include "glprogram.h"
#include "glshader/glshader.h"
#include "utils/utils.h"
#include <vector>
#include <utility>
#include <iterator>


OPENGL_NAMESPACE_BEGIN



Program::Program()
        :Resource()
{
    _id = GL::glCreateProgram();
}

Program::Program(GLuint id_)
        :Resource(id_)
{
}

Program::~Program()
{
    GL::glDeleteProgram(_id);
    std::for_each(_uniforms.begin(), _uniforms.end(), functors::delete_single());
    std::for_each(_attribs.begin(), _attribs.end(), functors::delete_single());
}

void Program::use()
{
    GL::glUseProgram(_id);
}

void Program::unuse()
{
    GL::glUseProgram(0);
}

bool Program::isValid(GLuint program_)
{
    return GL::glIsProgram(program_);
}

void Program::attachShader(Shader* shader_)
{
    GL::glAttachShader(_id, shader_->id());
}

void Program::detachShader(Shader* shader_)
{
    GL::glDetachShader(_id, shader_->id());
}

bool Program::link()
{
    GL::glLinkProgram(_id);
    _updateUniformsList();
    _updateAttribsList();
    return linkStatus();
}

bool Program::linkStatus() const
{
    return getParameteri(GL_LINK_STATUS);
}

bool Program::validate()
{
    GL::glValidateProgram(_id);
    return validateStatus();
}

bool Program::validateStatus() const
{
    return getParameteri(GL_VALIDATE_STATUS);
}

std::string Program::infoLog() const
{
    std::string res;
    std::vector<char> log_str;
    
    GLint len = getParameteri(GL_INFO_LOG_LENGTH);
    log_str.resize(len);
    GL::glGetProgramInfoLog(_id, len, NULL, &log_str[0]);
    res = &log_str[0];
    
    return res;
}

GLint Program::getParameteri(GLenum pname_) const
{
    GLint res;
    GL::glGetProgramiv(_id, pname_, &res);
    return res;
}

bool Program::hasUniform(const std::string& name_)
{
    return getUniform(name_) != NULL;
}

bool Program::hasUniform(Uniform* uniform_)
{
    UniformsIt it = std::find(_uniforms.begin(), _uniforms.end(), uniform_);
    if(it != _uniforms.end()) return true;
    return false;
}

Program::Uniform* Program::getUniform(const std::string& name_)
{
    std::pair<UniformsIt, UniformsIt> range = std::equal_range(_uniforms.begin(), _uniforms.end(),
                                                               name_, UniformNameCmp());
    UniformsIt::difference_type d = std::distance(range.first, range.second);
    if(d == 1){
        return *(range.first);
    }
    return NULL;
}

Program::UniformsIt Program::beginUniforms()
{
    return _uniforms.begin();
}

Program::UniformsIt Program::endUniforms()
{
    return _uniforms.end();
}

void Program::_updateUniformsList()
{
    int count = getParameteri(GL_ACTIVE_UNIFORMS);
    int name_max_len = getParameteri(GL_ACTIVE_UNIFORM_MAX_LENGTH);
    
    std::for_each(_uniforms.begin(), _uniforms.end(), functors::delete_single());
    _uniforms.clear();
    
    GLenum uniform_type = 0;
    GLint uniform_size = 0;
    GLint uniform_loc = -1;
    std::vector<char> buf_name;
    buf_name.resize(name_max_len);
    
    Uniform* u;
    
    for(int i = 0; i < count; i++){
        GL::glGetActiveUniform(_id, i, name_max_len, NULL,
                               &uniform_size, &uniform_type, &buf_name[0]);
        uniform_loc = GL::glGetUniformLocation(_id, &buf_name[0]);
        if(uniform_loc == -1) continue;
        u = new Uniform(this, std::string(&buf_name[0]),
                        uniform_type, uniform_size, uniform_loc);
        _uniforms.push_back(u);
    }
    
    std::sort(_uniforms.begin(), _uniforms.end(), UniformNameCmp());
}

void Program::bindAttribLocation(GLuint location_, const std::string& name_)
{
    GL::glBindAttribLocation(_id, location_, name_.c_str());
}

bool Program::hasAttrib(const std::string& name_)
{
    return getAttrib(name_) != NULL;
}

bool Program::hasAttrib(Attrib* Attrib_)
{
    AttribsIt it = std::find(_attribs.begin(), _attribs.end(), Attrib_);
    if(it != _attribs.end()) return true;
    return false;
}

Program::Attrib* Program::getAttrib(const std::string& name_)
{
    std::pair<AttribsIt, AttribsIt> range = std::equal_range(_attribs.begin(), _attribs.end(),
                                                               name_, AttribNameCmp());
    AttribsIt::difference_type d = std::distance(range.first, range.second);
    if(d == 1){
        return *(range.first);
    }
    return NULL;
}

Program::AttribsIt Program::beginAttribs()
{
    return _attribs.begin();
}

Program::AttribsIt Program::endAttribs()
{
    return _attribs.end();
}

void Program::_updateAttribsList()
{
    int count = getParameteri(GL_ACTIVE_ATTRIBUTES);
    int name_max_len = getParameteri(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
    
    std::for_each(_attribs.begin(), _attribs.end(), functors::delete_single());
    _attribs.clear();
    
    GLenum attrib_type = 0;
    GLint attrib_size = 0;
    GLuint attrib_loc = static_cast<GLuint>(-1);
    std::vector<char> buf_name;
    buf_name.resize(name_max_len);
    
    Attrib* a;
    
    for(int i = 0; i < count; i++){
        GL::glGetActiveAttrib(_id, i, name_max_len, NULL,
                               &attrib_size, &attrib_type, &buf_name[0]);
        attrib_loc = GL::glGetAttribLocation(_id, &buf_name[0]);
        if(attrib_loc == -1) continue;
        a = new Attrib(this, std::string(&buf_name[0]),
                        attrib_type, attrib_size, attrib_loc);
        _attribs.push_back(a);
    }
    
    std::sort(_attribs.begin(), _attribs.end(), AttribNameCmp());
}



Program::Uniform::Uniform(Program* program_, const std::string& name_, GLenum type_,
        GLint size_, GLint location_)
{
    _program = program_;
    _name = name_;
    _type = type_;
    _size = size_;
    _location = location_;
}

Program* Program::Uniform::program() const
{
    return _program;
}

const std::string& Program::Uniform::name() const
{
    return _name;
}

GLenum Program::Uniform::type() const
{
    return _type;
}

GLint Program::Uniform::location() const
{
    return _location;
}

void Program::Uniform::setFloat(float value_)
{
    GL::glUniform1fv(_location, 1, &value_);
}

void Program::Uniform::setVec2f(const vec2_t& value_)
{
    GL::glUniform2fv(_location, 1, value_.v);
}

void Program::Uniform::setVec3f(const vec3_t& value_)
{
    GL::glUniform3fv(_location, 1, value_.v);
}

void Program::Uniform::setVec4f(const vec4_t& value_)
{
    GL::glUniform4fv(_location, 1, value_.v);
}

void Program::Uniform::setQuat(const quat_t& value_)
{
    GL::glUniform4fv(_location, 1, value_.q);
}

void Program::Uniform::setMat2(const mat2_t& value_)
{
    GL::glUniformMatrix2fv(_location, 1, GL_FALSE, value_.mv);
}

void Program::Uniform::setMat3(const mat3_t& value_)
{
    GL::glUniformMatrix3fv(_location, 1, GL_FALSE, value_.mv);
}

void Program::Uniform::setMat4(const mat4_t& value_)
{
    GL::glUniformMatrix4fv(_location, 1, GL_FALSE, value_.mv);
}

void Program::Uniform::setInt(int value_)
{
    GL::glUniform1iv(_location, 1, &value_);
}

void Program::Uniform::setVec2i(const ivec2_t& value_)
{
    GL::glUniform2iv(_location, 1, value_.v);
}

void Program::Uniform::setVec3i(const ivec3_t& value_)
{
    GL::glUniform3iv(_location, 1, value_.v);
}

void Program::Uniform::setVec4i(const ivec4_t& value_)
{
    GL::glUniform4iv(_location, 1, value_.v);
}

float Program::Uniform::getFloat() const
{
    float res;
    GL::glGetUniformfv(_program->id(), _location, &res);
    return res;
}

vec2_t Program::Uniform::getVec2f() const
{
    vec2_t res;
    GL::glGetUniformfv(_program->id(), _location, res.v);
    return res;
}

vec3_t Program::Uniform::getVec3f() const
{
    vec3_t res;
    GL::glGetUniformfv(_program->id(), _location, res.v);
    return res;
}

vec4_t Program::Uniform::getVec4f() const
{
    vec4_t res;
    GL::glGetUniformfv(_program->id(), _location, res.v);
    return res;
}

quat_t Program::Uniform::getQuat() const
{
    quat_t res;
    GL::glGetUniformfv(_program->id(), _location, res.q);
    return res;
}

mat2_t Program::Uniform::getMat2() const
{
    mat2_t res;
    GL::glGetUniformfv(_program->id(), _location, res.mv);
    return res;
}

mat3_t Program::Uniform::getMat3() const
{
    mat3_t res;
    GL::glGetUniformfv(_program->id(), _location, res.mv);
    return res;
}

mat4_t Program::Uniform::getMat4() const
{
    mat4_t res;
    GL::glGetUniformfv(_program->id(), _location, res.mv);
    return res;
}

int Program::Uniform::getInt() const
{
    int res;
    GL::glGetUniformiv(_program->id(), _location, &res);
    return res;
}

ivec2_t Program::Uniform::getVec2i() const
{
    ivec2_t res;
    GL::glGetUniformiv(_program->id(), _location, res.v);
    return res;
}

ivec3_t Program::Uniform::getVec3i() const
{
    ivec3_t res;
    GL::glGetUniformiv(_program->id(), _location, res.v);
    return res;
}

ivec4_t Program::Uniform::getVec4i() const
{
    ivec4_t res;
    GL::glGetUniformiv(_program->id(), _location, res.v);
    return res;
}



Program::Attrib::Attrib(Program* program_, const std::string& name_, GLenum type_,
        GLint size_, GLuint index_)
{
    _program = program_;
    _name = name_;
    _type = type_;
    _size = size_;
    _index = index_;
}

Program* Program::Attrib::program() const
{
    return _program;
}

const std::string& Program::Attrib::name() const
{
    return _name;
}

GLenum Program::Attrib::type() const
{
    return _type;
}

GLuint Program::Attrib::index() const
{
    return _index;
}

void Program::Attrib::pointer(GLint size_, GLenum type_, GLsizei stride_, ptrdiff_t offset_)
{
    GL::glVertexAttribPointer(_index, size_, type_, GL_FALSE, stride_,
                              reinterpret_cast<const GLvoid*>(offset_));
}

void Program::Attrib::enableArray()
{
    GL::glEnableVertexAttribArray(_index);
}

void Program::Attrib::disableArray()
{
    GL::glDisableVertexAttribArray(_index);
}

void Program::Attrib::setFloat(float value_)
{
    GL::glVertexAttrib1fv(_index, &value_);
}

void Program::Attrib::setVec2f(const vec2_t& value_)
{
    GL::glVertexAttrib2fv(_index, value_.v);
}

void Program::Attrib::setVec3f(const vec3_t& value_)
{
    GL::glVertexAttrib3fv(_index, value_.v);
}

void Program::Attrib::setVec4f(const vec4_t& value_)
{
    GL::glVertexAttrib4fv(_index, value_.v);
}

void Program::Attrib::setQuat(const quat_t& value_)
{
    GL::glVertexAttrib4fv(_index, value_.q);
}

void Program::Attrib::setVec4i(const ivec4_t& value_)
{
    GL::glVertexAttrib4iv(_index, value_.v);
}

float Program::Attrib::getFloat() const
{
    vec4_t v;
    GL::glGetVertexAttribfv(_index, GL_CURRENT_VERTEX_ATTRIB, v.v);
    return v.x;
}

vec2_t Program::Attrib::getVec2f() const
{
    vec4_t v;
    GL::glGetVertexAttribfv(_index, GL_CURRENT_VERTEX_ATTRIB, v.v);
    return v.xy();
}

vec3_t Program::Attrib::getVec3f() const
{
    vec4_t v;
    GL::glGetVertexAttribfv(_index, GL_CURRENT_VERTEX_ATTRIB, v.v);
    return v.xyz();
}

vec4_t Program::Attrib::getVec4f() const
{
    vec4_t v;
    GL::glGetVertexAttribfv(_index, GL_CURRENT_VERTEX_ATTRIB, v.v);
    return v;
}

quat_t Program::Attrib::getQuat() const
{
    quat_t q;
    GL::glGetVertexAttribfv(_index, GL_CURRENT_VERTEX_ATTRIB, q.q);
    return q;
}

ivec4_t Program::Attrib::getVec4i() const
{
    ivec4_t v;
    GL::glGetVertexAttribiv(_index, GL_CURRENT_VERTEX_ATTRIB, v.v);
    return v;
}




OPENGL_NAMESPACE_END


