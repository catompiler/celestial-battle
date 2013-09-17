#include "mesh.h"
#include "exception/notfoundexception.h"


ENGINE_NAMESPACE_BEGIN


const Mesh::attribid_t Mesh::attrib_index_id = "in_index";
const Mesh::attribid_t Mesh::attrib_vertex_id = "in_vertex";
const Mesh::attribid_t Mesh::attrib_normal_id = "in_normal";
const Mesh::attribid_t Mesh::attrib_texuv_id = "in_texuv";
const Mesh::attribid_t Mesh::attrib_tangent_id = "in_tangent";



Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

buffer_ptr Mesh::indices()
{
    return attrib(attrib_index_id);
}

void Mesh::setIndices(buffer_ptr indices_)
{
    setAttrib(attrib_index_id, indices_);
}

buffer_ptr Mesh::vertives()
{
    return attrib(attrib_vertex_id);
}

void Mesh::setVertices(buffer_ptr vertices_)
{
    setAttrib(attrib_vertex_id, vertices_);
}

buffer_ptr Mesh::normals()
{
    return attrib(attrib_normal_id);
}

void Mesh::setNormals(buffer_ptr normals_)
{
    setAttrib(attrib_normal_id, normals_);
}

buffer_ptr Mesh::texuvs()
{
    return attrib(attrib_texuv_id);
}

void Mesh::setTexuvs(buffer_ptr texuvs_)
{
    setAttrib(attrib_texuv_id, texuvs_);
}

buffer_ptr Mesh::tangents()
{
    return attrib(attrib_tangent_id);
}

void Mesh::setTangents(buffer_ptr tangents_)
{
    setAttrib(attrib_tangent_id, tangents_);
}

bool Mesh::hasAttrib(const attribid_t& attribid_)
{
    return _attribs.find(attribid_) != _attribs.end();
}

buffer_ptr Mesh::attrib(const attribid_t& attribid_)
{
    Attribs::iterator it = _attribs.find(attribid_);
    if(it == _attribs.end()){
        throw(NotFoundException("Attrib not found"));
    }
    return buffer_ptr((*it).second);
}

void Mesh::setAttrib(const attribid_t& attribid_, buffer_ptr attrib_)
{
    _attribs[attribid_] = attrib_;
}

Mesh::iterator Mesh::attribsBegin()
{
    return _attribs.begin();
}

Mesh::iterator Mesh::attribsEnd()
{
    return _attribs.end();
}

ENGINE_NAMESPACE_END
