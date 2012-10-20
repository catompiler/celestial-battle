#ifndef _RESOURCE_PTR_H
#define _RESOURCE_PTR_H

#include <memory>

template <typename T>
using resource_ptr = std::shared_ptr<T>;


#endif  //_RESOURCE_PTR_H
