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


//        class value_compare : public std::binary_function<value_type, value_type, bool> {
//        public:
//            Compare comp;
//
//            value_compare(const Compare &c) : comp(c) {}  // constructed with map's comparison object
//        public:
////            typedef bool result_type;
////            typedef value_type first_argument_type;
////            typedef value_type second_argument_type;
//
//
//            bool operator()(const value_type &x, const value_type &y) const {
//                return comp(x.first, y.first);
//            }
//        };

        typedef ft::tree_iterator<value_type> iterator;
        typedef ft::const_tree_iterator<value_type> const_iterator;
        typedef ft::tree_reverse_iterator<value_type> reverse_iterator;
        typedef ft::const_reverse_iterator<value_type> const_reverse_iterator;
        typedef typename ft::tree<value_type, key_compare, allocator_type> tree_type;
        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
                 _alloc(alloc), _tree(tree_type(comp, alloc)), _compare(comp) {}

        template<class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type()) : _tree(tree<value_type>(first, last)) {
            (void)comp;
            (void)alloc;
        }

        map(const map &x) : _tree(tree_type(x.begin(), x.end())) {}

        /*** DESTRUCTION ***/

        ~map() {

        }

        iterator begin() { return _tree.begin(); }
        iterator end() { return _tree.end(); }
        const_iterator begin() const { return _tree.begin(); }
        const_iterator end() const { return _tree.end(); };

//        size_t erase (const key_type& k) {
//            iterator pos = find(k);
//            if ( pos == this->end() ) {
//                return (0);
//            }
//            _tree.erase(pos);
//            return (1);
//        }

        mapped_type& operator[] (const key_type& k) {
            return (*(( _tree.insert(ft::make_pair<const Key, T>(k,T())) ).first)).second;
        }

    private:

        allocator_type _alloc;
        tree_type _tree;
        key_compare _compare;
    };
}

#endif