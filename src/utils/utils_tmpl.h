#ifndef _UTILS_TMPL_H_
#define _UTILS_TMPL_H_


namespace iterators{

template<class Map, class Item>
MapValueIterator<Map, Item>::MapValueIterator()
{
}

template<class Map, class Item>
MapValueIterator<Map, Item>::MapValueIterator(typename Map::iterator it_)
{
    _it = it_;
}

template<class Map, class Item>
MapValueIterator<Map, Item>::MapValueIterator(const MapValueIterator<Map, Item>& iter_)
{
    operator=(iter_);
}

template<class Map, class Item>
MapValueIterator<Map, Item>::~MapValueIterator()
{
}

template<class Map, class Item>
MapValueIterator<Map, Item>& MapValueIterator<Map, Item>::operator=(const MapValueIterator<Map, Item>& iter_)
{
    _it = iter_._it;
    return *this;
}

template<class Map, class Item>
MapValueIterator<Map, Item>& MapValueIterator<Map, Item>::operator++()
{
    _it ++;
    return *this;
}

template<class Map, class Item>
MapValueIterator<Map, Item> MapValueIterator<Map, Item>::operator++(int)
{
    MapValueIterator<Map> res(*this);
    operator++();
    return res;
}

template<class Map, class Item>
MapValueIterator<Map, Item>& MapValueIterator<Map, Item>::operator--()
{
    _it --;
    return *this;
}

template<class Map, class Item>
MapValueIterator<Map, Item> MapValueIterator<Map, Item>::operator--(int)
{
    MapValueIterator<Map> res(*this);
    operator--();
    return res;
}

template<class Map, class Item>
bool MapValueIterator<Map, Item>::operator==(const MapValueIterator<Map, Item>& iter_) const
{
    return _it == iter_._it;
}

template<class Map, class Item>
bool MapValueIterator<Map, Item>::operator!=(const MapValueIterator<Map, Item>& iter_) const
{
    return !operator==(iter_);
}

template<class Map, class Item>
/*typename MapValueIterator<Map, Item>::value_type&*/
Item& MapValueIterator<Map, Item>::operator*()
{
    return (*_it).second;
}

template<class Map, class Item>
Item* MapValueIterator<Map, Item>::operator->()
{
    return &(*_it).second;
}

}//iterators

#endif
