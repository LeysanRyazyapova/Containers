//
// Created by Toad Miranda on 5/27/22.
//

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP
//#include "random_access_iterator.hpp"
#include "iostream"
namespace ft{
    struct random_access_iterator_tag;
    template<class It>
    struct iterator_traits {
        typedef typename It::iterator_category iterator_category;
        typedef typename It::value_type value_type;
        typedef typename It::difference_type difference_type;
        typedef typename It::pointer pointer;
        typedef typename It::reference reference;
    };
    template<class T>
    struct iterator_traits<T *> {
        typedef typename ft::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T& reference;
    };
    template<class T>
    struct iterator_traits<const T *> {
        typedef typename ft::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T& reference;
    };
}
#endif //ITERATOR_TRAITS_H
