#ifndef _UTILS_H_
#define _UTILS_H_

#include <iterator>
#include <utility>

/*
 * functors
 */
namespace functors{

//! delete single object
struct delete_single{
    template<class T>
    void operator()(T* obj){
        delete obj;
    }
    
    template<class T, class U>
    void operator()(std::pair<T, U>& pair_){
        delete pair_.second;
    }
};

//! delete array of objects
struct delete_array{
    template<class T>
    void operator()(T* arr){
        delete[] arr;
    }
    
    template<class T, class U>
    void operator()(std::pair<T, U>& pair_){
        delete[] pair_.second;
    }
};


}//functors

namespace iterators{

template<class Map, class Item = typename Map::mapped_type>
class MapValueIterator
    :public std::iterator<std::bidirectional_iterator_tag, typename Map::mapped_type>
{
public:
    MapValueIterator();
    MapValueIterator(typename Map::iterator it_);
    MapValueIterator(const MapValueIterator<Map, Item>& iter_);
    ~MapValueIterator();
    
    MapValueIterator<Map, Item>& operator=(const MapValueIterator<Map, Item>& iter_);
    
    MapValueIterator<Map, Item>& operator++();
    MapValueIterator<Map, Item> operator++(int);
    MapValueIterator<Map, Item>& operator--();
    MapValueIterator<Map, Item> operator--(int);
    
    bool operator==(const MapValueIterator<Map, Item>& iter_) const;
    bool operator!=(const MapValueIterator<Map, Item>& iter_) const;
    
    /*typename MapValueIterator<Map>::value_type&*/Item& operator*();
    
private:
    typename Map::iterator _it;
};

}//iterators


template<class T>
struct DirtyValue
{
    DirtyValue() :value(T()), dirty(true){}
    T value;
    bool dirty;
};


#include "utils/utils_tmpl.h"

#endif	//_UTILS_H_
