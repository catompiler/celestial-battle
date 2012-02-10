#ifndef _RESOURCES_H
#define	_RESOURCES_H

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
    
    template<class _Reader>
    bool addReader(_Reader* reader_);
    
    template<class _Reader>
    bool removeReader(_Reader* reader_);
    
private:
    typedef void AllType;
    typedef Reader<AllType*> AllReader;
    typedef std::vector<AllReader*> ReadersList;
    typedef std::map<int, ReadersList > Readers;
    
    Readers _readers;

    template<class T>
    Readers::iterator _getReadersIt();

    template<class T>
    ReadersList* _getReadersList();
    
};




template<class T>
smart_ptr<T> Resources::get()//create
{
    int type_index = tl::index_of<ResourceTypes, T>::value;
    
    if(type_index == -1) return smart_ptr<T>(NULL);
    
    return smart_ptr<T>(new T());
}

template<class T>
smart_ptr<T> Resources::get(const std::string& filename_)//read
{
    ReadersList* readerslist = _getReadersList<T>();
    if(readerslist == NULL) return smart_ptr<T>(NULL);
    
    T* res = NULL;
    
    for(ReadersList::iterator it = readerslist->begin();
            it != readerslist->end(); ++ it){
        res = reinterpret_cast<Reader<T>*>((*it))->read(filename_);
        if(res != NULL) break;
    }
    
    return res;
}

template<class _Reader>
bool Resources::addReader(_Reader* reader_)
{
    int type_index = tl::index_of<ResourceTypes, typename _Reader::ResourceType>::value;
    
    if(type_index == -1) return false;
    
    Readers::iterator readers_it = _readers.find(type_index);
    
    if(readers_it == _readers.end()){
        readers_it = _readers.insert(std::make_pair(type_index, ReadersList())).first;
    }
    
    AllReader* allreader = reinterpret_cast<AllReader*>(reader_);
    
    ReadersList* readerslist = &(*readers_it).second;
    
    ReadersList::iterator it = std::find(readerslist->begin(),
                                            readerslist->end(), allreader);
    
    if(it != readerslist->end()) return false;
    
    readerslist->insert(readerslist->end(), allreader);
    
    return true;
}

template<class _Reader>
bool Resources::removeReader(_Reader* reader_)
{
    Readers::iterator readers_it = _getReadersIt<typename _Reader::ResourceType>();
    
    if(readers_it == _readers.end()) return false;
    
    AllReader* allreader = reinterpret_cast<AllReader*>(reader_);
    
    ReadersList* readerslist = &(*readers_it).second;
    
    ReadersList::iterator it = std::find(readerslist->begin(),
                                            readerslist->end(), allreader);
    
    if(it == readerslist->end()) return false;
    
    readerslist->erase(it);
    
    if(readerslist->empty()){
        _readers.erase(readers_it);
    }
    
    return true;
}

template<class T>
Resources::Readers::iterator Resources::_getReadersIt()
{
    int type_index = tl::index_of<ResourceTypes, T>::value;
    
    if(type_index == -1) return _readers.end();
    
    return _readers.find(type_index);
}

template<class T>
Resources::ReadersList* Resources::_getReadersList()
{
    Readers::iterator readers_it = _getReadersIt<T>();
    
    if(readers_it == _readers.end()) return NULL;
    
    return &(*readers_it).second;
}




ENGINE_NAMESPACE_END

#endif	/* _RESOURCES_H */

