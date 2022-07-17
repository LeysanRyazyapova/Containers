#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP
#include "utils.hpp"
#include "tree.hpp"
#include <memory>
#include <iostream>
#include <string>
#include <alloca.h>
#include "iterator_traits.hpp"


namespace ft{


    template <class T>
    struct	s_node {
        T			*data;
        struct s_node	*left;
        struct s_node	*right;
        struct s_node	*parent;
        bool				color;
    };

    template <class value_type>
    class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, value_type> {

        class const_tree_iterator;


        typedef s_node<value_type> node;
    public:
        tree_iterator() : _ptr(nullptr ) { }
        ~tree_iterator() { }

        tree_iterator(tree_iterator const & it ) { *this = it; }
        tree_iterator(node *ptr ) { this->_ptr = ptr; }

        tree_iterator & operator=(tree_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        value_type & operator*() const { return *this->_ptr->data; }
        value_type * operator->() const { return this->_ptr->data; }

        tree_iterator & operator++() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        tree_iterator & operator--() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        tree_iterator operator++(int) { tree_iterator tmp = *this; this->operator++(); return tmp; }
        tree_iterator operator--(int) { tree_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==(tree_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=(tree_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        bool operator==(const_tree_iterator const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=(const_tree_iterator const & rhs ) const { return this->_ptr != rhs.getPtr(); }

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
    class const_tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, const value_type> {

        typedef s_node<value_type> node;
    public:
        const_tree_iterator() : _ptr(nullptr ) {}
        ~const_tree_iterator() {}

        const_tree_iterator(const_tree_iterator const & it ) { *this = it; }
        const_tree_iterator(tree_iterator<const value_type> const & it ) { *this = it; }
        const_tree_iterator(node *ptr ) { this->_ptr = ptr; }

        const_tree_iterator & operator=(const_tree_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        const_tree_iterator & operator=(tree_iterator<value_type> const & rhs ) {
            _ptr = rhs.getPtr();
            return *this;
        }

        value_type const & operator*() const { return *this->_ptr->data; }
        value_type const * operator->() const { return this->_ptr->data; }

        const_tree_iterator & operator++() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        const_tree_iterator & operator--() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        const_tree_iterator operator++(int) { const_tree_iterator tmp = *this; this->operator++(); return tmp; }
        const_tree_iterator operator--(int) { const_tree_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==(tree_iterator<value_type> const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=(tree_iterator<value_type> const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        bool operator==(const_tree_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=(const_tree_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        node* getPtr() const { return _ptr; }

    private:
        node* _ptr;

        node *_getMinNode(node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        node *_getMaxNode(node *h) const {
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

    template <class value_type>
    class tree_reverse_iterator : public ft::reverse_iterator<tree_iterator<value_type> > {

        typedef s_node<value_type> node;
    public:
        tree_reverse_iterator() : _ptr(nullptr ) { }
        ~tree_reverse_iterator() { }

        tree_reverse_iterator(tree_reverse_iterator const & it ) { *this = it; }
        tree_reverse_iterator(node *ptr ) { this->_ptr = ptr; }

        tree_reverse_iterator & operator=(tree_reverse_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        value_type & operator*() const { return *this->_ptr->data; }
        value_type * operator->() const { return this->_ptr->data; }

        tree_reverse_iterator & operator++() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        tree_reverse_iterator & operator--() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        tree_reverse_iterator operator++(int) { tree_reverse_iterator tmp = *this; this->operator++(); return tmp; }
        tree_reverse_iterator operator--(int) { tree_reverse_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==(tree_reverse_iterator const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=(tree_reverse_iterator const & rhs ) const { return this->_ptr != rhs._ptr; }

        bool operator==(const_tree_iterator<value_type> const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=(const_tree_iterator<value_type> const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        node* getPtr() const { return _ptr; }

    private:
        node* _ptr;

        node *_getMinNode(node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        node *_getMaxNode(node *h) const {
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

    template <class value_type>
    class const_reverse_iterator : public ft::reverse_iterator<tree_iterator<value_type> > {

        typedef s_node<value_type> node;
    public:
        const_reverse_iterator() : _ptr( nullptr ) {}
        ~const_reverse_iterator() {}

        const_reverse_iterator( const_reverse_iterator const & it ) { *this = it; }
        const_reverse_iterator(tree_reverse_iterator<value_type> const & it ) { *this = it; }
        const_reverse_iterator( node *ptr ) { this->_ptr = ptr; }

        const_reverse_iterator & operator=( const_reverse_iterator const & rhs ) {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        const_reverse_iterator & operator=(tree_reverse_iterator<value_type> const & rhs ) {
            _ptr = rhs.getPtr();
            return *this;
        }

        value_type const & operator*() const { return *this->_ptr->data; }
        value_type const * operator->() const { return this->_ptr->data; }

        const_reverse_iterator & operator++() { this->_ptr = _mapIteratorPrev(this->_ptr); return *this; }
        const_reverse_iterator & operator--() { this->_ptr = _mapIteratorNext(this->_ptr); return *this; }
        const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; this->operator++(); return tmp; }
        const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; this->operator--(); return tmp; }

        bool operator==(tree_reverse_iterator<value_type> const & rhs ) const { return this->_ptr == rhs.getPtr(); }
        bool operator!=(tree_reverse_iterator<value_type> const & rhs ) const { return this->_ptr != rhs.getPtr(); }

        bool operator==(const_tree_iterator<value_type>  const & rhs ) const { return this->_ptr == rhs._ptr; }
        bool operator!=(const_tree_iterator<value_type>  const & rhs ) const { return this->_ptr != rhs._ptr; }

        node* getPtr() const { return _ptr; }

    private:
        node* _ptr;

        node *_getMinNode(node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        node *_getMaxNode(node *h) const {
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
}

#endif