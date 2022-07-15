//
// Created by Toad Miranda on 3/29/22.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "random_access_iterator.hpp"
#include "utils.hpp"
#include <cstdio>

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
        typedef typename ft::random_access_iterator<value_type> iterator;
        typedef typename ft::random_access_iterator<const value_type> const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef size_t size_type;

        explicit vector(const allocator_type &alloc = allocator_type()) : _end_ptr(nullptr), _capacity(0), _size(0),
                                                                          _alloc(alloc) {};

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type()) : _capacity(n), _size(n), _alloc(alloc) {

            _end_ptr = _alloc.allocate(n);
            pointer tmp_pointer = _end_ptr;
            for (size_t i = 0; i < n; i++) {
                _alloc.construct(tmp_pointer++, val);
            }
            _end_ptr = tmp_pointer;
        };

        /*Constructs a container with as many elements as the range [first,last),
                 * with each element constructed from its corresponding element in that range, in the same order.*/
        template<class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) :  _capacity(
                0), _size(0), _alloc(alloc) {
            InputIterator it1 = first;
            size_type size = 0;
            while (it1 != last) {
                ++it1;
                ++size;
            }

            _end_ptr = _alloc.allocate(size);
            pointer tmp_pointer = _end_ptr;
            while (first != last) {
                _alloc.construct(tmp_pointer++, *first++);
            }
            _end_ptr = tmp_pointer;
            _size = size;
            _capacity = _size;
        };

        /*Constructs a container with a copy of each of the elements in x, in the same order.*/
        vector(const vector &x) : _capacity(x._capacity), _size(x._size), _alloc(x._alloc) {
            const_iterator it = x.begin();
            _end_ptr = _alloc.allocate(_capacity);
            pointer tmp_pointer = _end_ptr;
            for (size_t i = 0; i < x.size(); i++) {
                _alloc.construct(tmp_pointer++, *it++);
            }
            _end_ptr = tmp_pointer;
//            assign(x.begin(), x.end());
        };

        ~vector() {};

        /*Methods*/
        size_type size() const {
            return _size;
        };

        iterator begin() {
            return iterator(_end_ptr - _size);
        };

        const_iterator begin() const {
            return const_iterator(_end_ptr - _size);
        };

        iterator end() {
            return iterator(_end_ptr);
        };

        const_iterator end() const {
            return const_iterator(_end_ptr);
        };

        reverse_iterator rbegin() {
            return reverse_iterator(_end_ptr - 1);
        }

        reverse_iterator rend() {
            return reverse_iterator(_end_ptr - _size - 1);
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(_end_ptr - 1);
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(_end_ptr - _size - 1);
        };

        size_type max_size() const {
            return _alloc.max_size();
//            return std::numeric_limits<size_type>::max() / sizeof(ft::vector<T, Alloc>);

        };

        void resize(size_type n, value_type val = value_type()) {
            if (n > _size)
                insert(end(), n - _size, val);
            if (n < _size)
                erase(iterator(end().base() - (_size - n)), end());
        };

        iterator insert(iterator position, const value_type &val) {
            if (position < begin() || position > end())
                throw std::out_of_range("Error! Incorrect position\n");
            pointer position_ptr = position.base();
            if (_size + 1 > _capacity) {
                difference_type offset = _end_ptr - position_ptr;
                _reallocate(_capacity * 2);
                position_ptr = _end_ptr - offset;
            }
            ft_memmove(position_ptr + 1, position_ptr,
                       static_cast<size_t>(abs(_end_ptr - position_ptr)) * sizeof(value_type));
            _alloc.construct(position_ptr, val);
            _end_ptr += 1;
            _size += 1;
            return iterator(position_ptr);
        };

        void insert(iterator position, size_type n, const value_type &val) {
            if (position < begin() || position > end())
                throw std::out_of_range("Error! Incorrect position\n");
            pointer curPosPtr = position.base();
            if ((_size + n) > _capacity) {
                difference_type offset = _end_ptr - curPosPtr;
                reserve(_size + n);
                curPosPtr = _end_ptr - offset;
            }
            std::memmove(curPosPtr + n, curPosPtr,
                         static_cast<size_t>(abs(_end_ptr - curPosPtr)) * sizeof(value_type));
            for (size_type i = 0; i < n; ++i) {
                _alloc.construct(&curPosPtr[i], val);
            }
            _end_ptr += n;
            _size += n;
        };

        template<class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
            if (position < begin() || position > end())
                throw std::out_of_range("Error! Incorrect position\n");

            int pos = 0;
            for (iterator it = begin(); it != position; ++it)
                ++pos;

            int n = 0;
            for (InputIterator it = first; it != last; ++it)
                ++n;

            pointer curPosPtr = position.base();
            if ((_size + n) > _capacity) {
                difference_type offset = _end_ptr - curPosPtr;
                if (_capacity == 0)
                    _capacity = 1;
                size_type newCapacity = _capacity;
                while (_size + n > newCapacity)
                    newCapacity = 2 * newCapacity;
                reserve(newCapacity);
                curPosPtr = _end_ptr - offset;
            }
            ft_memmove(curPosPtr + n, curPosPtr,
                       static_cast<size_t>(abs(_end_ptr - curPosPtr)) * sizeof(value_type));
            for (InputIterator it = first; it != last; ++it) {
                _alloc.construct(curPosPtr++, *it);
            }
            _size += n;
            _end_ptr += n;
        };

        template<class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
            _my_clear();
            insert(begin(), first, last);
        };

        void assign(size_type n, const value_type &val) {
            _my_clear();
            insert(begin(), n, val);
        };

        void push_back(const value_type &val) {
            insert(end(), val);
        };

        void pop_back() {
            erase(--end());
        };


        void reserve(size_type n) {
            if (n < _capacity) return;
            pointer new_arr = _alloc.allocate(n);
            iterator it = begin();
            size_type i = 0;
            for (; i < _size; i++) {
                _alloc.construct(new_arr++, *it++);
            }
            _my_clear();
            _end_ptr = new_arr;
            _capacity = n;
            _size = i;
        };

        size_type capacity() const {
            return this->_capacity;
        }

        void printVector() {
            std::cout << "vector size: " << size() << "\n";
            std::cout << "vector capacity: " << capacity() << "\n";
            std::cout << "myvector contains:";
            for (iterator it = begin(); it != end(); it++) {
                std::cout << *it << ' ';
            }
            std::cout << std::endl;
        }

        void clear() {
            pointer tmp_pointer = _end_ptr;
            for (size_t i = 0; i < _size; i++) {
                _alloc.destroy(--tmp_pointer);
            }
            _end_ptr = tmp_pointer;
            _size = 0;
        };

        iterator erase(iterator position) {
            pointer erasePosPtr = position.base();
            _alloc.destroy(erasePosPtr);
            std::memmove(erasePosPtr, erasePosPtr + 1,
                         static_cast<size_t>(abs(_end_ptr - erasePosPtr - 1)) * sizeof(value_type));
            _size -= 1;
            _end_ptr -= 1;
            return (erasePosPtr);
        }

        iterator erase(iterator first, iterator last) {
            for (; first != last;) {
                erase(--last);
            }
            return last;
        }

        reference operator[](size_type n) {
            return *(begin() + n);
        };

        reference at(size_type n) {
            if (n < 0 || n >= _size)
                throw std::out_of_range("index out of range");
            return *(begin() + n);
        };

        const_reference at(size_type n) const {
            if (n < 0 || n >= _size)
                throw std::out_of_range("index out of range");
            return *(begin() + n);
        };

        reference front() {
            return *(_end_ptr - _size);
        };

        const_reference front() const { return *(_end_ptr - _size); }    // if empty() undefined behaviour
        reference back() { return *(_end_ptr - 1); }                    // if empty() undefined behaviour
        const_reference back() const { return *(_end_ptr - 1); }

        bool empty() const { return _size == 0; }


    private:
        pointer _end_ptr;
        size_type _capacity;
        size_type _size;
        allocator_type _alloc;

        void _reallocate(size_type n) {
            if (n == 0)
                n = 1;
            pointer tmp_ptr = _alloc.allocate(n);
            pointer begin = _end_ptr - _size;
            size_type i;
            for (i = 0; i < _size; ++i) {
                _alloc.construct(&tmp_ptr[i], begin[i]);
            }
            _my_clear();
            _capacity = n;
            _size = i;
            _end_ptr = &tmp_ptr[i];
        }

        void _my_clear() {
            clear();
            _alloc.deallocate(_end_ptr, _size);
            _capacity = 0;
            _end_ptr = nullptr;
        }

        void *ft_memmove(void *dst, const void *src, size_t len) {
            size_t i;
            unsigned char *dst2;
            unsigned char *src2;

            if (dst == NULL && src == NULL)
                return (NULL);
            src2 = (unsigned char *) src;
            dst2 = (unsigned char *) dst;
            i = 0;
            if (dst2 > src2) {
                while (len--) {
                    dst2[len] = src2[len];
                }
            } else if (dst2 < src2) {
                while (i < len) {
                    dst2[i] = src2[i];
                    i++;
                }
            }
            return (dst);
        }
    };

    template<class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return false;

        typename vector<T, Alloc>::const_iterator itl = lhs.begin();
        typename vector<T, Alloc>::const_iterator itle = lhs.end();
        typename vector<T, Alloc>::const_iterator itr = rhs.begin();
        typename vector<T, Alloc>::const_iterator itre = rhs.end();

        for (; itl != itle; ++itl) {
            if (itr == itre || *itl != *itr)
                return false;
            ++itr;
        }
        return true;
    }

    template<class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }

    template<class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        typename vector<T, Alloc>::const_iterator itl = lhs.begin();
        typename vector<T, Alloc>::const_iterator itle = lhs.end();
        typename vector<T, Alloc>::const_iterator itr = rhs.begin();
        typename vector<T, Alloc>::const_iterator itre = rhs.end();

        for (; itl != itle; ++itl, ++itr) {
            if (itr == itre)
                return false;
            if (*itl < *itr)
                return true;
        }
        if (itr != itre)
            return true;
        return false;
    }

    template<class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(rhs < lhs); }

    template<class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return rhs < lhs; }

    template<class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs); }

    template<class T, class Alloc>
    void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
        x.swap(y);
    }
}

#endif //VECTOR_HPP
