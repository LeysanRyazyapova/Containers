#include <vector>
#include "vector.hpp"
#include <iostream>
#include "utils.hpp"
int main(){

    ////Constructors
    ft::vector<int> first;

// empty vector of ints
    ft::vector<int> second(4,100);// four ints with value 100
    std::cout << "The contents of second are:";
    for (ft::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    ft::vector<int> third(second.begin(),second.end());  // iterating through second
    std::cout << "The contents of third are:";
    for (ft::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    ft::vector<int> fourth(third);                       // a copy of third
    std::cout << "The contents of fourth are:";
    for (ft::vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int) );
    std::cout << "The contents of fifth are:";
    for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';


////Insert
    std::vector<int> myvector (3,100);
    std::vector<int>::iterator it;

    it = myvector.end();
    it = myvector.insert ( it , 200 );
    for(std::vector<int>::iterator it2 = myvector.begin(); it2 != myvector.end(); it2++) {
        std::cout << *it2 << ' ';
    }
    std::cout << "\n";

    myvector.insert (it,2,300);
    for(std::vector<int>::iterator it2 = myvector.begin(); it2 != myvector.end(); it2++) {
        std::cout << *it2 << ' ';
    }
    std::cout << "\n";

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    std::vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());

    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray+3);

    std::cout << "myvector contains:";
    for (it=myvector.begin(); it<myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';
    myvector.reserve(15);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    for(std::vector<int>::iterator it2 = myvector.begin(); it2 != myvector.end(); it2++) {
        std::cout << *it2 << ' ';
    }
    std::cout<< "\n original";
    std::cout << myvector.capacity() << ' ';
    std::cout << myvector.size() << ' ';
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    myvector.clear();
    std::cout << "Before reserve" << '\n';
    fifth.printVector();
    ft::vector<int>::iterator myit = fifth.begin();
    std::cout << "iterator: " << *myit << '\n';
    fifth.reserve(10);
    std::cout << "Fifth after" << '\n';
    fifth.printVector();
    return 0;
}