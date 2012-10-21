#ifndef SHADERREADER_H
#define	SHADERREADER_H

#include "engine/engine.h"
#include "resources/reader.h"
#include "glshader/glshader.h"
#include "log/log.h"
#include <fstream>
#include <iterator>


ENGINE_NAMESPACE_BEGIN


template <typename R>
class ShaderReader
    :public Reader<R>
{
public:
    ShaderReader();
    ~ShaderReader();
    
    R* read(const std::string& filename_) const;
};


template <typename R>
ShaderReader<R>::ShaderReader()
{
}

template <typename R>
ShaderReader<R>::~ShaderReader()
{
}

template <typename R>
R* ShaderReader<R>::read(const std::string& filename_) const
{
    std::fstream ifs(filename_.c_str(), std::ios::in);
    if(!ifs) return nullptr;
    
    std::istreambuf_iterator<char> ist_beg(ifs), ist_eos;
    
    std::string source(ist_beg, ist_eos);
    
    if(source.empty()) return nullptr;
    
    R* shader = new R();
    
    shader->setSource(source);
    
    if(!shader->compile()){
        log(Log::Error) << "Error compile shader (\"" << filename_ << "\") Info log:"
                        << std::endl << shader->infoLog() << std::endl;
        delete shader;
        return nullptr;
    }
    return shader;
}


class VertexShaderReader
    :public ShaderReader<GL::VertexShader>
{
public:
    VertexShaderReader();
    ~VertexShaderReader();
};


class FragmentShaderReader
    :public ShaderReader<GL::FragmentShader>
{
public:
    FragmentShaderReader();
    ~FragmentShaderReader();
};


class GeometryShaderReader
    :public ShaderReader<GL::GeometryShader>
{
public:
    GeometryShaderReader();
    ~GeometryShaderReader();
};


class TessControlShaderReader
    :public ShaderReader<GL::TessControlShader>
{
public:
    TessControlShaderReader();
    ~TessControlShaderReader();
};


class TessEvalShaderReader
    :public ShaderReader<GL::TessEvalShader>
{
public:
    TessEvalShaderReader();
    ~TessEvalShaderReader();
};


class ComputeShaderReader
    :public ShaderReader<GL::ComputeShader>
{
public:
    ComputeShaderReader();
    ~ComputeShaderReader();
};


ENGINE_NAMESPACE_END


#endif	/* SHADERREADER_H */

