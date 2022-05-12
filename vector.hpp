//
// Created by Toad Miranda on 3/29/22.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
namespace ft {
    template<class T, class Alloc = std::allocator<T>>
            class vector {
            public:
                typedef T value_type;
                typedef Alloc allocator_type;
                typedef typename allocator_type::reference reference;
                typedef typename allocator_type::const_reference const_reference;
                typedef typename allocator_type::pointer pointer;
                typedef typename allocator_type::const_pointer const_pointer;


                explicit vector(const allocator_type& alloc = allocator_type());

            };
}

#endif //FT_CONTAINERS_VECTOR_HPP
