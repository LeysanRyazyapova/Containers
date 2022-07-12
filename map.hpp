//
// Created by Toad Miranda on 7/10/22.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <functional>
#include "utils.hpp"
#include "bidirectional_iterator.hpp"
#include "map_iterator.hpp"
namespace ft {
    template < class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
    > class map{
        typedef Key key_type;
        typedef T mapped_type;
        typedef typename ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef typename ft::map_iterator<s_node<value_type>, value_type> iterator;


        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
        public:
            Compare comp;
            value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

    private:
        typedef typename ft::s_node<value_type> t_node;
        typedef typename allocator_type::template rebind<t_node>::other allocator_rebind;
        allocator_rebind	_alloc_rebind;
        allocator_type		_alloc;
        Compare				_comp;

        t_node		*_root;
        t_node		*_begin_node;
        t_node		*_end_node;
        size_type	_size;

        static const bool	_color_black = false;
        static const bool	_color_red = true;


    };
}
#endif //FT_CONTAINERS_MAP_HPP
