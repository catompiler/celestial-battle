#include "mesh.h"
#include <algorithm>


ENGINE_NAMESPACE_BEGIN


#define INVALID_INDEX (-1)

const std::string Mesh::attrib_index_name = "in_index";
const std::string Mesh::attrib_vertex_name = "in_vertex";
const std::string Mesh::attrib_normal_name = "in_normal";
const std::string Mesh::attrib_texuv_name = "in_texuv";
const std::string Mesh::attrib_tangent_name = "in_tangent";



Mesh::Mesh()
{
    _indices_index = INVALID_INDEX;
    _vertices_index = INVALID_INDEX;
    _normals_index = INVALID_INDEX;
    _texuvs_index = INVALID_INDEX;
    _tangents_index = INVALID_INDEX;
}

Mesh::~Mesh()
{
    
}

buffer_ptr Mesh::indices()
{
    if(_indices_index != INVALID_INDEX){
        return _attribs.at(_indices_index).second;
    }
    return buffer_ptr(NULL);
}

buffer_ptr Mesh::vertives()
{
    if(_vertices_index != INVALID_INDEX){
        return _attribs.at(_vertices_index).second;
    }
    return buffer_ptr(NULL);
}

buffer_ptr Mesh::normals()
{
    if(_normals_index != INVALID_INDEX){
        return _attribs.at(_normals_index).second;
    }
    return buffer_ptr(NULL);
}

buffer_ptr Mesh::texuvs()
{
    if(_texuvs_index != INVALID_INDEX){
        return _attribs.at(_texuvs_index).second;
    }
    return buffer_ptr(NULL);
}

buffer_ptr Mesh::tangents()
{
    if(_tangents_index != INVALID_INDEX){
        return _attribs.at(_tangents_index).second;
    }
    return buffer_ptr(NULL);
}

bool Mesh::hasAttrib(const std::string& attrib_name_)
{
    return attrib(attrib_name_) != static_cast<GL::Buffer*>(NULL);
}

buffer_ptr Mesh::attrib(const std::string& attrib_name_)
{
    int i = _getAttribIndexSorted(attrib_name_);
    if(i != INVALID_INDEX){
        return _attribs.at(i).second;
    }
    return buffer_ptr(NULL);
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
