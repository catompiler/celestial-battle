#ifndef _UTILS_H_
#define _UTILS_H_

#include <stddef.h>
#include <algorithm>
#include <iterator>
#include <utility>

/*
 * functors
 */
namespace functors{

//! delete single object
struct delete_single{
    template <class T>
    void operator()(T* obj) const{
        delete obj;
    }
    
    template <class T, class U>
    void operator()(std::pair<T, U>& pair_) const{
        delete pair_.second;
    }
};

//! delete array of objects
struct delete_array{
    template <class T>
    void operator()(T* arr) const{
        delete[] arr;
    }
    
    template <class T, class U>
    void operator()(std::pair<T, U>& pair_) const{
        delete[] pair_.second;
    }
};

//! map's/pair's value/second comp(equal)
template <class T>
struct value_equal
{
    T value;
    
    value_equal(T v) :value(v){}
    
    bool operator()(const T& v){
        return value == v;
    }
    
    template <class Pair>
    bool operator()(const Pair& p){
        return value == p.second;
    }
};
template <class T>
value_equal<T> make_value_equal(T v){ return value_equal<T>(v); }

}//functors

namespace functions{

template <class Container>
void delete_all(Container& c)
{
    std::for_each(c.begin(), c.end(), functors::delete_single());
}

template <class Container, class Deleter>
void delete_all(Container& c, const Deleter& d)
{
    std::for_each(c.begin(), c.end(), d);
}

template <class Container>
void delete_all(Container* c)
{
    std::for_each(c->begin(), c->end(), functors::delete_single());
}

template <class Container, class Deleter>
void delete_all(Container* c, const Deleter& d)
{
    std::for_each(c->begin(), c->end(), d);
}

}//functions

namespace iterators{

template <class Map, class Item = typename Map::mapped_type>
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
    
    Item& operator*();
    Item* operator->();
    
private:
    typename Map::iterator _it;
};

}//iterators


template <class T>
struct DirtyValue
{
    DirtyValue() :value(T()), dirty(true){}
    void set(const T& value_, bool dirty_ = true)
        {value = value_; dirty = dirty_;}
    
    T value;
    bool dirty;
};

template <typename DataT>
struct SharedData
{
    SharedData() :data(DataT()), refs_count(1){}
    
    void acquire()
        {refs_count ++;}
    bool release()
        {if(refs_count > 0) refs_count --; return refs_count == 0;}
    
    DataT data;
    
    size_t refs_count;
};


#include "utils/utils_tmpl.h"

#endif	//_UTILS_H_
