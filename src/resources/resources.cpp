#include "resources.h"



ENGINE_NAMESPACE_BEGIN



Resources::Resources() {
}

Resources::~Resources() {
}

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
    return smart_ptr<T>(NULL);
}

template<class T>
bool Resources::addReader(T* reader_)
{
    return false;
}

template<class T>
bool Resources::removeReader(T* reader_)
{
    return false;
}



ENGINE_NAMESPACE_END

