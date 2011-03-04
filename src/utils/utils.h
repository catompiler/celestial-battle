#ifndef _UTILS_H_
#define _UTILS_H_

namespace utils{

namespace functors{

class delete_object{
public:
    template<class T>
    void operator()(T* obj){
        delete obj;
    }
};

class delete_array{
public:
    template<class T>
    void operator()(T* arr){
        delete[] arr;
    }
};


}//functors

}//utils

#endif	//_UTILS_H_
