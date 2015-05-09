#include "material.h"
#include "exception/notfoundexception.h"


ENGINE_NAMESPACE_BEGIN


Material::Material()
{
}

Material::Material(const ParametersList& parameters_)
{
    _parameters = parameters_;
}

Material::Material(const TexturesList& textures_)
{
    _textures = textures_;
}

Material::Material(const ParametersList& parameters_, const TexturesList& textures_)
{
    _parameters = parameters_;
    _textures = textures_;
}

Material::~Material()
{
}

bool Material::hasParameter(const parameterid_t& parameterid_) const
{
    return _parameters.find(parameterid_) != _parameters.end();
}

Material::ParameterValue& Material::value(const parameterid_t& parameterid_)
{
    ParametersList::iterator it = _parameters.find(parameterid_);
    if(it == _parameters.end()){
        throw(NotFoundException("Parameter not found"));
    }
    return (*it).second;
}

const Material::ParameterValue& Material::value(const parameterid_t& parameterid_) const
{
    ParametersList::const_iterator it = _parameters.find(parameterid_);
    if(it == _parameters.end()){
        throw(NotFoundException("Parameter not found"));
    }
    return (*it).second;
}

void Material::setValue(const parameterid_t& parameterid_, const ParameterValue& value_)
{
    _parameters[parameterid_] = value_;
}

void Material::clearParameters()
{
    _parameters.clear();
}

Material::parameters_iterator Material::parametersBegin()
{
    return _parameters.begin();
}

Material::parameters_iterator Material::parametersEnd()
{
    return _parameters.end();
}

Material::parameters_const_iterator Material::parametersBegin() const
{
    return _parameters.begin();
}

Material::parameters_const_iterator Material::parametersEnd() const
{
    return _parameters.end();
}

bool Material::hasTexture(const textureid_t& textureid_) const
{
    return _textures.find(textureid_) != _textures.end();
}

texture_ptr Material::texture(const textureid_t& textureid_)
{
    TexturesList::iterator it = _textures.find(textureid_);
    if(it == _textures.end()){
        throw(NotFoundException("Texture not found"));
    }
    return (*it).second;
}

const texture_ptr Material::texture(const textureid_t& textureid_) const
{
    TexturesList::const_iterator it = _textures.find(textureid_);
    if(it == _textures.end()){
        throw(NotFoundException("Texture not found"));
    }
    return (*it).second;
}

void Material::setTexture(const textureid_t& textureid_, texture_ptr texture_)
{
    _textures[textureid_] = texture_;
}

void Material::clearTextures()
{
    _textures.clear();
}

Material::textures_iterator Material::texturesBegin()
{
    return _textures.begin();
}

Material::textures_iterator Material::texturesEnd()
{
    return _textures.end();
}

Material::textures_const_iterator Material::texturesBegin() const
{
    return _textures.begin();
}

Material::textures_const_iterator Material::texturesEnd() const
{
    return _textures.end();
}

bool Material::hasProgram() const
{
    return _program != nullptr;
}

program_ptr Material::program()
{
    return _program;
}

const program_ptr Material::program() const
{
    return _program;
}

void Material::setProgram(program_ptr program_)
{
    _program = program_;
}


ENGINE_NAMESPACE_END

