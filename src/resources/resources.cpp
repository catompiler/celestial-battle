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
    std::for_each(_resourcetypeitems.begin(), _resourcetypeitems.end(), functors::delete_single());
}

void Resources::gc()
{
    //for each resource type
    for(ResourceTypeItems::iterator rti_it = _resourcetypeitems.begin();
            rti_it != _resourcetypeitems.end(); ++ rti_it){
        (*rti_it).second->gc();
    }
}



Resources::ResourceTypeItemBase::ResourceTypeItemBase()
{
}

Resources::ResourceTypeItemBase::ResourceTypeItemBase(const ResourceTypeItemBase& rtib_)
{
}

Resources::ResourceTypeItemBase::~ResourceTypeItemBase()
{
}


ENGINE_NAMESPACE_END

