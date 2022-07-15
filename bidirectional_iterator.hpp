#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP
#include "utils.hpp"
#include "tree.hpp"
#include <memory>
#include <iostream>
#include <string>
#include <alloca.h>
#include "iterator_traits.hpp"
#define BLACK 0
#define RED 1

namespace ft{


    template <class value_type>
    class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, value_type> {

        class const_bidirectional_iterator;


        typedef s_node<value_type> node;
    public:
        bidirectional_iterator() : _ptr( nullptr ) { }
        ~bidirectional_iterator() { }

        bidirectional_iterator( bidirectional_iterator const & it ) { *this = it; }
        bidirectional_iterator( node *ptr ) { this->_ptr = ptr; }

        bidirectional_iterator & operator=( bidirectional_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        value_type & operator*() const { return *this->_ptr->data; }
        value_type * operator->() const { return this->_ptr->data; }

        bidirectional_iterator & operator++() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        bidirectional_iterator & operator--() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        bidirectional_iterator operator++(int) { bidirectional_iterator tmp = *this; this->operator++(); return tmp; }
        bidirectional_iterator operator--(int) { bidirectional_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==( bidirectional_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=( bidirectional_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        bool operator==( const_bidirectional_iterator const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=( const_bidirectional_iterator const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        node* getPtr() const { return _ptr; }

    private:
        node* _ptr;

        node *_getMinNode(node *h)  {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        node *_getMaxNode(node *h)  {
            if (h->right == nullptr)
                return h;
            return _getMaxNode(h->right);
        }

        node *_mapIteratorNext(node *h)  {
            if (h->right)
                return _getMinNode(h->right);
            if (h->parent && h->parent->left == h)
                return h->parent;
            node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->right;
            } while (tmp->parent->right == tmp);
            return tmp->parent;
        }

        node *_mapIteratorPrev(node *h) {
            if (h->left)
                return _getMaxNode(h->left);
            if (h->parent && h->parent->right == h)
                return h->parent;
            node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->left;
            } while (tmp->parent->left == tmp);
            return tmp->parent;
        }

    };

    template<class value_type>
    class const_bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, value_type const> {

    public:
        const_bidirectional_iterator() : _ptr( nullptr ) {}
        ~const_bidirectional_iterator() {}

        const_bidirectional_iterator( const_bidirectional_iterator const & it ) { *this = it; }
        const_bidirectional_iterator( iterator const & it ) { *this = it; }
        const_bidirectional_iterator( node *ptr ) { this->_ptr = ptr; }

        const_bidirectional_iterator & operator=( const_bidirectional_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        const_bidirectional_iterator & operator=( iterator const & rhs ) {
            _ptr = rhs.getPtr();
            return *this;
        }

        value_type const & operator*() const { return *this->_ptr->data; }
        value_type const * operator->() const { return this->_ptr->data; }

        const_bidirectional_iterator & operator++() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        const_bidirectional_iterator & operator--() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        const_bidirectional_iterator operator++(int) { const_bidirectional_iterator tmp = *this; this->operator++(); return tmp; }
        const_bidirectional_iterator operator--(int) { const_bidirectional_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==( iterator const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=( iterator const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        bool operator==( const_bidirectional_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=( const_bidirectional_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        _t_node* getPtr() const { return _ptr; }

    private:
        _t_node* _ptr;

        _t_node *_getMinNode(_t_node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        _t_node *_getMaxNode(_t_node *h) const {
            if (h->right == nullptr)
                return h;
            return _getMaxNode(h->right);
        }

        _t_node *_mapIteratorNext(_t_node *h)  {
            if (h->right)
                return _getMinNode(h->right);
            if (h->parent && h->parent->left == h)
                return h->parent;
            _t_node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->right;
            } while (tmp->parent->right == tmp);
            return tmp->parent;
        }

        _t_node *_mapIteratorPrev(_t_node *h) {
            if (h->left)
                return _getMaxNode(h->left);
            if (h->parent && h->parent->right == h)
                return h->parent;
            _t_node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->left;
            } while (tmp->parent->left == tmp);
            return tmp->parent;
        }

    };

    class reverse_iterator : public ft::reverse_iterator<map::iterator> {

    public:
        reverse_iterator() : _ptr( nullptr ) { }
        ~reverse_iterator() { }

        reverse_iterator( reverse_iterator const & it ) { *this = it; }
        reverse_iterator( _t_node *ptr ) { this->_ptr = ptr; }

        reverse_iterator & operator=( reverse_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        value_type & operator*() const { return *this->_ptr->data; }
        value_type * operator->() const { return this->_ptr->data; }

        reverse_iterator & operator++() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        reverse_iterator & operator--() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        reverse_iterator operator++(int) { reverse_iterator tmp = *this; this->operator++(); return tmp; }
        reverse_iterator operator--(int) { reverse_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==( reverse_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=( reverse_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        bool operator==( const_reverse_iterator const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=( const_reverse_iterator const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        _t_node* getPtr() const { return _ptr; }

    private:
        _t_node* _ptr;

        _t_node *_getMinNode(_t_node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        _t_node *_getMaxNode(_t_node *h) const {
            if (h->right == nullptr)
                return h;
            return _getMaxNode(h->right);
        }

        _t_node *_mapIteratorNext(_t_node *h)  {
            if (h->right)
                return _getMinNode(h->right);
            if (h->parent && h->parent->left == h)
                return h->parent;
            _t_node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->right;
            } while (tmp->parent->right == tmp);
            return tmp->parent;
        }

        _t_node *_mapIteratorPrev(_t_node *h) {
            if (h->left)
                return _getMaxNode(h->left);
            if (h->parent && h->parent->right == h)
                return h->parent;
            _t_node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->left;
            } while (tmp->parent->left == tmp);
            return tmp->parent;
        }

    };

    class const_reverse_iterator : public ft::reverse_iterator<map::const_iterator> {

    public:
        const_reverse_iterator() : _ptr( nullptr ) {}
        ~const_reverse_iterator() {}

        const_reverse_iterator( const_reverse_iterator const & it ) { *this = it; }
        const_reverse_iterator( reverse_iterator const & it ) { *this = it; }
        const_reverse_iterator( _t_node *ptr ) { this->_ptr = ptr; }

        const_reverse_iterator & operator=( const_reverse_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        const_reverse_iterator & operator=( reverse_iterator const & rhs ) {
            _ptr = rhs.getPtr();
            return *this;
        }

        value_type const & operator*() const { return *this->_ptr->data; }
        value_type const * operator->() const { return this->_ptr->data; }

        const_reverse_iterator & operator++() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        const_reverse_iterator & operator--() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; this->operator++(); return tmp; }
        const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==( reverse_iterator const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=( reverse_iterator const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        bool operator==( const_reverse_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=( const_reverse_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        _t_node* getPtr() const { return _ptr; }

    private:
        _t_node* _ptr;

        _t_node *_getMinNode(_t_node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        _t_node *_getMaxNode(_t_node *h) const {
            if (h->right == nullptr)
                return h;
            return _getMaxNode(h->right);
        }

        _t_node *_mapIteratorNext(_t_node *h)  {
            if (h->right)
                return _getMinNode(h->right);
            if (h->parent && h->parent->left == h)
                return h->parent;
            _t_node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->right;
            } while (tmp->parent->right == tmp);
            return tmp->parent;
        }

        _t_node *_mapIteratorPrev(_t_node *h) {
            if (h->left)
                return _getMaxNode(h->left);
            if (h->parent && h->parent->right == h)
                return h->parent;
            _t_node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->left;
            } while (tmp->parent->left == tmp);
            return tmp->parent;
        }

    };
}

#endif