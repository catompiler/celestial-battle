#include "material.h"

ENGINE_NAMESPACE_BEGIN


Material::Material()
{
}

Material::Material(const ParametersList& parameters_)
{
    _parameters = parameters_;
}

Material::~Material()
{
}

bool Material::hasParameter(const parameterid_t& parameterid_) const
{
    return _parameters.find(parameterid_) != _parameters.end();
}

Material::ParameterValue& Material::value(const parameterid_t& parameterid_) throw(Exception&)
{
    ParametersList::iterator it = _parameters.find(parameterid_);
    if(it == _parameters.end()){
        throw(Exception("Parameter not found"));
    }
    return (*it).second;
}

const Material::ParameterValue& Material::value(const parameterid_t& parameterid_) const throw(Exception&)
{
    ParametersList::const_iterator it = _parameters.find(parameterid_);
    if(it == _parameters.end()){
        throw(Exception("Parameter not found"));
    }
    return (*it).second;
}

void Material::setValue(const parameterid_t& parameterid_, const ParameterValue& value_)
{
    _parameters[parameterid_] = value_;
}

Material::iterator Material::parametersBegin()
{
    return _parameters.begin();
}

Material::iterator Material::parametersEnd()
{
    return _parameters.end();
}

Material::const_iterator Material::parametersBegin() const
{
    return _parameters.begin();
}

Material::const_iterator Material::parametersEnd() const
{
    return _parameters.end();
}


ENGINE_NAMESPACE_END

