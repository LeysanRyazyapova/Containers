namespace ft {
    template <class T>
    typedef struct	s_node {
        T			*data;
        struct s_node	*left;
        struct s_node	*right;
        struct s_node	*parent;
        bool				color;
    };
    template<class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value>>
    class tree {
    private:
        typedef Value value_type;
        typedef s_node<value_type> node;
        typedef Alloc allocator_type;
        typedef typename allocator_type::template rebind<node>::other allocator_rebind;
        allocator_rebind _alloc_rebind;
        allocator_type _alloc;
        Compare _comp;


        node		*_root;
        node		*_begin_node;
        node		*_end_node;
        size_t	_size;

        value_type insert (const value_type& val) {
            std::pair<node*, bool> ret;

            ret = _treeInsert(&_root, val);
            if (ret.second)
                _size += 1;
            return std::make_pair(iterator(ret.first), ret.second);
        }
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

        void _destroyNode(node *ptr) {
            _alloc.destroy(ptr->data);
            _alloc.deallocate(ptr->data, 1);
            _alloc_rebind.deallocate(ptr, 1);
        }

        bool _isRed(node *h) {
            if (h == nullptr)
                return _color_black;
            return h->color == _color_red;
        }

        node *_rotateLeft(node *h) {
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

        node *_rotateRight(node *h) {
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

        node *_moveRedLeft(node *h) {
            _invertColors(h);
            if (h->right && _isRed(h->right->left)) {
                h->right = _rotateRight(h->right);
                h = _rotateLeft(h);
                _invertColors(h);
            }
            return h;
        }

        node *_moveRedRight(node *h) {
            _invertColors(h);
            if (_isRed(h->left->left)) {
                h = _rotateRight(h);
                _invertColors(h);
            }
            return h;
        }

        node *_getMinNode(node *h) const {
            if (h->left == nullptr)
                return h;
            return _getMinNode(h->left);
        }

        node *_fixUp(node *h) {
            if (h->right && _isRed(h->right))
                h = _rotateLeft(h);
            if (h->left && h->left->left && _isRed(h->left) && _isRed(h->left->left))
                h = _rotateRight(h);
            if (h->left && h->right && _isRed(h->left) && _isRed(h->right))
                _invertColors(h);
            if (h == _root && _root->color == _color_red)
                _root->color = _color_black;
            return h;
        }

        std::pair<node *, bool> _treeInsert(node **h, const value_type &val) {
            node *tmp;
            std::pair<node *, bool> ret;

            if (_root == nullptr) {
                _root = _createNode(nullptr, val, _color_black);
                _root->left = _begin_node;
                _root->right = _end_node;
                _begin_node->parent = _root;
                _end_node->parent = _root;
                return std::make_pair(_root, true);
            }

            bool less = _comp(val.first, (*h)->data->first);
            bool greater = _comp((*h)->data->first, val.first);

            if (!less && !greater) {
                return std::make_pair((*h), false); // do not make node, just return this (h.first, false)
            }

            if (less && ((*h)->left == nullptr || (*h)->left == _begin_node)) {
                tmp = _createNode((*h), val, _color_red);
                if ((*h)->left == _begin_node) {
                    tmp->left = _begin_node;
                    _begin_node->parent = tmp;
                }
                (*h)->left = tmp;
                ret = std::make_pair(tmp, true);
            } else if (greater && ((*h)->right == nullptr || (*h)->right == _end_node)) {
                tmp = _createNode((*h), val, _color_red);
                if ((*h)->right == _end_node) {
                    tmp->right = _end_node;
                    _end_node->parent = tmp;
                }
                (*h)->right = tmp;
                ret = std::make_pair(tmp, true);
            } else if (less) {
                ret = _treeInsert(&((*h)->left), val);
            } else {
                ret = _treeInsert(&((*h)->right), val);
            }
            *h = _fixUp(*h);
            return ret;// here we should return h and true or false
        }

        node *_treeSearch(node *h, const key_type &k) const {
            if (h == nullptr || h == _end_node || h == _begin_node)
                return nullptr;

            bool less = _comp(k, h->data->first);
            bool greater = _comp(h->data->first, k);

            if (!less && !greater)
                return h;

            if (less)
                return _treeSearch(h->left, k);
            else
                return _treeSearch(h->right, k);
        }

        void _treeEraseNodeBot(node **h) {
            node *right;
            node *left;
            bool ifRightNode = (*h)->right != nullptr;
            bool ifLeftNode = (*h)->left != nullptr;

            if (ifRightNode) {
                right = (*h)->right;
                right->parent = (*h)->parent;
            }
            if (ifLeftNode) {
                left = (*h)->left;
                left->parent = (*h)->parent;
            }
            _destroyNode(*h);
            if (ifRightNode)
                *h = right;
            else if (ifLeftNode)
                *h = left;
            else
                *h = nullptr;
        }

        void _treeEraseMin(node **h) {
            if ((*h)->left == nullptr || (*h)->left == _begin_node) {
                _treeEraseNodeBot(h);
                return;
            }

            if (!_isRed((*h)->left) && !_isRed((*h)->left->left))
                *h = _moveRedLeft(*h);

            _treeEraseMin(&(*h)->left);

            *h = _fixUp(*h);
        }

        size_type _treeErase(node **h, const key_type &k) {
            if (*h == nullptr)
                return 0;

            size_type count = 0;
            bool less = _comp(k, (*h)->data->first);
            bool greater = _comp((*h)->data->first, k);

            if (less) {
                if ((*h)->left == nullptr || (*h)->left == _begin_node)
                    return 0;
                if (!_isRed((*h)->left) && !_isRed((*h)->left->left))
                    *h = _moveRedLeft(*h);
                count = _treeErase(&(*h)->left, k);
            } else {
                if (_isRed((*h)->left)) {
                    *h = _rotateRight(*h);
                    count = _treeErase(&(*h)->right, k);
                    *h = _fixUp(*h);
                    return count;
                }

                if (!greater && ((*h)->right == nullptr || (*h)->right == _end_node)) {
                    _treeEraseNodeBot(h);
                    return 1;
                }

                if (greater && ((*h)->right == nullptr || (*h)->right == _end_node))
                    return 0;

                if (!_isRed((*h)->right) && !_isRed((*h)->right->left))
                    *h = _moveRedRight(*h);

                if (!_comp((*h)->data->first, k)) {
                    _treeEraseCurNodeBySwap(h);
                    count = 1;
                } else
                    count = _treeErase(&(*h)->right, k);
            }
            *h = _fixUp(*h);
            return count;
        }

        bool _isRightChild(node *h) {
            if (h->parent->right == h)
                return true;
            return false;
        }

        node *_getMinNodeWithErase(node **h) {
            node *ret;
            if ((*h)->left == nullptr) {
                ret = *h;
                if ((*h)->right != nullptr) {
                    (*h)->right->parent = (*h)->parent;
                    *h = (*h)->right;
                } else
                    *h = nullptr;
                return ret;
            }
            ret = _getMinNodeWithErase(&(*h)->left);
            *h = _fixUp(*h);
            return ret;
        }

        void _treeEraseCurNodeBySwap(node **h) {
            node *minPtr;
            node *toDel;

            minPtr = _getMinNodeWithErase(&(*h)->right);
            toDel = *h;

            minPtr->color = (*h)->color;
            minPtr->right = (*h)->right;
            minPtr->left = (*h)->left;
            minPtr->parent = (*h)->parent;

            if (minPtr->right) minPtr->right->parent = minPtr;
            if (minPtr->left) minPtr->left->parent = minPtr;
            if (minPtr->parent) {
                if (_isRightChild(*h))
                    minPtr->parent->right = minPtr;
                else
                    minPtr->parent->left = minPtr;
            } else {
                _root = minPtr;
            }
            _destroyNode(toDel);
        }

        iterator _treeBound(node *h, const key_type &k, bool isLower) const {
            if (h == nullptr || h == _end_node || h == _begin_node)
                return iterator(_end_node);

            bool less = _comp(k, h->data->first);
            bool greater = _comp(h->data->first, k);

            if (!less && !greater) {
                if (isLower)
                    return iterator(h);
                return ++iterator(h);
            }

            if (less) {
                if (h->left == nullptr || h->left == _begin_node) {
                    if (isLower)
                        return (h->left != _begin_node) ? --iterator(h) : iterator(h);
                    return iterator(h);
                }
                return _treeBound(h->left, k, isLower);
            } else {
                if (h->right == nullptr || h->right == _end_node) {
                    if (isLower)
                        return (h->right != _end_node) ? iterator(h) : iterator(_end_node);
                    return ++iterator(h);
                }
                return _treeBound(h->right, k, isLower);
            }
        }
    }
}