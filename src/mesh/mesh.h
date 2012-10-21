#ifndef _MESH_H_
#define _MESH_H_

#include "engine/engine.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <stddef.h>


ENGINE_NAMESPACE_BEGIN
class Mesh;
ENGINE_NAMESPACE_END
#include "resources/resptrs_types.h"



ENGINE_NAMESPACE_BEGIN


class Mesh
{
public:
    
    typedef std::string attribid_t;

    static const attribid_t attrib_index_id;
    static const attribid_t attrib_vertex_id;
    static const attribid_t attrib_normal_id;
    static const attribid_t attrib_texuv_id;
    static const attribid_t attrib_tangent_id;

    Mesh();
    ~Mesh();

    buffer_ptr indices();
    void setIndices(buffer_ptr indices_);
    
    buffer_ptr vertives();
    void setVertices(buffer_ptr vertices_);
    
    buffer_ptr normals();
    void setNormals(buffer_ptr normals_);
    
    buffer_ptr texuvs();
    void setTexuvs(buffer_ptr texuvs_);
    
    buffer_ptr tangents();
    void setTangents(buffer_ptr tangents_);

    bool hasAttrib(const attribid_t& attribid_);
    buffer_ptr attrib(const attribid_t& attribid_);
    void setAttrib(const attribid_t& attribid_, buffer_ptr attrib_);

private:

    typedef std::unordered_map<attribid_t, buffer_ptr> Attribs;
    Attribs _attribs;
    typedef Attribs::iterator AttribsIt;
};


ENGINE_NAMESPACE_END

#endif  //_MESH_H_
