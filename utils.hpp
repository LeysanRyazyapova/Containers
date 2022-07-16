//
// Created by Toad Miranda on 6/14/22.
//

#ifndef UTILS_HPP
#define UTILS_HPP
namespace ft{
    template<class T, T v>
    struct integral_constant {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant type; // using injected-class-name
        operator value_type() { return value; }
    };
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
    template <class _Tp> struct is_integral                     : public false_type {};
    template <>          struct is_integral<bool>               : public true_type {};
    template <>          struct is_integral<char>               : public true_type {};
    template <>          struct is_integral<signed char>        : public true_type {};
    template <>          struct is_integral<unsigned char>      : public true_type {};
    template <>          struct is_integral<wchar_t>            : public true_type {};
    template <>          struct is_integral<char16_t>           : public true_type {};
    template <>          struct is_integral<char32_t>           : public true_type {};
    template <>          struct is_integral<short>              : public true_type {};
    template <>          struct is_integral<unsigned short>     : public true_type {};
    template <>          struct is_integral<int>                : public true_type {};
    template <>          struct is_integral<unsigned int>       : public true_type {};
    template <>          struct is_integral<long>               : public true_type {};
    template <>          struct is_integral<unsigned long>      : public true_type {};
    template <>          struct is_integral<long long>          : public true_type {};
    template <>          struct is_integral<unsigned long long> : public true_type {};

    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template <class T1, class T2> struct pair {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;

        pair(): first(), second(){};
        template<class U, class V> pair (const pair<U,V>& pr): first(pr.first), second(pr.second){};
        pair (const first_type& a, const second_type& b): first(a), second(b){};
        pair& operator=(const pair& pr){
            return pair(pr);
        };

    };

    template <class T1, class T2>
    bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first==rhs.first && lhs.second==rhs.second; }

    template <class T1, class T2>
    bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs==rhs); }

    template <class T1, class T2>
    bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

    template <class T1, class T2>
    bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs<lhs); }

    template <class T1, class T2>
    bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return rhs<lhs; }

    template <class T1, class T2>
    bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs<rhs); }

    template <class T1,class T2>
    pair<T1,T2> make_pair(T1 x, T2 y)
    {
        return ( pair<T1,T2>(x,y) );
    }
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2,
                                 Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
        while (first1!=last1) {
            if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
                return false;
            ++first1; ++first2;
        }
        return true;
    }

};
#endif //FT_CONTAINERS_UTILS_HPP
