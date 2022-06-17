//
// Created by Toad Miranda on 3/29/22.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include "random_access_iterator.hpp"
#include "utils.hpp"
namespace ft {
    template<class T, class Alloc = std::allocator<T> >
            class vector {
            public:
                typedef T value_type;
                typedef Alloc allocator_type;
                typedef typename allocator_type::reference reference;
                typedef typename allocator_type::const_reference const_reference;
                typedef typename allocator_type::pointer pointer;
                typedef typename allocator_type::const_pointer const_pointer;
                typedef typename ft::RandomAccessIterator<value_type> iterator;
                typedef typename ft::RandomAccessIterator<const_pointer> const_iterator;
                typedef typename ft::reverse_iterator<iterator> reverse_iterator;
                typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
                typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
                typedef size_t size_type;
                explicit vector(const allocator_type& alloc = allocator_type()) : _end_ptr(nullptr), _capacity(0), _size(0), _alloc(alloc) {};
                explicit vector (size_type n, const value_type& val = value_type(),
                                 const allocator_type& alloc = allocator_type()) : _capacity(n), _size(n), _alloc(alloc) {
                    _end_ptr = _alloc.allocate(n);
                    pointer tmp_pointer = _end_ptr;
                    for(size_t i = 0; i < n; i++) {
                        _alloc.construct(tmp_pointer++, val);
                    }
                    _end_ptr = tmp_pointer;
                };
                /*Constructs a container with as many elements as the range [first,last),
                         * with each element constructed from its corresponding element in that range, in the same order.*/
                template <class InputIterator>
                vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) :  _capacity(0), _size(0), _alloc(alloc) {
                    InputIterator it1 = first;
                    size_type size = 0;
                    while(it1 != last) {
                        ++it1;
                        ++size;
                    }

                    _end_ptr = _alloc.allocate(size);
                    pointer tmp_pointer = _end_ptr;
                    while(first != last) {
                        _alloc.construct(tmp_pointer++, *first++);
                    }
                    _end_ptr = tmp_pointer;
                    _size = size;
                    _capacity = _size;
                };
                /*Constructs a container with a copy of each of the elements in x, in the same order.*/
                vector (const vector& x) : _capacity(x._capacity), _size(x._size), _alloc(x._alloc) {
                    iterator it = x.begin();
                    _end_ptr = _alloc.allocate(_capacity);
                    pointer tmp_pointer = _end_ptr;
                    for(size_t i = 0; i < x.size(); i++) {
                        _alloc.construct(tmp_pointer++, *it++);
                    }
                    _end_ptr = tmp_pointer;
                };
                ~vector(){};

            /*Methods*/
            size_type size() const {
                return _size;
            };

            iterator begin() const {
                return iterator(_end_ptr - _size);
            };
            iterator end() {
                return iterator(_end_ptr);
            };
            reverse_iterator rbegin() {
                return reverse_iterator(_end_ptr);
            }
            reverse_iterator rend() {
                return reverse_iterator(_end_ptr - _size);
            }
            size_type max_size() const{
                _alloc.max_size();
            };
//            void resize(size_type n, value_type val = value_type()) {
//                if(n > _size)
//                    if(n < _size)
//            };
//            iterator insert (iterator position, const value_type& val){
//
//            };
//
//            void insert (iterator position, size_type n, const value_type& val){
//
//            };
//
//            template <class InputIterator>
//                    void insert (iterator position, InputIterator first, InputIterator last) {
//
//                    };
//
//            template <class InputIterator>
//                    void assign (InputIterator first, InputIterator last) {
//
//                    };

            void assign(size_type n, const value_type& val) {
                clear();
                _alloc.deallocate(_end_ptr);
                _end_ptr = _alloc.allocate(n);
                pointer tmp = _end_ptr;
                for(size_type i = 0; i < n; i++) {
                    _alloc.construct(tmp++, val);
                }
                _end_ptr = tmp;
                _size = n;
                _capacity = n;
            };
            void reserve(size_type n) {
                if(n <= _capacity) return;
                pointer new_arr = _alloc.allocate(n);
                iterator it = begin();
                for(size_type i = 0; i < _size; i++) {
                    _alloc.construct(new_arr++, *it++);
                }
                clear();
                _end_ptr = new_arr;
                _capacity = n;
            };

            size_type capacity() {
                return _capacity;
            }

            void printVector() {
                std::cout<< "vector size: " << size() << "\n";
                std::cout << "vector capacity: " << capacity() << "\n";
                std::cout << "myvector contains:";
                for(iterator it = begin(); it != end(); it++) {
                    std::cout << *it << ' ';
                }
                std::cout << std::endl;
            }

            void clear() {
                pointer tmp_pointer = _end_ptr;
                for(size_t i = 0; i < _size ; ++i) {
                    _alloc.destroy(--tmp_pointer);
                }
                _end_ptr = tmp_pointer;
            };
            private:
                pointer _end_ptr;
                size_type _capacity;
                size_type _size;
                allocator_type _alloc;
            };
}

#endif //VECTOR_HPP
