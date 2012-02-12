#include "resources.h"
#include <utility>
#include <algorithm>
#include <stddef.h>
#include "utils/utils.h"
#include <iostream>

ENGINE_NAMESPACE_BEGIN



Resources::Resources() {
}

Resources::~Resources() {
    //for each resource type
    /*for(ResTypeItems::iterator rti_it = _restypeitems.begin();
            rti_it != _restypeitems.end(); ++ rti_it){
        //get resources list
        ResourcesList* resourceslist = (*rti_it).second->resources();
        //if has resources
        if(resourceslist != NULL){
            //for each resource
            for(ResourcesList::iterator res_it = resourceslist->begin();
                    res_it != resourceslist->end(); ++ res_it){
                //delete
                delete (*res_it).second;
            }
        }
        delete (*rti_it).second;
    }*/
    std::for_each(_restypeitems.begin(), _restypeitems.end(), functors::delete_single());
}




Resources::ResTypeItem::ResTypeItem()
{
    _readers = NULL;
    _resources = NULL;
}

Resources::ResTypeItem::ResTypeItem(const ResTypeItem& restypeitem_)
{
    if(restypeitem_._readers){
        _readers = new ReadersList(*restypeitem_._readers);
    }else{
        _readers = NULL;
    }
    
    if(restypeitem_._resources){
        _resources = new ResourcesList(*restypeitem_._resources);
    }else{
        _resources = NULL;
    }
}

Resources::ResTypeItem::~ResTypeItem()
{
    if(_readers) delete _readers;
    if(_resources){
        std::for_each(_resources->begin(), _resources->end(), functors::delete_single());
        delete _resources;
    }
}

bool Resources::ResTypeItem::hasReaders() const
{
    return _readers != NULL && !_readers->empty();
}

Resources::ReadersList* Resources::ResTypeItem::readers()
{
    return _readers;
}

Resources::ReadersList* Resources::ResTypeItem::getReaders()
{
    if(_readers == NULL){
        _readers = new ReadersList();
    }
    return _readers;
}

bool Resources::ResTypeItem::hasResources() const
{
    return _resources != NULL && !_resources->empty();
}

Resources::ResourcesList* Resources::ResTypeItem::resources()
{
    return _resources;
}

Resources::ResourcesList* Resources::ResTypeItem::getResources()
{
    if(_resources == NULL){
        _resources = new ResourcesList();
    }
    return _resources;
}


ENGINE_NAMESPACE_END

