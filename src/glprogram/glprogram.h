#ifndef _GLPROGRAM_H_
#define _GLPROGRAM_H_


#include "glresource/glresource.h"
#include "opengl/opengl.h"
#include "glmath/glmath.h"
#include <vector>
#include <stddef.h>


OPENGL_NAMESPACE_BEGIN


class Shader;


class Program
        :public Resource
{
public:
    Program();
    Program(GLuint id_);
    ~Program();
    
    void use();
    void unuse();
    
    static bool isValid(GLuint program_);
    
    void attachShader(Shader* shader_);
    void detachShader(Shader* shader_);
    
    bool link();
    bool linkStatus() const;
    
    bool validate();
    bool validateStatus() const;
    
    std::string infoLog() const;
    
    GLint getParameteri(GLenum pname_) const;
    
    
    class Uniform;
    typedef std::vector<Uniform*> Uniforms;
    typedef Uniforms::iterator UniformsIt;
    
    bool hasUniform(const std::string& name_);
    bool hasUniform(Uniform* uniform_);
    Uniform* getUniform(const std::string& name_);
    UniformsIt beginUniforms();
    UniformsIt endUniforms();
    
    class Attrib;
    typedef std::vector<Attrib*> Attribs;
    typedef Attribs::iterator AttribsIt;
    
    void bindAttribLocation(GLuint location_, const std::string& name_);
    bool hasAttrib(const std::string& name_);
    bool hasAttrib(Attrib* Attrib_);
    Attrib* getAttrib(const std::string& name_);
    AttribsIt beginAttribs();
    AttribsIt endAttribs();
    
    class Uniform{
    public:
        Uniform(Program* program_, const std::string& name_, GLenum type_,
                GLint size_, GLint location_);
        
        Program* program() const;
        const std::string& name() const;
        GLenum type() const;
        GLint location() const;
        
        void setFloat(float value_);
        void setVec2f(const vec2_t& value_);
        void setVec3f(const vec3_t& value_);
        void setVec4f(const vec4_t& value_);
        void setQuat(const quat_t& value_);
        void setMat2(const mat2_t& value_);
        void setMat3(const mat3_t& value_);
        void setMat4(const mat4_t& value_);
        void setInt(int value_);
        void setVec2i(const ivec2_t& value_);
        void setVec3i(const ivec3_t& value_);
        void setVec4i(const ivec4_t& value_);
        
        float getFloat() const;
        vec2_t getVec2f() const;
        vec3_t getVec3f() const;
        vec4_t getVec4f() const;
        quat_t getQuat() const;
        mat2_t getMat2() const;
        mat3_t getMat3() const;
        mat4_t getMat4() const;
        int getInt() const;
        ivec2_t getVec2i() const;
        ivec3_t getVec3i() const;
        ivec4_t getVec4i() const;
    private:
        GLint _location;
        GLint _size;
        GLenum _type;
        std::string _name;
        Program* _program;
    };
    
    
    class Attrib{
    public:
        Attrib(Program* program_, const std::string& name_, GLenum type_,
                GLint size_, GLuint index_);
        
        Program* program() const;
        const std::string& name() const;
        GLenum type() const;
        GLuint index() const;
        
        void pointer(GLint size_, GLenum type_, GLsizei stride_, ptrdiff_t offset_);
        void enableArray();
        void disableArray();
        
        void setFloat(float value_);
        void setVec2f(const vec2_t& value_);
        void setVec3f(const vec3_t& value_);
        void setVec4f(const vec4_t& value_);
        void setQuat(const quat_t& value_);
        void setVec4i(const ivec4_t& value_);
        
        float getFloat() const;
        vec2_t getVec2f() const;
        vec3_t getVec3f() const;
        vec4_t getVec4f() const;
        quat_t getQuat() const;
        ivec4_t getVec4i() const;
        
    private:
        GLuint _index;
        GLint _size;
        GLenum _type;
        std::string _name;
        Program* _program;
    };
    
private:
    
    template<class T>
    struct NameCmp{
        bool operator()(T* l, T* r) const{
            return l->name() < r->name();
        }
        bool operator()(const std::string& l, T* r) const{
            return l < r->name();
        }
        bool operator()(T* l, const std::string& r) const{
            return l->name() < r;
        }
    };
    
    typedef NameCmp<Uniform> UniformNameCmp;
    typedef NameCmp<Attrib> AttribNameCmp;
    
    
    Uniforms _uniforms;
    void _updateUniformsList();
    
    Attribs _attribs;
    void _updateAttribsList();
};

OPENGL_NAMESPACE_END


#endif  //_GLPROGRAM_H_
