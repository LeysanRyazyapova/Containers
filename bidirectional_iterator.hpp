//
// Created by Toad Miranda on 7/11/22.
//

#ifndef FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP
#define FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP
#include "iterator_traits.hpp"
namespace ft {
    template <class T>
    class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

    public:
        typedef typename iterator<bidirectional_iterator_tag, T>::value_type val;
        typedef typename iterator<bidirectional_iterator_tag, T>::pointer	pointer;
        typedef typename iterator<bidirectional_iterator_tag, T>::difference_type difference_type;
        typedef typename iterator<bidirectional_iterator_tag, T>::reference reference;

        bidirectional_iterator(): _ptr(nullptr){}
        ~bidirectional_iterator(){}

        bidirectional_iterator(bidirectional_iterator const &it) { *this = it;}

        bidirectional_iterator(pointer ptr){ this->_ptr = ptr;}

        bidirectional_iterator& operator=(bidirectional_iterator const &it) {
            if(this != &it)
                this->_ptr = it._ptr;
            return *this;
        }


        bidirectional_iterator & operator++(){ this->_ptr+=1; return *this;}
        bidirectional_iterator operator++(int) {
            bidirectional_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        bidirectional_iterator &operator--(){ this->_ptr -= 1; return *this;}
        bidirectional_iterator operator--(int) { bidirectional_iterator tmp(*this); (*this)--; return tmp;}



        bidirectional_iterator operator[](difference_type n) { return *(*this + n);}

        reference operator*() const { pointer tmp = _ptr; return *tmp;}
        pointer operator->() const { return this->_ptr;}

        pointer base() const {
            return _ptr;
        }

        operator bidirectional_iterator<const T>() const
        { return (bidirectional_iterator<const T>(_ptr)); }

    private:
        pointer _ptr;
    };

}
#endif //FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP
