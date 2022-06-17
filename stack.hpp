//
// Created by Toad Miranda on 5/5/22.
//

#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"
#include <vector>
namespace ft {
    template<class T, class Container = std::vector<T> >
    class stack {
    public:
        typedef Container container_type;
        typedef T value_type;
        typedef typename Container::size_type size_type;
        explicit stack(const container_type& ctnr = container_type()) : _ctnr(ctnr){};
        bool empty() const { return _ctnr.empty(); };
        size_type size() const { return _ctnr.size();};
        value_type& top() {return _ctnr.back();};
        const value_type& top() const { return _ctnr.back();};
        void push(const value_type& val) { _ctnr.push_back();};
        void pop() {_ctnr.pop_back;};
    private:
        container_type _ctnr;
        template <class U, class Cont>
        friend bool operator==(const ft::stack<U,Cont>& lhs, const ft::stack<U,Cont>& rhs;
        template <class U, class Cont>
        friend bool operator!=(const ft::stack<U,Cont>& lhs, const ft::stack<U,Cont>& rhs);
        template <class U, class Cont>
        friend bool operator<(const ft::stack<U,Cont>& lhs, const ft::stack<U,Cont>& rhs);
        template <class U, class Cont>
        friend bool operator<=(const ft::stack<U,Cont>& lhs, const ft::stack<U,Cont>& rhs);
        template <class U, class Cont>
        friend bool operator>(const ft::stack<U,Cont>& lhs, const ft::stack<U,Cont>& rhs);
        template <class U, class Cont>
        friend bool operator>=(const ft::stack<U,Cont>& lhs, const ft::stack<U,Cont>& rhs);
    };
    template <class T, class Container>
    bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {return lhs == rhs;};
    template <class T, class Container>
    bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {return lhs != rhs; };
    template <class T, class Container>
    bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs < rhs; };
    template <class T, class Container>
    bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs <= rhs; };
    template <class T, class Container>
    bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs > rhs; };
    template <class T, class Container>
    bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return lhs >= rhs; };
}

#endif //FT_CONTAINERS_STACK_HPP
