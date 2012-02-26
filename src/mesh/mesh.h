#ifndef _MESH_H_
#define _MESH_H_

#include "engine/engine.h"
#include <string>
#include <vector>
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

    static const std::string attrib_index_name;
    static const std::string attrib_vertex_name;
    static const std::string attrib_normal_name;
    static const std::string attrib_texuv_name;
    static const std::string attrib_tangent_name;

    Mesh();
    ~Mesh();

    buffer_ptr indices();
    buffer_ptr vertives();
    buffer_ptr normals();
    buffer_ptr texuvs();
    buffer_ptr tangents();

    bool hasAttrib(const std::string& attrib_name);
    buffer_ptr attrib(const std::string& attrib_name);

private:

    int _indices_index;
    int _vertices_index;
    int _normals_index;
    int _texuvs_index;
    int _tangents_index;

    typedef std::vector<std::pair<std::string, buffer_ptr> > Attribs;
    Attribs _attribs;
    typedef Attribs::iterator AttribsIt;

    struct PairFirstCmp{
        template<class Pair>
        bool operator()(const Pair& left_, const Pair& right_){
            return left_.first < right_.first;
        }
        template<class Pair>
        bool operator()(const std::string& left_, const Pair& right_){
            return left_ < right_.first;
        }
        template<class Pair>
        bool operator()(const Pair& left_, const std::string& right_){
            return left_.first < right_;
        }
    };
    
    void _resortAttribs();
    
    int _getAttribIndexSorted(const std::string& attrib_name_);

};


ENGINE_NAMESPACE_END

#endif  //_MESH_H_
