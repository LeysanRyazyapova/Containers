//
// Created by Toad Miranda on 5/24/22.
//

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP
#include "iterator_traits.hpp"
#include <cstddef>
#include <iostream>
namespace ft {
    template<class Category, class T, class Dist = ptrdiff_t, class Pt = T*, class Rt = T&>
    struct iterator : public Category{
        typedef Category iterator_category;
        typedef T value_type;
        typedef Dist difference_type;
        typedef Pt pointer;
        typedef Rt reference;
    };

    struct input_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{};
    struct bidirectional_iterator_tag : public forward_iterator_tag{};
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};

    template<class T>
    class RandomAccessIterator : public iterator<random_access_iterator_tag, T> {
    public:
        typedef typename iterator<random_access_iterator_tag, T>::pointer	pointer;
        typedef typename iterator<random_access_iterator_tag, T>::difference_type difference_type;
        typedef typename iterator<random_access_iterator_tag, T>::reference reference;

        RandomAccessIterator(): _ptr(nullptr){}
        ~RandomAccessIterator(){}

        RandomAccessIterator(RandomAccessIterator const &it) { *this = it;}
        RandomAccessIterator(pointer ptr){ this->_ptr = ptr;}

        RandomAccessIterator& operator=(RandomAccessIterator const &it) {
            if(this != &it)
                this->_ptr = it._ptr;
            return *this;
        }


        RandomAccessIterator & operator++(){ this->_ptr+=1; return *this;}
        RandomAccessIterator operator++(int) {
            RandomAccessIterator tmp(*this);
            ++(*this);
            return tmp;
        }
        RandomAccessIterator &operator--(){ this->_ptr -= 1; return *this;}
        RandomAccessIterator operator--(int) { RandomAccessIterator tmp(*this); (*this)--; return tmp;}
        RandomAccessIterator operator+(difference_type const n) { RandomAccessIterator it = this->_ptr + n; return *it;}
        RandomAccessIterator operator-(difference_type const n) { RandomAccessIterator it = this->_ptr - n; return *it;}
        RandomAccessIterator operator-(RandomAccessIterator const &it) { RandomAccessIterator tmp = this->_ptr - it._ptr; return *tmp;}
        bool operator==(RandomAccessIterator const &it) { return this->_ptr== it._ptr;}
        bool operator!=(RandomAccessIterator const &it) { return !(this->_ptr == it._ptr);}
        bool operator<(RandomAccessIterator const &it) { return this->_ptr < it._ptr;}
        bool operator>(RandomAccessIterator const &it) { return this->_ptr > it._ptr;}
        bool operator<=(RandomAccessIterator const &it) { return this->_ptr <= it._ptr;}
        bool operator>=(RandomAccessIterator const &it) { return this->_ptr >= it._ptr;}
        RandomAccessIterator operator+=(difference_type n) { this->_ptr = this->_ptr + n; return *this;}
        RandomAccessIterator operator-=(difference_type n) { this->_ptr = this->_ptr - n; return *this;}
        RandomAccessIterator operator[](difference_type n) { return *(*this + n);}

        reference operator*() const { return *this->_ptr;}
        pointer operator->() const { return this->_ptr;}

    private:
        pointer _ptr;
    };

    template<class Iter>
    class reverse_iterator : public iterator<
            typename Iter::iterator_category,
            typename Iter::value_type,
            typename Iter::difference_type,
            typename Iter::pointer,
            typename Iter::reference> {

        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;

    public:
        typedef  Iter iterator_type;
        reverse_iterator() : _current(nullptr) {};
        ~reverse_iterator(){};
        explicit reverse_iterator(Iter x) {
            this->_current = x;
        };
        template<class U>
                reverse_iterator(const reverse_iterator<U>& x){ *this = x; };
        Iter base() const {return this->_current - 1;};
        reference operator*() const { return *this->_current; };
        pointer operator->() const { return this->_current; };
        reverse_iterator& operator++() { this->_current -= 1; return *this; };
        reverse_iterator operator++(int) { Iter tmp(*this); (*this)++; return tmp; };
        reverse_iterator& operator--() { this->_current += 1; return *this; };
        reverse_iterator operator--(int) { Iter tmp(*this); (*this)--; return tmp; };
        reverse_iterator& operator+=(difference_type n) { this->_current = this->_current - n; return *this; };
        reverse_iterator operator+(difference_type n) const { Iter tmp = this->_current - n; return tmp; };
        reverse_iterator& operator-=(difference_type n) { this->_current = this->_current + n; return *this; };
        reverse_iterator operator-(difference_type n) const { Iter tmp = this->_current + n; return tmp; };
        reference operator[](difference_type n) const { return *(*this - n); };
        bool operator==(reverse_iterator const &it) { return this->_current== it._current;}
        bool operator!=(reverse_iterator const &it) { return !(this->_current == it._current);}
        bool operator<(reverse_iterator const &it) { return this->_current > it._current;}
        bool operator>(reverse_iterator const &it) { return this->_current < it._current;}
        bool operator<=(reverse_iterator const &it) { return this->_current >= it._current;}
        bool operator>=(reverse_iterator const &it) { return this->_current <= it._current;}
    protected:
        Iter _current;
    };

}
#endif //ITERATOR_HPP
