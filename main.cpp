#include <vector>
#include "vector.hpp"
#include <iostream>
#include "utils.hpp"
int main(){

//    ////Constructors
//    ft::vector<int> first;
//
////// empty vector of ints
//    std::cout << "---------STD--------" << "\n";
//    std::vector<int> second2(4,100);// four ints with value 100
//    std::cout << "The contents of second are:";
//    for (std::vector<int>::iterator it = second2.begin(); it != second2.end(); ++it)
//        std::cout << ' ' << *it;
//    std::cout << '\n';
//    std::cout << "Capacity: " << second2.capacity() << "\n";
//    std::cout << "Size: " << second2.size() << "\n";
//    std::cout << '\n';
//
//    std::cout << "---------MY--------" << "\n";
//    ft::vector<int> second(4,100);// four ints with value 100
//    std::cout << "The contents of second are:";
//    for (ft::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
//        std::cout << ' ' << *it;
//    std::cout << '\n';
//    std::cout << "Capacity: " << second.capacity() << "\n";
//    std::cout << "Size: " << second.size() << "\n";
//
//
//    std::cout << "---------STD--------" << "\n";
//    std::vector<int> third(second2.begin(),second2.end());  // iterating through second
//    std::cout << "The contents of third are:";
//    for (std::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
//        std::cout << ' ' << *it;
//    std::cout << '\n';
//    std::cout << "Capacity: " << third.capacity() << "\n";
//    std::cout << "Size: " << third.size() << "\n";
//    std::cout << '\n';
//
//    std::cout << "---------MY--------" << "\n";
//    ft::vector<int> third2(second.begin(),second.end());  // iterating through second
//    std::cout << "The contents of third are:";
//    for (ft::vector<int>::iterator it = third2.begin(); it != third2.end(); ++it)
//        std::cout << ' ' << *it;
//    std::cout << '\n';
//    std::cout << "Capacity: " << third2.capacity() << "\n";
//    std::cout << "Size: " << third2.size() << "\n";
//
//    std::cout << "---------STD--------" << "\n";
//    ft::vector<int> fourth(third2);                       // a copy of third
//    std::cout << "The contents of fourth are:";
//    for (ft::vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
//        std::cout << ' ' << *it;
//    std::cout << '\n';
//    std::cout << "Capacity: " << third2.capacity() << "\n";
//    std::cout << "Size: " << third2.size() << "\n";

    ft::vector<int> vector;
//    vector.insert(vector.begin(), 1200 * 10000, 1);
//    vector.clear();
    std::vector<int> v;
//    v.insert(v.begin(), 1200 * 10000, 1);
    std::cout << "My capacity: " << vector.capacity() << "\n";
    std::cout << "STD capacity: " << v.capacity() << "\n";

//    vector.assign(1000, 1);
//    v.assign(1000, 1);
    vector.push_back(1);
    vector.push_back(2);
    std::cout << "---------MY--------" << "\n";
    for (ft::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    v.push_back(1);
    v.push_back(2);
    ft::vector<int> vector2;
    std::vector<int> v2;
    vector2.push_back(*(vector.end()));
    v2.push_back(*(v.end() - 1));
    vector2.push_back(*(vector.end() - 1));
    v2.push_back(*(v.end() - 2));

    std::cout << "---------MY--------" << "\n";
    for (ft::vector<int>::iterator it = vector2.begin(); it != vector2.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
        std::cout << "Capacity: " << vector2.capacity() << "\n";
    std::cout << "Size: " << vector2.size() << "\n";

    std::cout << "---------STD--------" << "\n";
    for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
        std::cout << "Capacity: " << v2.capacity() << "\n";
    std::cout << "Size: " << v2.size() << "\n";


//    // the iterator constructor can also be used to construct from arrays:
//    int myints[] = {16,2,77,29};
//    ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int) );
//    std::cout << "The contents of fifth are:";
//    for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
//        std::cout << ' ' << *it;
//    std::cout << '\n';


//////Insert
//    std::vector<int> myvector (3,100);
//    std::vector<int>::iterator it;
//
//    it = myvector.end();
//    it = myvector.insert ( it , 200 );
//    for(std::vector<int>::iterator it2 = myvector.begin(); it2 != myvector.end(); it2++) {
//        std::cout << *it2 << ' ';
//    }
//    std::cout << "\n";
//
//    myvector.insert (it,2,300);
//    for(std::vector<int>::iterator it2 = myvector.begin(); it2 != myvector.end(); it2++) {
//        std::cout << *it2 << ' ';
//    }
//    std::cout << "\n";
//
//    // "it" no longer valid, get a new one:
//    it = myvector.begin();
//
//    std::vector<int> anothervector (2,400);
//    myvector.insert (it+2,anothervector.begin(),anothervector.end());
//
//    int myarray [] = { 501,502,503 };
//    myvector.insert (myvector.begin(), myarray, myarray+3);
//
//    std::cout << "myvector contains:";
//    for (it=myvector.begin(); it<myvector.end(); it++)
//        std::cout << ' ' << *it;
//    std::cout << '\n';
//    myvector.reserve(15);
//    std::cout << std::endl;
//    std::cout << std::endl;
//    std::cout << std::endl;
//    for(std::vector<int>::iterator it2 = myvector.begin(); it2 != myvector.end(); it2++) {
//        std::cout << *it2 << ' ';
//    }
//    std::cout<< "\n original";
//    std::cout << myvector.capacity() << ' ';
//    std::cout << myvector.size() << ' ';
//    std::cout << std::endl;
//    std::cout << std::endl;
//    std::cout << std::endl;
//    myvector.clear();
//    std::cout << "Before reserve" << '\n';
//    fifth.printVector();
//    ft::vector<int>::iterator myit = fifth.begin();
//    std::cout << "iterator: " << *myit << '\n';
//    fifth.reserve(10);
//    std::cout << "Fifth after" << '\n';
//    fifth.printVector();

//    std::vector<int> myvector;
//    for (int i=0; i<100; i++) myvector.push_back(i);
//    std::cout << "capacity: " << (int) myvector.capacity() << '\n';
//    return 0;
}