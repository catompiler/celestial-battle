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
public:
    
    typedef tl::makeTypeList<GL::Buffer,
            GL::VertexShader, GL::FragmentShader, GL::GeometryShader,
            GL::TessControlShader, GL::TessEvalShader, GL::ComputeShader, GL::Program,
            GL::Texture1D, GL::Texture2D, GL::Texture3D, GL::TextureCube, GL::TextureRect,
            Mesh, Material>::value ResourceTypes;
    
    template <typename T>
    class ResourceContainer{
    public:
        ResourceContainer();
        ResourceContainer(const resource_ptr<T>& sptr_);
        ~ResourceContainer();
        
        resource_ptr<T>& get();
        void set(const resource_ptr<T>& sptr_);
    private:
        resource_ptr<T> _sptr;
    };
    
    template <typename T>
    using ResourcesList = std::unordered_multimap<std::string, ResourceContainer<T>*>;
    
    template <typename T>
    using ReadersList = std::list<Reader<T>*>;
    
    
    Resources();
    virtual ~Resources();
    
    template<class T>
    bool hasResourceType();
    
    template<class T>
    resource_ptr<T> get();//create
    
    template<class T>
    resource_ptr<T> get(const std::string& filename_);//read
    
    template<class T>
    bool release(resource_ptr<T>& resource_);//release
    
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
        iterator(typename ResourcesList<T>::iterator it_);
        iterator(const iterator<T>& it_);
        ~iterator();
        
        iterator<T>& operator=(const iterator<T>& it_);
        
        iterator<T>& operator++();
        iterator<T> operator++(int);
        iterator<T>& operator--();
        iterator<T> operator--(int);
        
        bool operator==(const iterator<T>& it_) const;
        bool operator!=(const iterator<T>& it_) const;
        
        resource_ptr<T>& operator*();
        resource_ptr<T>& operator->();
        
        const std::string& filename() const;
        resource_ptr<T>& sptr();
        
    private:
        typename ResourcesList<T>::iterator _it;
    };
    
    
    template<class T>
    iterator<T> begin();
    
    template<class T>
    iterator<T> end();
    
    
private:
    
    class ResourceTypeItemBase{
    public:
        ResourceTypeItemBase();
        ResourceTypeItemBase(const ResourceTypeItemBase& rtib_);
        virtual ~ResourceTypeItemBase();
        virtual bool hasReaders() const = 0;
        virtual bool hasResources() const = 0;
        virtual void gc() = 0;
    };
    
    template <typename T>
    class ResourceTypeItem
        :public ResourceTypeItemBase
    {
    public:
        ResourceTypeItem();
        ResourceTypeItem(const ResourceTypeItem& restypeitem_);
        ~ResourceTypeItem();
        
        bool hasReaders() const;
        ReadersList<T>* readers();
        ReadersList<T>* getReaders();
        bool hasResources() const;
        ResourcesList<T>* resources();
        ResourcesList<T>* getResources();
        void gc();
        
    private:
        ReadersList<T>* _readers;
        ResourcesList<T>* _resources;
    };
    
    
    typedef std::unordered_map<int, ResourceTypeItemBase*> ResourceTypeItems;
    
    ResourceTypeItems _resourcetypeitems;
    
    template<class T>
    int _getResourceTypeIndex();
    
    template<class T>
    ResourceTypeItems::iterator _getResourceTypeIt();
    
    template<class T>
    ResourceTypeItems::iterator _resourceTypeIt();
    
    template<class T>
    ReadersList<T>* _readersList();
};




template<class T>
bool Resources::hasResourceType()
{
    return _getResourceTypeIndex<T>() != -1;
}

template<class T>
resource_ptr<T> Resources::get()//create
{
    ResourceTypeItems::iterator restype_it = _getResourceTypeIt<T>();
    if(restype_it == _resourcetypeitems.end()) return resource_ptr<T>(NULL);
    
    ResourceTypeItem<T>* restypeitem = static_cast<ResourceTypeItem<T>*>((*restype_it).second);
    ResourcesList<T>* resourceslist = restypeitem->getResources();
    
    resource_ptr<T> res_sptr(new T());
    resourceslist->insert(
            std::make_pair(std::string(), new ResourceContainer<T>(res_sptr))
            );
    return res_sptr;
}

template<class T>
resource_ptr<T> Resources::get(const std::string& filename_)//read
{
    ResourceTypeItems::iterator restype_it = _resourceTypeIt<T>();
    if(restype_it == _resourcetypeitems.end()) return resource_ptr<T>(NULL);
    
    ResourceTypeItem<T>* restypeitem = static_cast<ResourceTypeItem<T>*>((*restype_it).second);
    
    ResourcesList<T>* resourceslist = restypeitem->resources();
    if(resourceslist != NULL){
        typename ResourcesList<T>::iterator res_it = resourceslist->find(filename_);
        if(res_it != resourceslist->end()){
            ResourceContainer<T>* rescontainer = static_cast<ResourceContainer<T>*>((*res_it).second);
            return rescontainer->get();
        }
    }
    
    ReadersList<T>* readerslist = restypeitem->readers();
    if(readerslist == NULL) return resource_ptr<T>(NULL);
    
    T* res = NULL;
    
    for(typename ReadersList<T>::iterator it = readerslist->begin();
            it != readerslist->end(); ++ it){
        res = static_cast<Reader<T>*>((*it))->read(this, filename_);
        if(res != NULL){
            if(resourceslist == NULL) resourceslist = restypeitem->getResources();
            resource_ptr<T> res_sptr(res);
            resourceslist->insert(
                    std::make_pair(filename_, new ResourceContainer<T>(res_sptr))
                    );
            return res_sptr;
        }
    }
    
    return resource_ptr<T>(NULL);
}

template<class T>
bool Resources::release(resource_ptr<T>& resource_)
{
    ResourceTypeItems::iterator restype_it = _resourceTypeIt<T>();
    if(restype_it == _resourcetypeitems.end()) return false;
    
    ResourceTypeItem<T>* restypeitem = static_cast<ResourceTypeItem<T>*>((*restype_it).second);
    ResourcesList<T>* resourceslist = restypeitem->resources();
    if(resourceslist == NULL) return false;
    
    typename ResourcesList<T>::iterator res_it =
    std::find_if(resourceslist->begin(), resourceslist->end(), [&resource_](typename ResourcesList<T>::value_type& item_){
        return item_.second->get() == resource_;
    });
    
    if(res_it == resourceslist->end()) return false;
    
    //if(!resource_.release()) resource_.reset();
    resource_ = NULL;
    
    ResourceContainer<T>* rescontainer = (*res_it).second;
    
    assert(rescontainer->get().use_count() != 0);
    
    if(rescontainer->get().use_count() == 1){
        delete rescontainer;
        resourceslist->erase(res_it);
        return true;
    }
    return false;
}

template<class _Reader>
bool Resources::addReader(_Reader* reader_)
{
    ResourceTypeItems::iterator restypeitem_it = 
            _getResourceTypeIt<typename _Reader::ResourceType>();
    if(restypeitem_it == _resourcetypeitems.end()) return false;
    
    ResourceTypeItem<typename _Reader::ResourceType>* resourcetypeitem = 
                static_cast<ResourceTypeItem<typename _Reader::ResourceType>*>((*restypeitem_it).second);
    
    ReadersList<typename _Reader::ResourceType>* readerslist = resourcetypeitem->getReaders();
    
    typename ReadersList<typename _Reader::ResourceType>::iterator it = std::find(readerslist->begin(),
                                            readerslist->end(), reader_);
    
    if(it != readerslist->end()) return false;
    
    readerslist->insert(readerslist->end(), reader_);
    
    return true;
}

template<class _Reader>
bool Resources::removeReader(_Reader* reader_)
{
    ResourceTypeItems::iterator restypeitem_it = 
            _getResourceTypeIt<typename _Reader::ResourceType>();
    if(restypeitem_it == _resourcetypeitems.end()) return false;
    
    ResourceTypeItem<typename _Reader::ResourceType>* resourcetypeitem = 
                static_cast<ResourceTypeItem<typename _Reader::ResourceType>*>((*restypeitem_it).second);
    
    ReadersList<typename _Reader::ResourceType>* readerslist = resourcetypeitem->readers();
    
    if(readerslist == NULL) return false;
    
    typename ReadersList<typename _Reader::ResourceType>::iterator it = std::find(readerslist->begin(),
                                            readerslist->end(), reader_);
    
    if(it == readerslist->end()) return false;
    
    readerslist->erase(it);
    
    return true;
}

template<class T>
Resources::iterator<T> Resources::begin()
{
    ResourceTypeItems::iterator restype_it = _resourceTypeIt<T>();
    if(restype_it == _resourcetypeitems.end()) return iterator<T>();
    
    ResourceTypeItem<T>* restypeitem = static_cast<ResourceTypeItem<T>*>((*restype_it).second);
    ResourcesList<T>* resourceslist = restypeitem->resources();
    
    if(resourceslist == NULL) return iterator<T>();
    
    return iterator<T>(resourceslist->begin());
}

template<class T>
Resources::iterator<T> Resources::end()
{
    ResourceTypeItems::iterator restype_it = _resourceTypeIt<T>();
    if(restype_it == _resourcetypeitems.end()) return iterator<T>();
    
    ResourceTypeItem<T>* restypeitem = static_cast<ResourceTypeItem<T>*>((*restype_it).second);
    ResourcesList<T>* resourceslist = restypeitem->resources();
    
    if(resourceslist == NULL) return iterator<T>();
    
    return iterator<T>(resourceslist->end());
}



template <typename T>
Resources::ResourceTypeItem<T>::ResourceTypeItem()
    :ResourceTypeItemBase()
{
    _readers = NULL;
    _resources = NULL;
}

template <typename T>
Resources::ResourceTypeItem<T>::ResourceTypeItem(const ResourceTypeItem& restypeitem_)
    :ResourceTypeItemBase(restypeitem_)
{
    if(restypeitem_._readers){
        _readers = new ReadersList<T>(*restypeitem_._readers);
    }else{
        _readers = NULL;
    }
    
    if(restypeitem_._resources){
        _resources = new ResourcesList<T>(*restypeitem_._resources);
    }else{
        _resources = NULL;
    }
}

template <typename T>
Resources::ResourceTypeItem<T>::~ResourceTypeItem()
{
    if(_readers) delete _readers;
    if(_resources){
        std::for_each(_resources->begin(), _resources->end(), functors::delete_single());
        delete _resources;
    }
}

template <typename T>
bool Resources::ResourceTypeItem<T>::hasReaders() const
{
    return _readers != NULL && !_readers->empty();
}

template <typename T>
Resources::ReadersList<T>* Resources::ResourceTypeItem<T>::readers()
{
    return _readers;
}

template <typename T>
Resources::ReadersList<T>* Resources::ResourceTypeItem<T>::getReaders()
{
    if(_readers == NULL){
        _readers = new ReadersList<T>();
    }
    return _readers;
}

template <typename T>
bool Resources::ResourceTypeItem<T>::hasResources() const
{
    return _resources != NULL && !_resources->empty();
}

template <typename T>
Resources::ResourcesList<T>* Resources::ResourceTypeItem<T>::resources()
{
    return _resources;
}

template <typename T>
Resources::ResourcesList<T>* Resources::ResourceTypeItem<T>::getResources()
{
    if(_resources == NULL){
        _resources = new ResourcesList<T>();
    }
    return _resources;
}

template <typename T>
void Resources::ResourceTypeItem<T>::gc()
{
    //if has resources
    if(_resources != NULL){
        //for each resource
        for(typename ResourcesList<T>::iterator res_it = _resources->begin();
                res_it != _resources->end();){
            ResourceContainer<T>* resource_container = (*res_it).second;
            //if no one use the resource
            assert(resource_container->get().use_count() != 0);
            if(resource_container->get().use_count() == 1){
                //delete
                delete resource_container;
                //erase
                typename ResourcesList<T>::iterator erase_it = res_it ++;
                _resources->erase(erase_it);
            }else{
                ++ res_it;
            }
        }
    }
}



template<class T>
int Resources::_getResourceTypeIndex()
{
    return tl::index_of<ResourceTypes, T>::value;
}

template<class T>
Resources::ResourceTypeItems::iterator Resources::_getResourceTypeIt()
{
    int type_index = _getResourceTypeIndex<T>();
    if(type_index == -1) return _resourcetypeitems.end();
    
    ResourceTypeItems::iterator it = _resourcetypeitems.find(type_index);
    if(it == _resourcetypeitems.end()){
        it = _resourcetypeitems.insert(std::make_pair(type_index, new ResourceTypeItem<T>())).first;
    }
    return it;
}

template<class T>
Resources::ResourceTypeItems::iterator Resources::_resourceTypeIt()
{
    int type_index = _getResourceTypeIndex<T>();
    if(type_index == -1) return _resourcetypeitems.end();
    
    return _resourcetypeitems.find(type_index);
}

template<class T>
Resources::ReadersList<T>* Resources::_readersList()
{
    ResourceTypeItems::iterator restypeitem_it = _getResourceTypeIt<T>();
    if(restypeitem_it == _resourcetypeitems.end()) return NULL;

    ResourceTypeItem<T>* resourceTypeItem = static_cast<ResourceTypeItem<T>*>((*restypeitem_it).second);
    
    if(resourceTypeItem == NULL) return NULL;
    
    ReadersList<T>* readerslist = resourceTypeItem->readers();
    
    return readerslist;
}


template <typename T>
Resources::ResourceContainer<T>::ResourceContainer()
{
}

template <typename T>
Resources::ResourceContainer<T>::ResourceContainer(const resource_ptr<T>& sptr_)
{
    _sptr = sptr_;
}

template <typename T>
Resources::ResourceContainer<T>::~ResourceContainer()
{
}

template <typename T>
resource_ptr<T>& Resources::ResourceContainer<T>::get()
{
    return _sptr;
}

template <typename T>
void Resources::ResourceContainer<T>::set(const resource_ptr<T>& sptr_)
{
    _sptr = sptr_;
}



template<class T>
Resources::iterator<T>::iterator()
{
}

template<class T>
Resources::iterator<T>::iterator(typename ResourcesList<T>::iterator it_)
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
resource_ptr<T>& Resources::iterator<T>::operator*()
{
    return sptr();
}

template<class T>
resource_ptr<T>& Resources::iterator<T>::operator->()
{
    return sptr();
}

template<class T>
const std::string& Resources::iterator<T>::filename() const
{
    return (*_it).first;
}

template<class T>
resource_ptr<T>& Resources::iterator<T>::sptr()
{
    return (*_it).second->get();
}


ENGINE_NAMESPACE_END

#endif	/* _RESOURCES_H */

