#ifndef _UTILS_H_
#define _UTILS_H_

namespace utils{

namespace functors{

struct delete_single{
    template<class T>
    void operator()(T* obj){
        delete obj;
    }
};

struct delete_array{
    template<class T>
    void operator()(T* arr){
        delete[] arr;
    }
};


}//functors

}//utils

#endif	//_UTILS_H_
