//
// Created by Toad Miranda on 5/24/22.
//

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP
#include "iterator_traits.hpp"
#include "utils.hpp"
#include <cstddef>
#include <iostream>

namespace ft {

    template<class T>
    class random_access_iterator : public iterator<random_access_iterator_tag, T> {
    public:
        typedef typename iterator<random_access_iterator_tag, T>::value_type val;
        typedef typename iterator<random_access_iterator_tag, T>::pointer	pointer;
        typedef typename iterator<random_access_iterator_tag, T>::difference_type difference_type;
        typedef typename iterator<random_access_iterator_tag, T>::reference reference;

        random_access_iterator(): _ptr(nullptr){}
        ~random_access_iterator(){}

        random_access_iterator(random_access_iterator const &it) { *this = it;}

        random_access_iterator(pointer ptr){ this->_ptr = ptr;}

        random_access_iterator& operator=(random_access_iterator const &it) {
            if(this != &it)
                this->_ptr = it._ptr;
            return *this;
        }


        random_access_iterator & operator++(){ this->_ptr+=1; return *this;}
        random_access_iterator operator++(int) {
            random_access_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        random_access_iterator &operator--(){ this->_ptr -= 1; return *this;}
        random_access_iterator operator--(int) { random_access_iterator tmp(*this); (*this)--; return tmp;}
        random_access_iterator operator+(difference_type const n) const { return random_access_iterator(_ptr + n);}
        random_access_iterator operator-(difference_type const n) const { return random_access_iterator(_ptr - n);}
        random_access_iterator operator-(random_access_iterator const &it) { random_access_iterator tmp = this->_ptr - it._ptr; return *tmp;}
        bool operator==(random_access_iterator const &it) { return this->_ptr == it._ptr;}
        bool operator!=(random_access_iterator const &it) { return !(this->_ptr == it._ptr);}
        bool operator<(random_access_iterator const &it) { return this->_ptr < it._ptr;}
        bool operator>(random_access_iterator const &it) { return this->_ptr > it._ptr;}
        bool operator<=(random_access_iterator const &it) { return this->_ptr <= it._ptr;}
        bool operator>=(random_access_iterator const &it) { return this->_ptr >= it._ptr;}
        random_access_iterator operator+=(difference_type const &n) { this->_ptr = this->_ptr + n; return (*this);};
        random_access_iterator operator-=(difference_type const &n) { this->_ptr = this->_ptr - n; return (*this);};
        random_access_iterator operator[](difference_type n) { return *(*this + n);}

        reference operator*() const { pointer tmp = _ptr; return *tmp;}
        pointer operator->() const { return this->_ptr;}

        pointer base() const {
            return _ptr;
        }

        operator random_access_iterator<const T>() const
        { return (random_access_iterator<const T>(_ptr)); }

    private:
        pointer _ptr;
    };



    template<class Iter>
    class reverse_iterator : public iterator<
            typename ft::iterator_traits<Iter>::iterator_category,
            typename ft::iterator_traits<Iter>::value_type,
            typename ft::iterator_traits<Iter>::difference_type,
            typename ft::iterator_traits<Iter>::pointer,
            typename ft::iterator_traits<Iter>::reference> {



    public:
        typedef  Iter iterator_type;
        typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iter>::pointer pointer;
        typedef typename ft::iterator_traits<Iter>::reference reference;

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
        reverse_iterator operator+(difference_type const n) const { return reverse_iterator(_current - n); };
        reverse_iterator& operator-=(difference_type const n) { this->_current = this->_current + n; return *this; };
        reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); };
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
