#include "mesh.h"
#include <algorithm>


ENGINE_NAMESPACE_BEGIN


#define INVALID_INDEX (-1)

const std::string Mesh::attrib_vertex_name = "in_vertex";
const std::string Mesh::attrib_normal_name = "in_normal";
const std::string Mesh::attrib_texuv_name = "in_texuv";
const std::string Mesh::attrib_tangent_name = "in_tangent";



Mesh::Mesh()
{
    _vertices_index = INVALID_INDEX;
    _normals_index = INVALID_INDEX;
    _texuvs_index = INVALID_INDEX;
    _tangents_index = INVALID_INDEX;
}

Mesh::~Mesh()
{
    
}

GL::Buffer* Mesh::indices()
{
    return _indices;
}

GL::Buffer* Mesh::vertives()
{
    if(_vertices_index != INVALID_INDEX){
        return _attribs.at(_vertices_index).second;
    }
    return NULL;
}

GL::Buffer* Mesh::normals()
{
    if(_normals_index != INVALID_INDEX){
        return _attribs.at(_normals_index).second;
    }
    return NULL;
}

GL::Buffer* Mesh::texuvs()
{
    if(_texuvs_index != INVALID_INDEX){
        return _attribs.at(_texuvs_index).second;
    }
    return NULL;
}

GL::Buffer* Mesh::tangents()
{
    if(_tangents_index != INVALID_INDEX){
        return _attribs.at(_tangents_index).second;
    }
    return NULL;
}

bool Mesh::hasAttrib(const std::string& attrib_name_)
{
    return attrib(attrib_name_) != NULL;
}

GL::Buffer* Mesh::attrib(const std::string& attrib_name_)
{
    int i = _getAttribIndexSorted(attrib_name_);
    if(i != INVALID_INDEX){
        return _attribs.at(i).second;
    }
    return NULL;
}

void Mesh::_resortAttribs()
{
    std::sort(_attribs.begin(), _attribs.end(), PairFirstCmp());
    _vertices_index = _getAttribIndexSorted(attrib_vertex_name);
    _normals_index = _getAttribIndexSorted(attrib_normal_name);
    _texuvs_index = _getAttribIndexSorted(attrib_texuv_name);
    _tangents_index = _getAttribIndexSorted(attrib_tangent_name);
}

int Mesh::_getAttribIndexSorted(const std::string& attrib_name_)
{
    std::pair<AttribsIt, AttribsIt> range = std::equal_range(_attribs.begin(), _attribs.end(),
                                                             attrib_name_, PairFirstCmp());
    AttribsIt::difference_type d = std::distance(range.first, range.second);
    if(d == 1){
        return std::distance(_attribs.begin(), range.first);//(*(range.first)).second;
    }
    return INVALID_INDEX;
}

ENGINE_NAMESPACE_END
