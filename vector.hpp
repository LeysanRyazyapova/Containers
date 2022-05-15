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
                typedef typename RandomAccessIterator iterator;
                //typedef typename RandomAccessIterator const_iterator;
                //typedef typename ReverseIterator<iterator> reverse_iterator;
//                typedef typename ReverseIterator<const_iterator> const_reverse_iterator;
//                typedef typename iterator_traits<iterator>::difference_type difference_type;
                typedef typename size_t size_type;
//                explicit vector(const allocator_type& alloc = allocator_type()) : _array(nullptr), _capacity(0), _size(0), _alloc(alloc) {};
//                explicit vector (size_type n, const value_type& val = value_type(),
//                                 const allocator_type& alloc = allocator_type()) : _capacity(n), _size(n), _alloc(alloc) {
//                    _array = _alloc.allocate(n);
//                    for(size_t i = 0; i < n; i++) {
//                        _array = _alloc.construct();
//                    }
                };
            private:
                value_type* _array;
                size_type _capacity;
                size_type _size;
                allocator_type _alloc;
            };
}

#endif //FT_CONTAINERS_VECTOR_HPP
