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
}
#endif //FT_CONTAINERS_UTILS_HPP