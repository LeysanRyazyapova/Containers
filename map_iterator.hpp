//
// Created by Toad Miranda on 7/12/22.
//

#ifndef FT_CONTAINERS_MAP_ITERATOR_HPP
#define FT_CONTAINERS_MAP_ITERATOR_HPP
#include "utils.hpp"
#include "Tree.hpp"
#include <memory>
#include <iostream>
#include <string>
#include <alloca.h>
#include "iterator_traits.hpp"

namespace ft{

    template<class Node, class T>
           class map_iterator: ft::iterator<ft::bidirectional_iterator_tag, Node> {
           public:
               map_iterator() : _ptr( nullptr ) { }
               ~map_iterator() { }

               map_iterator( map_iterator const & it ) { *this = it; }
               map_iterator( Node *ptr ) { this->_ptr = ptr; }

               map_iterator & operator=( map_iterator const & rhs ) {
                   if (this != &rhs)
                       _ptr = rhs._ptr;
                   return *this;
               }

               T & operator*() const { return *this->_ptr->data; }
               T * operator->() const { return this->_ptr->data; }

               map_iterator & operator++() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
               map_iterator & operator--() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
               map_iterator operator++(int) { map_iterator tmp = *this; this->operator++(); return tmp; }
               map_iterator operator--(int) { map_iterator tmp = *this; this->operator--(); return tmp; }

               bool operator==( map_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
               bool operator!=( map_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }


               Node* getPtr() const { return _ptr; }
           private:
               Node* _ptr;
           };

    template<class Node, class T>
    class const_map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Node const> {

    public:
        const_map_iterator() : _ptr( nullptr ) {}
        ~const_map_iterator() {}

        const_map_iterator( const_map_iterator const & it ) { *this = it; }
        const_map_iterator(  map_iterator<Node, T> const & it ) { *this = it; }
        const_map_iterator( Node *ptr ) { this->_ptr = ptr; }

        const_map_iterator & operator=( const_map_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        const_map_iterator & operator=( map_iterator<Node, T> const & rhs ) {
            _ptr = rhs.getPtr();
            return *this;
        }

        T const & operator*() const { return *this->_ptr->data; }
        T const * operator->() const { return this->_ptr->data; }

        const_map_iterator & operator++() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        const_map_iterator & operator--() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        const_map_iterator operator++(int) { const_map_iterator tmp = *this; this->operator++(); return tmp; }
        const_map_iterator operator--(int) { const_map_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==( map_iterator<Node, T> const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=( map_iterator<Node, T> const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        bool operator==( const_map_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=( const_map_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        Node* getPtr() const { return _ptr; }

    private:
        Node* _ptr;

        Node *_getMinNode(Node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        Node *_getMaxNode(Node *h) const {
            if (h->right == nullptr)
                return h;
            return _getMaxNode(h->right);
        }

        Node *_mapIteratorNext(Node *h)  {
            if (h->right)
                return _getMinNode(h->right);
            if (h->parent && h->parent->left == h)
                return h->parent;
            Node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->right;
            } while (tmp->parent->right == tmp);
            return tmp->parent;
        }

        Node *_mapIteratorPrev(Node *h) {
            if (h->left)
                return _getMaxNode(h->left);
            if (h->parent && h->parent->right == h)
                return h->parent;
            Node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->left;
            } while (tmp->parent->left == tmp);
            return tmp->parent;
        }

    };




    template<class Node, class T>
    class map_reverse_iterator : public ft::reverse_iterator<map_iterator<Node, T>> {

    public:
        map_reverse_iterator() : _ptr( nullptr ) { }
        ~map_reverse_iterator() { }

        map_reverse_iterator( map_reverse_iterator const & it ) { *this = it; }
        map_reverse_iterator( Node *ptr ) { this->_ptr = ptr; }

        map_reverse_iterator & operator=( map_reverse_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        T & operator*() const { return *this->_ptr->data; }
        T * operator->() const { return this->_ptr->data; }

        map_reverse_iterator & operator++() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        map_reverse_iterator & operator--() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        map_reverse_iterator operator++(int) { map_reverse_iterator tmp = *this; this->operator++(); return tmp; }
        map_reverse_iterator operator--(int) { map_reverse_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==( map_reverse_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=( map_reverse_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        bool operator==( const_reverse_iterator const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=( const_reverse_iterator const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        Node* getPtr() const { return _ptr; }

    private:
        Node* _ptr;

        Node *_getMinNode(Node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        Node *_getMaxNode(Node *h) const {
            if (h->right == nullptr)
                return h;
            return _getMaxNode(h->right);
        }

        Node *_mapIteratorNext(Node *h)  {
            if (h->right)
                return _getMinNode(h->right);
            if (h->parent && h->parent->left == h)
                return h->parent;
            Node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->right;
            } while (tmp->parent->right == tmp);
            return tmp->parent;
        }

        Node *_mapIteratorPrev(Node *h) {
            if (h->left)
                return _getMaxNode(h->left);
            if (h->parent && h->parent->right == h)
                return h->parent;
            Node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->left;
            } while (tmp->parent->left == tmp);
            return tmp->parent;
        }

    };

    template<class Node, class T>
    class const_reverse_iterator : public ft::reverse_iterator<const_map_iterator<Node, T>> {

    public:
        const_reverse_iterator() : _ptr( nullptr ) {}
        ~const_reverse_iterator() {}

        const_reverse_iterator( const_reverse_iterator const & it ) { *this = it; }
        const_reverse_iterator( map_reverse_iterator<Node, T> const & it ) { *this = it; }
        const_reverse_iterator( Node *ptr ) { this->_ptr = ptr; }

        const_reverse_iterator & operator=( const_reverse_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        const_reverse_iterator & operator=( map_reverse_iterator<Node, T> const & rhs ) {
            _ptr = rhs.getPtr();
            return *this;
        }

        T const & operator*() const { return *this->_ptr->data; }
        T const * operator->() const { return this->_ptr->data; }

        const_reverse_iterator & operator++() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        const_reverse_iterator & operator--() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; this->operator++(); return tmp; }
        const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==( map_reverse_iterator<Node, T> const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=( map_reverse_iterator<Node, T> const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        bool operator==( const_reverse_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=( const_reverse_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        Node* getPtr() const { return _ptr; }

    private:
        Node* _ptr;

        Node *_getMinNode(Node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        Node *_getMaxNode(Node *h) const {
            if (h->right == nullptr)
                return h;
            return _getMaxNode(h->right);
        }

        Node *_mapIteratorNext(Node *h)  {
            if (h->right)
                return _getMinNode(h->right);
            if (h->parent && h->parent->left == h)
                return h->parent;
            Node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->right;
            } while (tmp->parent->right == tmp);
            return tmp->parent;
        }

        Node *_mapIteratorPrev(Node *h) {
            if (h->left)
                return _getMaxNode(h->left);
            if (h->parent && h->parent->right == h)
                return h->parent;
            Node *tmp = h;
            do {
                tmp = tmp->parent;
                if (tmp == nullptr)
                    return h->left;
            } while (tmp->parent->left == tmp);
            return tmp->parent;
        }

    };

}
#endif //FT_CONTAINERS_MAP_ITERATOR_HPP
