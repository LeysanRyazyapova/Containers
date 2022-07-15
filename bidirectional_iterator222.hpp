//
// Created by Toad Miranda on 7/11/22.
//

#ifndef FT_CONTAINERS_BIDIRECTIONAL_ITERATOR222_HPP
#define FT_CONTAINERS_BIDIRECTIONAL_ITERATOR222_HPP
#include "iterator_traits.hpp"
namespace ft {
    template <class T>
    class bidirectional_iterator222 : public ft::iterator<ft::bidirectional_iterator_tag, T> {

    public:
        typedef typename iterator<bidirectional_iterator_tag, T>::value_type val;
        typedef typename iterator<bidirectional_iterator_tag, T>::pointer	pointer;
        typedef typename iterator<bidirectional_iterator_tag, T>::difference_type difference_type;
        typedef typename iterator<bidirectional_iterator_tag, T>::reference reference;

        bidirectional_iterator222(): _ptr(nullptr){}
        ~bidirectional_iterator222(){}

        bidirectional_iterator222(bidirectional_iterator222 const &it) { *this = it;}

        bidirectional_iterator222(pointer ptr){ this->_ptr = ptr;}

        bidirectional_iterator222& operator=(bidirectional_iterator222 const &it) {
            if(this != &it)
                this->_ptr = it._ptr;
            return *this;
        }


        bidirectional_iterator222 & operator++(){ this->_ptr+=1; return *this;}
        bidirectional_iterator222 operator++(int) {
            bidirectional_iterator222 tmp(*this);
            ++(*this);
            return tmp;
        }
        bidirectional_iterator222 &operator--(){ this->_ptr -= 1; return *this;}
        bidirectional_iterator222 operator--(int) { bidirectional_iterator222 tmp(*this); (*this)--; return tmp;}



        bidirectional_iterator222 operator[](difference_type n) { return *(*this + n);}

        reference operator*() const { pointer tmp = _ptr; return *tmp;}
        pointer operator->() const { return this->_ptr;}

        pointer base() const {
            return _ptr;
        }

        operator bidirectional_iterator222<const T>() const
        { return (bidirectional_iterator222<const T>(_ptr)); }

    private:
        pointer _ptr;
    };

}
#endif //FT_CONTAINERS_BIDIRECTIONAL_ITERATOR222_HPP
