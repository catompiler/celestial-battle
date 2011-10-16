#ifndef _TYPELIST_H_
#define _TYPELIST_H_

namespace tl{

class NullType{};

template <class Type1, class Type2>
struct TypeList
{
    typedef Type1 Head;
    typedef Type2 Tail;
};


template <class TList>
struct length{
    enum {value = -1};
};

template <>
struct length<NullType>{
    enum {value = 0};
};

template <class Type1, class Type2>
struct length<TypeList<Type1, Type2> >{
    enum {value = 1 + length<Type2>::value};
};


template <class TList, int n_>
struct at{
    typedef NullType value;
};

template<class Type1, class Type2, int n_>
struct at<TypeList<Type1, Type2>, n_>{
    typedef typename at<Type2, n_ - 1>::value value;
};

template<int n_>
struct at<NullType, n_>{
    typedef NullType value;
};

template<class Type1, class Type2>
struct at<TypeList<Type1, Type2>, 0>{
    typedef Type1 value;
};



template <class TList, class T>
struct index_of{
    enum {value = -1};
};

template <class T1, class T2, class T>
struct index_of<TypeList<T1, T2>, T>{
private:
    enum {index_of_value = index_of<T2, T>::value};
public:
    enum {value = index_of_value == -1 ? -1 : 1 + index_of_value};
};

template <class T2, class T>
struct index_of<TypeList<T, T2>, T>{
    enum {value = 0};
};

template <class T>
struct index_of<NullType, T>{
    enum {value = -1};
};

//#define MAKE_TYPELIST1(T) TypeList<T, NullType>
//#define MAKE_TYPELIST2(T1, T2) TypeList<T1, MAKE_TYPELIST1(T2)>
//#define MAKE_TYPELIST3(T1, T2, T3) TypeList<T1, MAKE_TYPELIST2(T2, T3)>

template <class T>
struct makeTypeList1{
    typedef TypeList<T, NullType> value;
};

template <class T1, class T2>
struct makeTypeList2{
    typedef TypeList<T1, typename makeTypeList1<T2>::value> value;
};

template <class T1, class T2, class T3>
struct makeTypeList3{
    typedef TypeList<T1, typename makeTypeList2<T2, T3>::value> value;
};

template <class T1, class T2, class T3, class T4>
struct makeTypeList4{
    typedef TypeList<T1, typename makeTypeList3<T2, T3, T4>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5>
struct makeTypeList5{
    typedef TypeList<T1, typename makeTypeList4<T2, T3, T4, T5>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6>
struct makeTypeList6{
    typedef TypeList<T1, typename makeTypeList5<T2, T3, T4, T5, T6>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7>
struct makeTypeList7{
    typedef TypeList<T1, typename makeTypeList6<T2, T3, T4, T5, T6, T7>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8>
struct makeTypeList8{
    typedef TypeList<T1, typename makeTypeList7<T2, T3, T4, T5,
                                                T6, T7, T8>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9>
struct makeTypeList9{
    typedef TypeList<T1, typename makeTypeList8<T2, T3, T4, T5,
                                                T6, T7, T8, T9>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9, class T10>
struct makeTypeList10{
    typedef TypeList<T1, typename makeTypeList9<T2, T3, T4, T5,
                                                T6, T7, T8, T9,
                                                T10>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9, class T10,
          class T11>
struct makeTypeList11{
    typedef TypeList<T1, typename makeTypeList10<T2, T3, T4, T5,
                                                 T6, T7, T8, T9,
                                                 T10, T11>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9, class T10,
          class T11, class T12>
struct makeTypeList12{
    typedef TypeList<T1, typename makeTypeList11<T2, T3, T4, T5,
                                                 T6, T7, T8, T9,
                                                 T10, T11, T12>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9, class T10,
          class T11, class T12, class T13>
struct makeTypeList13{
    typedef TypeList<T1, typename makeTypeList12<T2, T3, T4, T5,
                                                 T6, T7, T8, T9,
                                                 T10, T11, T12, T13>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9, class T10,
          class T11, class T12, class T13, class T14>
struct makeTypeList14{
    typedef TypeList<T1, typename makeTypeList13<T2, T3, T4, T5,
                                                 T6, T7, T8, T9,
                                                 T10, T11, T12, T13,
                                                 T14>::value> value;
};

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9, class T10,
          class T11, class T12, class T13, class T14, class T15>
struct makeTypeList15{
    typedef TypeList<T1, typename makeTypeList14<T2, T3, T4, T5,
                                                 T6, T7, T8, T9,
                                                 T10, T11, T12, T13,
                                                 T14, T15>::value> value;
};



#ifdef __GXX_EXPERIMENTAL_CXX0X__

template <class ... Types>
struct makeTypeList{
};

template <class T, class ... Types>
struct makeTypeList<T, Types ...>{
    typedef TypeList<T, typename makeTypeList<Types ...>::value > value;
};

template <class T>
struct makeTypeList<T>{
    typedef TypeList<T, NullType> value;
};

#endif

}


#endif  //_TYPELIST_H_
