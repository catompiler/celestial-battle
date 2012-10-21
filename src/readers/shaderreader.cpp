#include "shaderreader.h"



ENGINE_NAMESPACE_BEGIN



VertexShaderReader::VertexShaderReader()
    :ShaderReader<GL::VertexShader>()
{
}

VertexShaderReader::~VertexShaderReader()
{
}



FragmentShaderReader::FragmentShaderReader()
    :ShaderReader<GL::FragmentShader>()
{
}

FragmentShaderReader::~FragmentShaderReader()
{
}



GeometryShaderReader::GeometryShaderReader()
    :ShaderReader<GL::GeometryShader>()
{
}

GeometryShaderReader::~GeometryShaderReader()
{
}



TessControlShaderReader::TessControlShaderReader()
    :ShaderReader<GL::TessControlShader>()
{
}

TessControlShaderReader::~TessControlShaderReader()
{
}



TessEvalShaderReader::TessEvalShaderReader()
    :ShaderReader<GL::TessEvalShader>()
{
}
TessEvalShaderReader::~TessEvalShaderReader()
{
}



ComputeShaderReader::ComputeShaderReader()
    :ShaderReader<GL::ComputeShader>()
{
}

ComputeShaderReader::~ComputeShaderReader()
{
}




ENGINE_NAMESPACE_END

