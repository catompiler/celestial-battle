#ifndef _MESH_H_
#define _MESH_H_

#include "glbuffer/glbuffer.h"
#include "engine/engine.h"
#include <string>
#include <vector>
#include <utility>
#include <stddef.h>

ENGINE_NAMESPACE_BEGIN


class Mesh
{
public:

    static const std::string attrib_vertex_name;
    static const std::string attrib_normal_name;
    static const std::string attrib_texuv_name;
    static const std::string attrib_tangent_name;

    Mesh();
    ~Mesh();

    GL::Buffer* indices();
    GL::Buffer* vertives();
    GL::Buffer* normals();
    GL::Buffer* texuvs();
    GL::Buffer* tangents();

    bool hasAttrib(const std::string& attrib_name);
    GL::Buffer* attrib(const std::string& attrib_name);

private:

    size_t _indices_count;
    GL::Buffer* _indices;

    size_t _vertices_count;
    /*GL::Buffer* _vertices;
    GL::Buffer* _normals;
    GL::Buffer* _texuvs;
    GL::Buffer* _tangents;*/
    int _vertices_index;
    int _normals_index;
    int _texuvs_index;
    int _tangents_index;

    typedef std::vector<std::pair<std::string, GL::Buffer*> > Attribs;
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
