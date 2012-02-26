#ifndef _RESOURCES_H
#define	_RESOURCES_H

#include <assert.h>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include "engine/engine.h"
#include "resptrs_types.h"
#include "typelist/typelist.h"
#include "reader.h"


ENGINE_NAMESPACE_BEGIN


class Resources {
//private:
    class ResBase;
    typedef std::multimap<std::string, ResBase*> ResourcesList;
    
public:
    
    typedef tl::makeTypeList11<GL::Buffer,
            GL::VertexShader, GL::FragmentShader, GL::Program,
            GL::Texture1D, GL::Texture2D, GL::Texture3D, GL::TextureCube, GL::TextureRect,
            Mesh, Material>::value ResourceTypes;
    
    
    Resources();
    virtual ~Resources();
    
    template<class T>
    bool hasResourceType();
    
    template<class T>
    smart_ptr<T> get();//create
    
    template<class T>
    smart_ptr<T> get(const std::string& filename_);//read
    
    template<class T>
    bool release(smart_ptr<T>& resource_);//release
    
    void gc();
    
    template<class _Reader>
    bool addReader(_Reader* reader_);
    
    template<class _Reader>
    bool removeReader(_Reader* reader_);
    
    
    template <class T>
    class iterator
        :public std::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        iterator();
        iterator(ResourcesList::iterator it_);
        iterator(const iterator<T>& it_);
        ~iterator();
        
        iterator<T>& operator=(const iterator<T>& it_);
        
        iterator<T>& operator++();
        iterator<T> operator++(int);
        iterator<T>& operator--();
        iterator<T> operator--(int);
        
        bool operator==(const iterator<T>& it_) const;
        bool operator!=(const iterator<T>& it_) const;
        
        smart_ptr<T>& operator*();
        smart_ptr<T>& operator->();
        
        const std::string& filename() const;
        smart_ptr<T>& sptr();
        
    private:
        ResourcesList::iterator _it;
    };
    
    
    template<class T>
    iterator<T> begin();
    
    template<class T>
    iterator<T> end();
    
    
private:
    struct AllType{};
    typedef Reader<AllType*> AllReader;
    typedef std::list<AllReader*> ReadersList;
    
    class ResBase{
    public:
        ResBase(){};
        virtual ~ResBase(){};
        virtual AllType* allptr() = 0;
        virtual int refs_count() = 0;
        virtual smart_ptr<AllType>& allsptr() = 0;
    };
    
    template<class T>
    class ResContainer
        :public ResBase
    {
    public:
        ResContainer(smart_ptr<T>& ptr_);
        ~ResContainer();
        
        void set_ptr(smart_ptr<T>& ptr_);
        
        T* ptr();
        smart_ptr<T>& sptr();
        AllType* allptr();
        int refs_count();
        smart_ptr<AllType>& allsptr();
    private:
        smart_ptr<T> _ptr;
    };
    
    //typedef std::multimap<std::string, ResBase*> ResourcesList;
    
    
    class ResBasePtrCmp{
    public:
        template<class T>
        ResBasePtrCmp(T* ptr_){
            _ptr = reinterpret_cast<AllType*>(ptr_);
        }
        template <class Pair>
        bool operator()(Pair& respair_){
            return respair_.second->allptr() == _ptr;
        }
    private:
        AllType* _ptr;
    };
    
    
    
    class ResTypeItem{
    public:
        ResTypeItem();
        ResTypeItem(const ResTypeItem& restypeitem_);
        ~ResTypeItem();
        
        bool hasReaders() const;
        ReadersList* readers();
        ReadersList* getReaders();
        bool hasResources() const;
        ResourcesList* resources();
        ResourcesList* getResources();
        
    private:
        ReadersList* _readers;
        ResourcesList* _resources;
    };
    
    
    typedef std::map<int, ResTypeItem*> ResTypeItems;
    
    ResTypeItems _restypeitems;
    
    template<class T>
    int _getResourceTypeIndex();
    
    template<class T>
    ResTypeItems::iterator _getResTypeIt();
    
    template<class T>
    ResTypeItems::iterator _resTypeIt();
    
    template<class T>
    ReadersList* _readersList();
};




template<class T>
bool Resources::hasResourceType()
{
    return _getResourceTypeIndex<T>() != -1;
}

template<class T>
smart_ptr<T> Resources::get()//create
{
    ResTypeItems::iterator restype_it = _getResTypeIt<T>();
    if(restype_it == _restypeitems.end()) return smart_ptr<T>(NULL);
    
    ResTypeItem* restypeitem = (*restype_it).second;
    ResourcesList* resourceslist = restypeitem->getResources();
    
    smart_ptr<T> res_sptr(new T());
    resourceslist->insert(
            std::make_pair(std::string(), new ResContainer<T>(res_sptr))
            );
    return res_sptr;
}

template<class T>
smart_ptr<T> Resources::get(const std::string& filename_)//read
{
    ResTypeItems::iterator restype_it = _resTypeIt<T>();
    if(restype_it == _restypeitems.end()) return smart_ptr<T>(NULL);
    
    ResTypeItem* restypeitem = (*restype_it).second;
    
    ResourcesList* resourceslist = restypeitem->resources();
    if(resourceslist != NULL){
        ResourcesList::iterator res_it = resourceslist->find(filename_);
        if(res_it != resourceslist->end()){
            ResContainer<T>* rescontainer = static_cast<ResContainer<T>*>(
                                                    (*res_it).second);
            return rescontainer->sptr();
        }
    }
    
    ReadersList* readerslist = restypeitem->readers();
    if(readerslist == NULL) return smart_ptr<T>(NULL);
    
    T* res = NULL;
    
    for(ReadersList::iterator it = readerslist->begin();
            it != readerslist->end(); ++ it){
        res = reinterpret_cast<Reader<T>*>((*it))->read(filename_);
        if(res != NULL){
            if(resourceslist == NULL) resourceslist = restypeitem->getResources();
            smart_ptr<T> res_sptr(res);
            resourceslist->insert(
                    std::make_pair(filename_, new ResContainer<T>(res_sptr))
                    );
            return res_sptr;
        }
    }
    
    return smart_ptr<T>(NULL);
}

template<class T>
bool Resources::release(smart_ptr<T>& resource_)
{
    ResTypeItems::iterator restype_it = _resTypeIt<T>();
    if(restype_it == _restypeitems.end()) return false;
    
    ResTypeItem* restypeitem = (*restype_it).second;
    ResourcesList* resourceslist = restypeitem->resources();
    if(resourceslist == NULL) return false;
    
    ResourcesList::iterator res_it = std::find_if(resourceslist->begin(),
                        resourceslist->end(), ResBasePtrCmp(resource_.get()));
    
    if(res_it == resourceslist->end()) return false;
    
    //if(!resource_.release()) resource_.reset();
    resource_ = NULL;
    
    ResContainer<T>* rescontainer = static_cast<ResContainer<T>*>((*res_it).second);
    
    assert(rescontainer->sptr().refs_count() != 0);
    if(rescontainer->sptr().refs_count() == 1){
        delete rescontainer;
        resourceslist->erase(res_it);
        return true;
    }
    return false;
}

template<class _Reader>
bool Resources::addReader(_Reader* reader_)
{
    ResTypeItems::iterator restypeitem_it = 
            _getResTypeIt<typename _Reader::ResourceType>();
    if(restypeitem_it == _restypeitems.end()) return false;
    
    AllReader* allreader = reinterpret_cast<AllReader*>(reader_);
    ReadersList* readerslist = (*restypeitem_it).second->getReaders();
    
    ReadersList::iterator it = std::find(readerslist->begin(),
                                            readerslist->end(), allreader);
    
    if(it != readerslist->end()) return false;
    
    readerslist->insert(readerslist->end(), allreader);
    
    return true;
}

template<class _Reader>
bool Resources::removeReader(_Reader* reader_)
{
    ResTypeItems::iterator restypeitem_it = 
            _getResTypeIt<typename _Reader::ResourceType>();
    if(restypeitem_it == _restypeitems.end()) return false;
    
    AllReader* allreader = reinterpret_cast<AllReader*>(reader_);
    ReadersList* readerslist = (*restypeitem_it).second->getReaders();
    
    ReadersList::iterator it = std::find(readerslist->begin(),
                                            readerslist->end(), allreader);
    
    if(it == readerslist->end()) return false;
    
    readerslist->erase(it);
    
    return true;
}

template<class T>
Resources::iterator<T> Resources::begin()
{
    ResTypeItems::iterator restype_it = _resTypeIt<T>();
    if(restype_it == _restypeitems.end()) return iterator<T>();
    
    ResTypeItem* restypeitem = (*restype_it).second;
    ResourcesList* resourceslist = restypeitem->resources();
    
    if(resourceslist == NULL) return iterator<T>();
    
    return iterator<T>(resourceslist->begin());
}

template<class T>
Resources::iterator<T> Resources::end()
{
    ResTypeItems::iterator restype_it = _resTypeIt<T>();
    if(restype_it == _restypeitems.end()) return iterator<T>();
    
    ResTypeItem* restypeitem = (*restype_it).second;
    ResourcesList* resourceslist = restypeitem->resources();
    
    if(resourceslist == NULL) return iterator<T>();
    
    return iterator<T>(resourceslist->end());
}

template<class T>
int Resources::_getResourceTypeIndex()
{
    return tl::index_of<ResourceTypes, T>::value;
}

template<class T>
Resources::ResTypeItems::iterator Resources::_getResTypeIt()
{
    int type_index = _getResourceTypeIndex<T>();
    if(type_index == -1) return _restypeitems.end();
    
    ResTypeItems::iterator it = _restypeitems.find(type_index);
    if(it == _restypeitems.end()){
        it = _restypeitems.insert(std::make_pair(type_index, new ResTypeItem())).first;
    }
    return it;
}

template<class T>
Resources::ResTypeItems::iterator Resources::_resTypeIt()
{
    int type_index = _getResourceTypeIndex<T>();
    if(type_index == -1) return _restypeitems.end();
    
    return _restypeitems.find(type_index);
}

template<class T>
Resources::ReadersList* Resources::_readersList()
{
    ResTypeItems::iterator restypeitem_it = _getResTypeIt<T>();
    if(restypeitem_it == _restypeitems.end()) return NULL;

    ReadersList* readerslist = (*restypeitem_it).second->readers();
    
    return readerslist;
}



template<class T>
Resources::ResContainer<T>::ResContainer(smart_ptr<T>& ptr_)
{
    set_ptr(ptr_);
}

template<class T>
Resources::ResContainer<T>::~ResContainer()
{
    _ptr = NULL;
}

template<class T>
void Resources::ResContainer<T>::set_ptr(smart_ptr<T>& ptr_)
{
    _ptr = ptr_;
}

template<class T>
T* Resources::ResContainer<T>::ptr()
{
    return _ptr.get();
}

template<class T>
smart_ptr<T>& Resources::ResContainer<T>::sptr()
{
    return _ptr;
}

template<class T>
Resources::AllType* Resources::ResContainer<T>::allptr()
{
    return reinterpret_cast<AllType*>(_ptr.get());
}

template<class T>
int Resources::ResContainer<T>::refs_count()
{
    return _ptr.refs_count();
}

template<class T>
smart_ptr<Resources::AllType>& Resources::ResContainer<T>::allsptr()
{
    return smart_ptr_cast<AllType>(_ptr);
}




template<class T>
Resources::iterator<T>::iterator()
{
}

template<class T>
Resources::iterator<T>::iterator(ResourcesList::iterator it_)
{
    _it = it_;
}

template<class T>
Resources::iterator<T>::iterator(const iterator<T>& it_)
{
    _it = it_._it;
}

template<class T>
Resources::iterator<T>::~iterator()
{
}

template<class T>
Resources::iterator<T>& Resources::iterator<T>::operator=(const iterator<T>& it_)
{
    _it = it_._it;
}

template<class T>
Resources::iterator<T>& Resources::iterator<T>::operator++()
{
    ++ _it;
    return *this;
}

template<class T>
Resources::iterator<T> Resources::iterator<T>::operator++(int)
{
    return iterator<T>(_it ++);
}

template<class T>
Resources::iterator<T>& Resources::iterator<T>::operator--()
{
    -- _it;
    return *this;
}

template<class T>
Resources::iterator<T> Resources::iterator<T>::operator--(int)
{
    return iterator<T>(_it --);
}

template<class T>
bool Resources::iterator<T>::operator==(const iterator<T>& it_) const
{
    return _it == it_._it;
}

template<class T>
bool Resources::iterator<T>::operator!=(const iterator<T>& it_) const
{
    return _it != it_._it;
}

template<class T>
smart_ptr<T>& Resources::iterator<T>::operator*()
{
    return static_cast<ResContainer<T>*>((*_it).second)->sptr();
}

template<class T>
smart_ptr<T>& Resources::iterator<T>::operator->()
{
    return static_cast<ResContainer<T>*>((*_it).second)->sptr();
}

template<class T>
const std::string& Resources::iterator<T>::filename() const
{
    return (*_it).first;
}

template<class T>
smart_ptr<T>& Resources::iterator<T>::sptr()
{
    return static_cast<ResContainer<T>*>((*_it).second)->sptr();
}


ENGINE_NAMESPACE_END

#endif	/* _RESOURCES_H */

