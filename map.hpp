#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>
#include <memory>
#include <iostream>
#include <alloca.h>
#include <algorithm>
#include <string>
#include "tree.hpp"
#include "tree_iterator.hpp"


namespace ft {
    template<class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<ft::pair<const Key, T> >    // map::allocator_type
    >
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;


        class value_compare : public std::binary_function<value_type, value_type, bool> {
            friend class map<key_type, mapped_type, key_compare, Alloc>;
        protected:
            Compare comp;

            value_compare(const Compare &c) : comp(c) {}  // constructed with map's comparison object
        public:
            bool operator()(const value_type &x, const value_type &y) const {
                return comp(x.first, y.first);
            }
        };

        typedef ft::tree_iterator<value_type> iterator;
        typedef ft::const_tree_iterator<value_type> const_iterator;
        typedef ft::tree_reverse_iterator<value_type> reverse_iterator;
        typedef ft::const_reverse_iterator<value_type> const_reverse_iterator;
        typedef typename ft::tree<value_type, key_compare, allocator_type> tree_type;
        typedef value_compare vc;
        typedef ft::s_node<value_type> node;

        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
                 _alloc(alloc), _tree(tree_type(comp, alloc)), _compare(comp) {}

        template<class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _tree(tree_type(first, last, comp, alloc)) {
            (void)comp;
        }

        map(const map &x) : _tree(tree_type(x.begin(), x.end(), x.getComp(), x. getAlloc())) {}

        /*** DESTRUCTION ***/

        ~map() {

        }

        iterator begin() { return _tree.begin(); }
        iterator end() { return _tree.end(); }
        const_iterator begin() const { return _tree.begin(); }
        const_iterator end() const { return _tree.end(); };



        ft::pair<iterator,bool> insert(const value_type& val){
            return _tree.insert(val);
        };

        iterator insert(iterator position, const value_type& val){
            return _tree.insert(position, val);
        };


        size_type erase(const key_type& k) {
            value_type val = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
            size_type ret = _tree.erase(_tree.getRoot(), val);
            return ret;
        }

        void erase (iterator position) {
            erase(position->first);
        }

        void erase(iterator first, iterator last) {
            iterator next;
            while (first != last)
            {
                next = first;
                ++next;
                erase(first);
                first = next;
            }

        }

        iterator find (const key_type& k) {
            value_type val = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
            node *toFind = _tree.search(_tree.getRoot(), val);
            if (toFind == nullptr)
                return iterator(_tree.getEndNode());
            return iterator(toFind);
        }
        const_iterator find (const key_type& k) const {
            value_type val = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
            node *toFind = _treeSearch(_tree.getRoot(), val);
            if (toFind == nullptr)
                return const_iterator(_tree.getEndNode());
            return const_iterator(toFind);
        }

        mapped_type& operator[] (const key_type& k) {
            return (*((_tree.insert(ft::make_pair(k,mapped_type()))).first)).second;
        }

    private:

        allocator_type _alloc;
        tree_type _tree;
        key_compare _compare;

        allocator_type getAlloc() const {
            return _alloc;
        }

        key_compare getComp() const {
            return _compare;
        }
    };
}

#endif