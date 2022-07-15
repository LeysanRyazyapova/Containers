#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>
#include <memory>
#include <iostream>
#include <alloca.h>
#include <algorithm>
#include <string>
#include "tree.hpp"
#include "bidirectional_iterator.hpp"


namespace ft{
    template < class Key,                                     // map::key_type
            class T,                                       // map::mapped_type
            class Compare = std::less<Key>,                     // map::key_compare
            class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
    > class map
    {
    public:
        typedef Key 								                            key_type;
        typedef T									                            mapped_type;
        typedef ft::pair<const key_type , mapped_type>	                        value_type;
        typedef Compare								                            key_compare;
        typedef Alloc							                        	    allocator_type;
        typedef value_type&							                            reference;
        typedef const value_type&					                            const_reference;
        typedef value_type*							                            pointer;
        typedef const value_type*					                            const_pointer;
        typedef ptrdiff_t 							                            difference_type;
        typedef size_t 								                            size_type;
        typedef ft::map_iterator<node<value_type>*, value_type>                      iterator;
        typedef ft::map_iterator<const node<value_type>*, value_type>                const_iterator;
        typedef ft::map_reverse_iterator<Key, T>                                      reverse_iterator;
        typedef ft::map_reverse_iterator<const Key, T>                                const_reverse_iterator;
        class value_compare
        {
            friend class map<key_type, mapped_type, key_compare, Alloc>;
        protected:
            Compare         comp;
            value_compare   (Compare c) : comp(c){}
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator() (const value_type& x, const value_type& y) const
            {
                return (comp(x.first, y.first));
            }
        };


    private:
        typedef typename allocator_type::template rebind<node<value_type> >::other           alloc_node;
        typedef typename allocator_type::template rebind<Tree<value_type> >::other           alloc_tree;
        allocator_type  _alloc;
        alloc_node      _allocNode;
        alloc_tree      _allocTree;
        key_compare     _comp;
        Tree<value_type>*   _tree;


    public:
        map() {
            _tree = _allocTree.allocate(sizeof(Tree<value_type>));
            _allocTree.construct(_tree);
        }

        explicit map (const key_compare& comp,
                      const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp) {
            _tree = _allocTree.allocate(sizeof(Tree<value_type>));
            _allocTree.construct(_tree);
        }

        template <class InputIterator>
        explicit  map (InputIterator first, InputIterator last,
                       const key_compare& comp = key_compare(),
                       const allocator_type& alloc = allocator_type()) : _comp(comp),_alloc(alloc) {
            _tree = _allocTree.allocate(sizeof(Tree<value_type>));
            _allocTree.construct(_tree);
            for(; first != last; ++first)
                insert(ft::make_pair(first->first, first->second));
        }

        map (const map& x) : _alloc(x._alloc), _comp(x._comp) {
            _tree = _allocTree.allocate(sizeof(Tree<value_type>));
            _allocTree.construct(_tree, *(x._tree));
            addTree(x._tree->root);

        }
        map& operator=(const map& other) {
            if (this == &other)
                return *this;
            _comp = other._comp;
            _alloc = other._alloc;
            clearMap();
            _tree = _allocTree.allocate(sizeof(Tree<value_type>));
            _allocTree.construct(_tree, *other._tree);
            addTree(other._tree->root);
            return *this;
        }
        ~map(){
            clearMap();
        }

//	    iterators:

        iterator begin() {return _tree->getFirst();}
        const_iterator begin() const {return _tree->getFirst();}
        iterator end() {return _tree->getEnd();}
        const_iterator end() const {return _tree->getEnd();}
        reverse_iterator rbegin() {return iterator(_tree->getLast());}
        const_reverse_iterator rbegin() const {return iterator(_tree->getLast());}
        reverse_iterator rend() {return reverse_iterator(iterator(_tree->getEnd()));}
        const_reverse_iterator rend() const {return const_reverse_iterator(iterator(_tree->getEnd()));}

//	    //capacity:

        bool empty() const {return _tree->_size == 0;}
        size_type size() const {return _tree->_size;}
        size_type max_size() const {return _alloc.max_size();}
//      Element access:

        mapped_type& operator[] (const key_type& k) {
            return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
        }

//	    //Modifers:

        ft::pair<iterator,bool> insert (const value_type& val){ return insertNode(_tree->root, val);}

        iterator insert (iterator position, const value_type& val) {
            if (position == end())
                return insertNode(_tree->root, val).first;
            else{
                if (position->first > val.first){
                    iterator cur = position;
                    --cur;
                    while (cur != end() && cur->first >= val.first){
                        --position;
                        --cur;
                    }
                } else if (position->first < val.first) {
                    iterator cur = position;
                    ++cur;
                    while (cur != end() && cur->first <= val.first) {
                        ++position;
                        ++cur;
                    }
                }
            }
            return insertNode(position.base(), val).first;
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last) {
            for (; first != last; ++first)
                insert(ft::make_pair(first->first, first->second));
        }

        void erase (iterator position) {
            iterator tmp = position;
            _tree->deleteNode(tmp.base());
        }

        size_type erase (const key_type& k) {
            return _tree->deleteNode(find(k).base());
        }

        void erase (iterator first, iterator last) {
            iterator tmp;

            for (; first != last; ++first) {
                tmp = first;
                _tree->deleteNode(tmp.base());
            }
        }

        void swap (map& x) {
            std::swap(_tree, x._tree);
        }

        void clear() {
            clearMap();
            _tree = _allocTree.allocate(sizeof(Tree<value_type>));
            _allocTree.construct(_tree);
        }

//      Observers:

        key_compare key_comp() const { return _comp;}

        value_compare value_comp() const { return value_compare(key_comp());}

//      Operations:

        iterator find (const key_type& k) {
            node<value_type> *cur = _tree->root;

            while (!cur->NIL) {
                if (k == cur->value->first)
                    return cur;
                else
                    cur = _comp(k, cur->value->first) ? cur->left : cur->right;
            }
            return (end());
        }

        const_iterator find (const key_type& k) const {
            node<value_type> *cur = _tree->root;

            while (!cur->NIL) {
                if (k == cur->value->first)
                    return cur;
                else
                    cur = _comp(k, cur->value->first) ? cur->left : cur->right;
            }
            return (end());
        }

        size_type count (const key_type& k) const {
            return (find(k) == end()) ? 0 : 1;
        }

        iterator lower_bound (const key_type& k) {
            node<value_type> *cur = _tree->root;

            while (!cur->NIL) {
                if (k == cur->value->first)
                    return iterator(cur);
                else {
                    if (_comp(k, cur->value->first)) {
                        if (!cur->left->NIL)
                            cur = cur->left;
                        else
                            return iterator(cur);
                    } else {
                        if (!cur->right->NIL)
                            cur = cur->right;
                        else
                            return ++iterator(cur);
                    }
                }
            }
            return end();
        }

        const_iterator lower_bound (const key_type& k) const {
            node<value_type> *cur = _tree->root;

            while (!cur->NIL) {
                if (k == cur->value->first)
                    return const_iterator(cur);
                else {
                    if (_comp(k, cur->value->first)) {
                        if (!cur->left->NIL)
                            cur = cur->left;
                        else
                            return const_iterator(cur);
                    } else {
                        if (!cur->right->NIL)
                            cur = cur->right;
                        else
                            return ++const_iterator(cur);
                    }
                }
            }
            return end();
        }

        iterator upper_bound (const key_type& k) {
            iterator cur = lower_bound(k);

            if (cur == end())
                return cur;
            else
            if (_comp(k, cur->first))
                return cur;
            else
                return ++cur;
        }

        const_iterator upper_bound (const key_type& k) const {
            const_iterator cur = lower_bound(k);

            if (cur == end())
                return cur;
            else
            if (_comp(k, cur->first))
                return cur;
            else
                return ++cur;
        }

        ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
            return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
        }

        ft::pair<iterator,iterator>             equal_range (const key_type& k) {
            return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
        }

        allocator_type get_allocator() const { return _alloc;}



    private:

        void clearTree(node<value_type> *tr){
            if (tr->NIL)
                return;
            if (!tr->left->NIL)
                clearTree(tr->left);
            if (!tr->right->NIL)
                clearTree(tr->right);
            _allocNode.destroy(tr);
            _allocNode.deallocate(tr, sizeof(node<value_type>));
        }

        void clearMap() {
            clearTree(_tree->root);
            _allocTree.destroy(_tree);
            _allocTree.deallocate(_tree, sizeof(Tree<value_type>));
        }

        void addTree(node<value_type> *tmp) {
            if (!tmp->left->NIL)
                addTree(tmp->left);
            if (!tmp->NIL)
                insert(*tmp->value);
            if (!tmp->right->NIL)
                addTree(tmp->right);
        }

        ft::pair<iterator, bool> insertNode(node<value_type> *tmp, const value_type& value) {
            node<value_type> *current, *parent, *x;

            current = tmp;
            parent = 0;
            while (!current->NIL) {
                if (value.first == current->value->first) return ft::make_pair(current, false);
                parent = current;
                current = _comp(value.first, current->value->first) ?
                          current->left : current->right;
            }

            x = _allocNode.allocate(sizeof(node<value_type>));
            _allocNode.construct(x, value);
            x->parent = parent;
            x->left = &_tree->tr;
            x->right = &_tree->tr;
            x->color = RED;

            if (parent) {
                if (_comp(value.first, parent->value->first))
                    parent->left = x;
                else
                    parent->right = x;
            } else {
                _tree->root = x;
            }

            _tree->insert(x);

            if (x == _tree->getLast()) { _tree->tr.parent = x; }
            if (x == _tree->getFirst()) { _tree->tr.begin = x; }
            _tree->_size++;
            return ft::make_pair(x, true);
        }
    };
}

#endif