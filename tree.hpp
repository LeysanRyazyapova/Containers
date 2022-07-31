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
        typedef typename ft::tree_iterator<Value> iterator;
        typedef typename ft::const_tree_iterator<Value> const_iterator;
        typedef ft::tree_reverse_iterator<Value> reverse_iterator;
        typedef ft::const_reverse_iterator<Value> const_reverse_iterator;
        typedef Compare key_compare;
        typedef size_t size_type;


        allocator_rebind _alloc_rebind;
        allocator_type _alloc;
        key_compare _comp;
        node *_root;
        node *_begin_node;
        node *_end_node;
        size_t _size;

        static const bool _color_black = false;
        static const bool _color_red = true;

    public:

        tree(const Compare &comp = key_compare(), const allocator_type &a = allocator_type()) : _alloc(a), _comp(comp),
                                                                                                _root(0), _size(0) {
            _begin_node = createEmptyNode();
            _end_node = createEmptyNode();
        }

        template<class InputIterator>
        tree(InputIterator first, InputIterator last,
             const key_compare &comp = key_compare(),
             const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp), _root(nullptr), _size(0) {
            _begin_node = createEmptyNode();
            _end_node = createEmptyNode();
            insert(first, last);
        }


        iterator begin() { return _size != 0 ? ++iterator(_begin_node) : iterator(_end_node); }

        iterator end() { return iterator(_end_node); }

        const_iterator begin() const { return _size != 0 ? ++const_iterator(_begin_node) : const_iterator(_end_node); }

        const_iterator end() const { return const_iterator(_end_node); };

        node* getRoot() { return _root;}
        node* getEndNode() { return _root;}

        ft::pair<iterator, bool> insert(const value_type &val) {
            ft::pair<node *, bool> ret;

            ret = RBInsert(&_root, val);
            if (ret.second)
                _size += 1;
            return ft::make_pair(iterator(ret.first), ret.second);
        }

        iterator insert(iterator position, const value_type &val) {
            static_cast<void>(position);
            return insert(val).first;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0) {
            for (; first != last; ++first) {
                insert(*first);
            }
        }

        node *search(node *h, value_type& val) const {
            if (h == nullptr || h == _end_node || h == _begin_node)
                return nullptr;

            bool less = _comp(val.first, h->data->first);
            bool greater = _comp(h->data->first, val.first);

            if (!less && !greater)
                return h;

            if (less)
                return search(h->left, val);
            else
                return search(h->right, val);
        }

        size_type erase(node* h, const value_type& val) {

            if (h == nullptr)
                return 0;

            size_type count = 0;
            bool less = _comp(val.first, h->data->first);
            bool greater = _comp(h->data->first, val.first);

            if (less) {
                if (h->left == nullptr || h->left == _begin_node)
                    return 0;
                if (!isRed(h->left) && !isRed(h->left->left))
                    h = _moveRedLeft(h);
                count = erase(h->left, val);
            }
            else {
                if (isRed(h->left)) {
                    h = rotateRight(h);
                    count = erase(h->right, val);
                    h = fixUp(h);
                    return count;
                }

                if (!greater && ( h->right == nullptr || h->right == _end_node )) {
                    _treeEraseNodeBot(h);
                    return 1;
                }

                if (greater && (h->right == nullptr || h->right == _end_node))
                    return 0;

                if (!isRed(h->right) && !isRed(h->right->left))
                    h = _moveRedRight(h);

                if (!_comp(h->data->first, val.first)) {
                    _treeEraseCurNodeBySwap(h);
                    count = 1;
                }
                else
                    count = erase(h->right, val);
            }
            h = fixUp(h);
            return count;
        }


        node	*_moveRedLeft(node *h) {
            _invertColors(h);
            if (h->right && isRed(h->right->left)) {
                h->right = rotateRight(h->right);
                h = rotateLeft(h);
                _invertColors(h);
            }
            return h;
        }

        node	*_moveRedRight(node *h) {
            _invertColors(h);
            if (isRed(h->left->left)) {
                h = rotateRight(h);
                _invertColors(h);
            }
            return h;
        }


        void	_treeEraseNodeBot(node *h) {
            node *right;
            node *left;
            bool ifRightNode = h->right != nullptr;
            bool ifLeftNode = h->left != nullptr;

            if (ifRightNode) {
                right = h->right;
                right->parent = h->parent;
            }
            if (ifLeftNode) {
                left = h->left;
                left->parent = h->parent;
            }
            _destroyNode(h);
            if (ifRightNode)
                h = right;
            else if (ifLeftNode)
                h = left;
            else
                h = nullptr;
        }

        void	_treeEraseCurNodeBySwap(node *h) {
            node *minPtr;
            node *toDel;

            minPtr = _getMinNodeWithErase(h->right);
            toDel = h;

            minPtr->color = h->color;
            minPtr->right = h->right;
            minPtr->left = h->left;
            minPtr->parent = h->parent;

            if (minPtr->right) minPtr->right->parent = minPtr;
            if (minPtr->left) minPtr->left->parent = minPtr;
            if (minPtr->parent) {
                if (h == h->parent->right)
                    minPtr->parent->right = minPtr;
                else
                    minPtr->parent->left = minPtr;
            }
            else {
                _root = minPtr;
            }
            _destroyNode(toDel);
        }

        void	_destroyNode(node *ptr) {
            _alloc.destroy(ptr->data);
            _alloc.deallocate(ptr->data, 1);
            _alloc_rebind.deallocate(ptr, 1);
        }

        node *_getMinNodeWithErase(node *h) {
            node *ret;
            if (h->left == nullptr) {
                ret = h;
                if (h->right != nullptr) {
                    h->right->parent = h->parent;
                    h = h->right;
                }
                else
                    h = nullptr;
                return ret;
            }
            ret = _getMinNodeWithErase(h->left);
            h = fixUp(h);
            return ret;
        }



//        size_type treeDelete(iterator position) {
//
//        }

        node *createEmptyNode() {
            node *newNode = _alloc_rebind.allocate(1);
            newNode->color = _color_black;
            newNode->right = nullptr;
            newNode->left = nullptr;
            newNode->parent = nullptr;
            newNode->data = nullptr;
            return newNode;
        }

        node *createNode(node *parent, const value_type &val, bool color) {
            node *newNode = _alloc_rebind.allocate(1);
            newNode->color = color;
            newNode->right = nullptr;
            newNode->left = nullptr;
            newNode->parent = parent;
            newNode->data = _alloc.allocate(1);
            _alloc.construct(newNode->data, val);
            return newNode;
        }


        bool isRed(node *h) {
            if (h == nullptr)
                return _color_black;
            return h->color == _color_red;
        }

        node *rotateLeft(node *h) {
            h->right->parent = h->parent;
            h->parent = h->right;
            if (h->right->left) h->right->left->parent = h;
            node *tmp = h->right->left;
            h->right->left = h;
            h->right = tmp;
            h->parent->color = h->color;
            h->color = _color_red;
            if (h == _root)
                _root = h->parent;
            return h->parent;
        }

        node *rotateRight(node *h) {
            h->left->parent = h->parent;
            h->parent = h->left;
            if (h->left->right) h->left->right->parent = h;
            node *tmp = h->left->right;
            h->left->right = h;
            h->left = tmp;
            h->parent->color = h->color;
            h->color = _color_red;
            if (h == _root)
                _root = h->parent;
            return h->parent;
        }

        void _invertColors(node *h) {
            if (h->right)
                h->right->color = !h->right->color;
            if (h->left)
                h->left->color = !h->left->color;
            h->color = !h->color;
        }

        node *fixUp(node *h) {
            if (h->right && isRed(h->right))
                h = rotateLeft(h);
            if (h->left && h->left->left && isRed(h->left) && isRed(h->left->left))
                h = rotateRight(h);
            if (h->left && h->right && isRed(h->left) && isRed(h->right))
                _invertColors(h);
            if (h == _root && _root->color == _color_red)
                _root->color = _color_black;
            return h;
        }

        ft::pair<node *, bool> RBInsert(node **h, const value_type &val) {
            node *tmp;
            ft::pair<node *, bool> ret;

            if (_root == nullptr) {
                _root = createNode(nullptr, val, _color_black);
                _root->left = _begin_node;
                _root->right = _end_node;
                _begin_node->parent = _root;
                _end_node->parent = _root;
                return ft::make_pair(_root, true);
            }

            bool less = _comp(val.first, (*h)->data->first);
            bool greater = _comp((*h)->data->first, val.first);

            if (!less && !greater) {
                return ft::make_pair((*h), false); // do not make node, just return this (h.first, false)
            }

            if (less && ((*h)->left == nullptr || (*h)->left == _begin_node)) {
                tmp = createNode((*h), val, _color_red);
                if ((*h)->left == _begin_node) {
                    tmp->left = _begin_node;
                    _begin_node->parent = tmp;
                }
                (*h)->left = tmp;
                ret = ft::make_pair(tmp, true);
            } else if (greater && ((*h)->right == nullptr || (*h)->right == _end_node)) {
                tmp = createNode((*h), val, _color_red);
                if ((*h)->right == _end_node) {
                    tmp->right = _end_node;
                    _end_node->parent = tmp;
                }
                (*h)->right = tmp;
                ret = ft::make_pair(tmp, true);
            } else if (less) {
                ret = RBInsert(&((*h)->left), val);
            } else {
                ret = RBInsert(&((*h)->right), val);
            }
            *h = fixUp(*h);
            return ret;// here we should return h and true or false
        }


    };
}
#endif