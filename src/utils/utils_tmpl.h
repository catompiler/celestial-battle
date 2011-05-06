#ifndef _UTILS_TMPL_H_
#define _UTILS_TMPL_H_

#include <cstdlib>

namespace utils{

/*
 * casts
 */
namespace casts{
    
template<> long number_cast(const char* str){
    return strtol(str, NULL, 0);
}

template<> int number_cast(const char* str){
    return number_cast<long>(str);
}

template<> unsigned long number_cast(const char* str){
    return strtoul(str, NULL, 0);
}

template<> unsigned int number_cast(const char* str){
    return number_cast<unsigned long>(str);
}

template<> double number_cast(const char* str){
    return strtod(str, NULL);
}

template<> float number_cast(const char* str){
    return number_cast<double>(str);
}

}//casts 

}

#endif