#ifndef TREE_HPP
#define TREE_HPP
#include "tree_iterator.hpp"
#include "map.hpp"
namespace ft {

    template<class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> >
    class tree {
    private:
        typedef Value value_type;
        typedef s_node<value_type> node;
        typedef Alloc allocator_type;
        typedef typename allocator_type::template rebind<node>::other allocator_rebind;
        typedef typename ft::tree_iterator<Value>			iterator;
        typedef typename ft::const_tree_iterator<Value>	const_iterator;
        typedef	ft::tree_reverse_iterator<Value> reverse_iterator;
        typedef	ft::const_reverse_iterator<Value> const_reverse_iterator;
        typedef Compare key_compare;
        typedef size_t size_type;


        allocator_rebind _alloc_rebind;
        allocator_type _alloc;
        key_compare _comp;
        node		*_root;
        node		*_begin_node;
        node		*_end_node;
        size_t	_size;

        static const bool	_color_black = false;
        static const bool	_color_red = true;

    public:

        tree(const Compare &comp = key_compare(), const allocator_type& a = allocator_type()):_alloc(a), _comp(comp), _root(0), _size(0) {
            _begin_node = _createEmptyNode();
            _end_node = _createEmptyNode();
        }

        template<class InputIterator>
        tree(InputIterator first, InputIterator last,
             const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _root(nullptr), _size(0){
            _begin_node = _createEmptyNode();
            _end_node = _createEmptyNode();
            insert(first, last);
        }


        iterator begin() { return _size != 0 ? ++iterator(_begin_node) : iterator(_end_node); }
        iterator end() { return iterator(_end_node); }
        const_iterator begin() const { return _size != 0 ? ++const_iterator(_begin_node) : const_iterator(_end_node); }
        const_iterator end() const { return const_iterator(_end_node); };

        ft::pair<iterator,bool> insert(const value_type& val) {
            ft::pair<node*, bool> ret;

            ret = RBInsert(val);
            if (ret.second)
                _size += 1;
            return ft::make_pair(iterator(ret.first), ret.second);
        }

//        iterator insert(iterator position, const value_type& val) {
//            static_cast<void>(position);
//            return insert(val).first;
//        }

//        template <class InputIterator>
//        void insert(InputIterator first, InputIterator last,
//                     typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
//            for ( ; first != last; ++first) {
//                insert(*first);
//            }
//        }

//        size_type treeDelete(iterator position) {
//
//        }

        node *_createEmptyNode() {
            node *newNode = _alloc_rebind.allocate(1);
            newNode->color = _color_black;
            newNode->right = nullptr;
            newNode->left = nullptr;
            newNode->parent = nullptr;
            newNode->data = nullptr;
            return newNode;
        }

        node *_createNode(node *parent, const value_type &val, bool color) {
            node *newNode = _alloc_rebind.allocate(1);
            newNode->color = color;
            newNode->right = nullptr;
            newNode->left = nullptr;
            newNode->parent = parent;
            newNode->data = _alloc.allocate(1);
            _alloc.construct(newNode->data, val);
            return newNode;
        }


        bool _isRed(node *h) {
            if (h == nullptr)
                return _color_black;
            return h->color == _color_red;
        }

        void leftRotate(node *h) {
            node *tmp = h->right;
            h->right = tmp->left;

            if(tmp->left != nullptr)
                tmp->left.parent = h;
            tmp->parent = h->parent;
            if(h == _root)
                _root = tmp;
            else if(h == h->parent->left)
                h->parent->left = tmp;
            else
                h->parent->right = tmp;
            tmp->left = h;
            h->parent = tmp;
        }

        void rightRotate(node *h) {
            node *tmp = h->left;
            h->left = tmp->right;

            if(tmp->right != nullptr)
                tmp->right->parent = h;
            tmp->parent == h->parent;
            if(h == _root)
                _root = tmp;
            else if(h == h->parent->left)
                h->parent->left = tmp;
            else
                h->parent->right = tmp;
            tmp->right = h;
            h->parent = tmp;
        }

        ft::pair<node *, bool> RBInsert(const value_type& val) {
            node *tmp = nullptr;
            node *ptr = _root;
            node *newNode = _createNode(nullptr, val, _color_red);

            ft::pair<node *, bool> ret;

            if (_root == nullptr) {
                _root = _createNode(nullptr, val, _color_black);
                _root->left = _begin_node;
                _root->right = _end_node;
                _begin_node->parent = _root;
                _end_node->parent = _root;
                return ft::make_pair(_root, true);
            }

            while(ptr != nullptr) {
                tmp = ptr;
                bool less = _comp(val.first, ptr->data->first);
                if(less)
                    ptr = ptr->left;
                else
                    ptr = ptr->right;
            }
            newNode->parent = tmp;
            bool less = _comp(val.first, tmp->data->first);
            bool greater = _comp(tmp->data->first, val.first);
            if(!less && !greater)
                return ft::make_pair(*tmp, false);
            else if(less)
                tmp->left = newNode;
            else if(greater)
                tmp->right = newNode;
            RBInsertFixUP(newNode);
            return ft::make_pair(_root, true);
        }

        void RBInsertFixUP(node *h) {
            while (_is_red(h->parent->color)) {
                if(h->parent == h->parent->parent->left) {
                    node *tmp = h->parent->parent->right;
                        if(_is_red(tmp->parent)) {
                            h->parent->color = _color_black;
                            tmp->color = _color_black;
                            h->parent->parent->color = _color_red;
                            h = h->parent->parent;
                        } else {
                            if(h == h->parent->right) {
                                h = h->parent;
                                leftRotate(h);
                            }
                            h->parent->color = _color_black;
                            h->parent->parent->color = _color_red;
                            rightRotate(h->parent->parent);
                        }
                } else {
                    if (h->parent == h->parent->parent->right) {
                        node *tmp = h->parent->parent->left;
                        if(_is_red(tmp->parent)) {
                            h->parent->color = _color_black;
                            tmp->color = _color_black;
                            h->parent->parent->color = _color_red;
                            h = h->parent->parent;
                        } else {
                            if(h == h->parent->right) {
                                h = h->parent;
                                rightRotate(h);
                            }
                            h->parent->color = _color_black;
                            h->parent->parent->color = _color_red;
                            leftRotate(h->parent->parent);
                        }
                    }
                }
            }
            _root->color = _color_red;
        }
    };
}
#endif