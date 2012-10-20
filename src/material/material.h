#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <string>
#include <unordered_map>
#include <utility>
#include <stddef.h>
#include "engine/engine.h"
#include "glmath/glmath.h"
#include "tlvariant/tlvariant.h"


ENGINE_NAMESPACE_BEGIN
class Material;
ENGINE_NAMESPACE_END
#include "resources/resptrs_types.h"



ENGINE_NAMESPACE_BEGIN


class Material
{
public:

    typedef tl::makeTypeList12<int, float, quat_t,
                               vec2_t, vec3_t, vec4_t,
                               ivec2_t, ivec3_t, ivec4_t,
                               mat2_t, mat3_t, mat4_t>::value ParameterValueTypes;
    typedef TLVariant<ParameterValueTypes> ParameterValue;
    typedef std::string parameterid_t;
    typedef std::unordered_map<parameterid_t, ParameterValue> ParametersList;
    
    typedef std::string textureid_t;

    Material();
    Material(const ParametersList& parameters_);
    ~Material();

    bool hasParameter(const parameterid_t& parameterid_) const;
    ParameterValue& value(const parameterid_t& parameterid_) throw(Exception&);
    const ParameterValue& value(const parameterid_t& parameterid_) const throw(Exception&);
    void setValue(const parameterid_t& parameterid_, const ParameterValue& value_);

    typedef ParametersList::iterator parameters_iterator;
    typedef ParametersList::const_iterator parameters_const_iterator;
    parameters_iterator parametersBegin();
    parameters_iterator parametersEnd();
    parameters_const_iterator parametersBegin() const;
    parameters_const_iterator parametersEnd() const;

private:
    ParametersList _parameters;
};


ENGINE_NAMESPACE_END

#endif  //_MATERIAL_H_
