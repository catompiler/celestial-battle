#ifndef RESOURCES_H
#define	RESOURCES_H

#include "engine/engine.h"
#include <string>
#include "reader.h"
#include <map>
#include <vector>
#include "smart_ptr/smart_ptr.h"
#include "typelist/typelist.h"
#include "glresource/glresource.h"
#include "gltexture/gltexture.h"
#include "glshader/glshader.h"
#include "glprogram/glprogram.h"
#include "glbuffer/glbuffer.h"
#include "mesh/mesh.h"
#include "material/material.h"


ENGINE_NAMESPACE_BEGIN


class Resources {
public:
    
    typedef tl::makeTypeList11<GL::Buffer,
            GL::VertexShader, GL::FragmentShader, GL::Program,
            GL::Texture1D, GL::Texture2D, GL::Texture3D, GL::TextureCube, GL::TextureRect,
            Mesh, Material>::value ResourceTypes;
    
    
    Resources();
    virtual ~Resources();
    
    template<class T>
    smart_ptr<T> get();//create
    
    template<class T>
    smart_ptr<T> get(const std::string& filename_);//read
    
    template<class T>
    bool addReader(T* reader_);
    
    template<class T>
    bool removeReader(T* reader_);
    
private:
    typedef Reader<void*> AllReader;
    typedef std::map<int, std::vector<AllReader*> > Readers;
    
    Readers _readers;

};

ENGINE_NAMESPACE_END

#endif	/* RESOURCES_H */

