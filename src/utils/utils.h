#ifndef _UTILS_H_
#define _UTILS_H_

namespace utils{


/*
 * casts
 */
namespace casts{

//! cast string in number
template<class T> T number_cast(const char*);

}//casts


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
};

//! delete array of objects
struct delete_array{
    template<class T>
    void operator()(T* arr){
        delete[] arr;
    }
};


}//functors

}//utils

#include "utils/utils_tmpl.h"

#endif	//_UTILS_H_
