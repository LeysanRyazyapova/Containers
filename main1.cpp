//
// Created by Toad Miranda on 7/15/22.
//

//#include "stack.hpp"
//#include <stack>
#include "vector.hpp"
#include <vector>
#include "map.hpp"
#include <map>
template<class T>
void printSTDVector(std::vector<T> vector1);
template<class T>
void printVector(ft::vector<T> v);
template<class Key, class Value>
void printSTDMap(std::map<Key, Value> m);

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
    bool operator() (const char& lhs, const char& rhs) const
    {return lhs<rhs;}
};
template<class Key, class Value>
void printMap(ft::map<Key, Value> m);
int main() {
//
//    ///*VECTOR*///
//
//    std::cout << "Constructors\n\n";
//    //// constructors used in the same order as described above:
//    std::vector<int> first;                                // empty vector of ints
//    std::cout << "The contents of STD empty vector of ints are:";
//    printSTDVector(first);
//
//    ft::vector<int> first2;                                // empty vector of ints
//    std::cout << "The contents of FT empty vector of ints are:";
//    printVector(first2);
//
//    std::vector<int> second (4,100);                       // four ints with value 100
//    std::cout << "The contents of STD four ints with value 100 are:";
//    printSTDVector(second);
//
//    ft::vector<int> second2 (4,100);                       // four ints with value 100
//    std::cout << "The contents of FT four ints with value 100 are:";
//    printVector(second2);
//
//    std::vector<int> third (second.begin(),second.end());  // iterating through second
//    std::cout << "The contents of STD construct with iterator are:";
//    printSTDVector(third);
//
//    ft::vector<int> third2(second2.begin(),second2.end());  // iterating through second
//    std::cout << "The contents of FT construct with iterator are:";
//    printVector(third2);
//
//    std::vector<int> fourth (third);                       // a copy of third
//    std::cout << "The contents of STD copy constructor are:";
//    printSTDVector(fourth);
//
//    ft::vector<int> fourth2 (third2);                       // a copy of third
//    std::cout << "The contents of FT copy constructor are:";
//    printVector(fourth2);
//
//    // the iterator constructor can also be used to construct from arrays:
//    int myints[] = {16,2,77,29};
//    std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
//    std::cout << "The contents of STD array constructor are:";
//    printSTDVector(fifth);
//
//    ft::vector<int> fifth2 (myints, myints + sizeof(myints) / sizeof(int) );
//    std::cout << "The contents of FT array constructor are:";
//    printVector(fifth2);
//
//    ///*operator=*///
//    std::vector<int> foo(3,0);
//    std::vector<int> bar(5,0);
//
//    bar = foo;
//    foo = std::vector<int>();
//
//    std::cout << "STD: ";
//    printSTDVector(foo);
//    printSTDVector(bar);
//
//    ft::vector<int> foo2 (3,0);
//    ft::vector<int> bar2 (5,0);
//
//    bar2 = foo2;
//    foo2 = ft::vector<int>();
//
//    std::cout << "FT: ";
//    printVector(foo2);
//    printVector(bar2);
//
//
//    ///*rbegin and rend*///
//
//    std::vector<int> myvector (5);  // 5 default-constructed ints
//    int i=0;
//    std::vector<int>::reverse_iterator rit = myvector.rbegin();
//    for (; rit!= myvector.rend(); ++rit)
//        *rit = ++i;
//    std::cout << "STD contains:";
//    printSTDVector(myvector);
//
//    ft::vector<int> myvector2 (5);  // 5 default-constructed ints
//    i=0;
//    ft::vector<int>::reverse_iterator rit2 = myvector2.rbegin();
//    for (; rit2!= myvector2.rend(); ++rit2)
//        *rit2 = ++i;
//    std::cout << "FT contains:";
//    printVector(myvector2);
//
//    ///*max_size*///
//
//    // set some content in the vector:
//    for (int i=0; i<101; i++) myvector.push_back(i);
//    printSTDVector(myvector);
//    std::cout << "STD max_size: " << myvector.max_size() << "\n";
//
//    for (int i=0; i<101; i++) myvector2.push_back(i);
//    printVector(myvector2);
//    std::cout << "FT max_size: " << myvector2.max_size() << "\n";
//
//    ////*MAP*///
//
//    std::map<char,int> map1;
//
//    std::less<int> k;
//
//
//    k(4, 5);
//    map1['a']=10;
//    map1['b']=30;
//    map1['c']=50;
//    map1['d']=70;
//
//    std::map<char,int> map2 (map1.begin(),map1.end());
//
//    std::map<char,int> map3 (map2);
//
//    std::map<char,int,classcomp> map4;                 // class as Compare
//
//    bool(*fn_pt)(char,char) = fncomp;
//    std::map<char,int,bool(*)(char,char)> map5 (fn_pt);
//
//    printSTDMap(map2);


    ///***FT**///

    ft::map<char,int> map12;

    map12['a'] = 10;
    map12['b']=30;
    map12['c']=50;
    map12['d']=70;


    ft::map<char,int> map22 (map12.begin(),map12.end());

    ft::map<char,int> map32 (map22);

    ft::map<char,int,classcomp> map42;                 // class as Compare

    //ft::map<char,int,bool(*)(char,char)> map52 (fn_pt);

    printMap(map12);

    map12.erase('a');

    printMap(map12);

    return 0;
}
template<typename T>
void printSTDVector(std::vector<T> vector1) {
    for (typename std::vector<T>::iterator it = vector1.begin(); it != vector1.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    std::cout << "capacity: " << vector1.capacity() << " size: " << vector1.size() << "\n";
}
template<class T>
void printVector(ft::vector<T> v){
    for (typename ft::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    std::cout << "capacity: " << v.capacity() << " size: " << v.size() << "\n";
}
template<class Key, class Value>
void printSTDMap(std::map<Key, Value> m) {
    std::cout << "STD MAP" << std::endl;
    for (typename std::map<Key,Value>::iterator it=m.begin(); it!=m.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    std::cout << '\n';
    return;
}
template<class Key, class Value>
void printMap(ft::map<Key, Value> m) {
    std::cout << "FT MAP" << std::endl;
    for (typename ft::map<Key,Value>::iterator it=m.begin(); it!=m.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    std::cout << '\n';
    return;
}