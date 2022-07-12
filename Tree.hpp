//
// Created by Toad Miranda on 7/12/22.
//

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP
#include "utils.hpp"
#define BLACK 0
#define RED 1

namespace ft {
    template<class value_type>
    struct	s_node {
        value_type			*data;
        struct _s_tree_node	*left;
        struct _s_tree_node	*right;
        struct _s_tree_node	*parent;
        bool				color;
    };


}
#endif //FT_CONTAINERS_TREE_HPP
