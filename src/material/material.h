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
    typedef ParametersList::iterator parameters_iterator;
    typedef ParametersList::const_iterator parameters_const_iterator;
    
    typedef std::string textureid_t;
    typedef std::unordered_map<parameterid_t, texture_ptr> TexturesList;
    typedef TexturesList::iterator textures_iterator;
    typedef TexturesList::const_iterator textures_const_iterator;

    Material();
    Material(const ParametersList& parameters_);
    Material(const TexturesList& textures_);
    Material(const ParametersList& parameters_, const TexturesList& textures_);
    ~Material();

    bool hasParameter(const parameterid_t& parameterid_) const;
    ParameterValue& value(const parameterid_t& parameterid_);//throw(Exception&);
    const ParameterValue& value(const parameterid_t& parameterid_) const;// throw(Exception&);
    void setValue(const parameterid_t& parameterid_, const ParameterValue& value_);
    void clearParameters();

    parameters_iterator parametersBegin();
    parameters_iterator parametersEnd();
    parameters_const_iterator parametersBegin() const;
    parameters_const_iterator parametersEnd() const;
    
    bool hasTexture(const textureid_t& textureid_) const;
    texture_ptr texture(const textureid_t& textureid_);
    const texture_ptr texture(const textureid_t& textureid_) const;
    void setTexture(const textureid_t& textureid_, texture_ptr texture_);
    void clearTextures();
    
    textures_iterator texturesBegin();
    textures_iterator texturesEnd();
    textures_const_iterator texturesBegin() const;
    textures_const_iterator texturesEnd() const;

private:
    ParametersList _parameters;
    TexturesList _textures;
};


ENGINE_NAMESPACE_END

#endif  //_MATERIAL_H_
