#include <iostream>
#include <initializer_list>
#include "vector.h"

int main()
{
    Vector<int> v0 = {3, 4, 5 , 6};
    v0.at(2) = 10; // 3, 4, 10, 6
    const Vector<int> v1 = v0;
    std::cout << v1[2] << std::endl << (v1 == v0) << std::endl;//10 1
    std::cout << *v1.begin() << std::endl; // 3
    std::cout << *v0.cbegin() << std::endl; // 3
    std::cout << *v1.rbegin() << std::endl; // 6
    std::cout << *v0.crbegin() << std::endl; // 6
    std::cout << v1.empty() << std::endl; // 0
    std::cout << v1.size() << ' ' << v1.capacity() << std::endl; // 4 4
    v0.reserve(6);
    std::cout << v0.capacity() << v0.size() << std::endl; // 6, 4


    std::initializer_list init = {1, 2, 15};
    v0.insert(v0.begin() + 2, init); // 3 4 1 2 15 10 6
    for(int i = 0; i < v0.size(); ++i)
    {
        std::cout << v0[i] << ",   ";
    }
    std::cout << std::endl;
    for(Vector<int>::iterator it = v0.begin(); it != v0.end(); ++it)
    {
        std::cout << *it << ' ';// 3 4 1 2 15 10 6
    }

    std::cout << std::endl;
    Vector<int>::reverse_iterator f = v0.rbegin();
    Vector<int>::reverse_iterator l = v0.rend();
    for(Vector<int>::reverse_iterator it = f; it != l; ++it)
    {
        std::cout << *it << ' ';// 6 10 15 2 1 4 3
    }
    std::cout << std::endl;

    Vector<int> v2 = v0;
    Vector<int>::iterator first = v0.begin() + 2;
    Vector<int>::iterator last = v0.begin() + 4;
    v2.insert(v2.begin() + 1, first, last);
    for(Vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
    {
        std::cout << *it << ' ';// 3 1 2 4 1 2 15 10 6
    }
    std::cout << std::endl;
    Vector<int> v3(first, last);
    for(Vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
    {
        std::cout << *it << ' ';// 1 2
    }
    std::cout << std::endl;

    size_t cnt = 3;
    const int& ref = 90;
    v3.insert(v3.begin(), cnt, ref);
    for(Vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
    {
        std::cout << *it << ' ';// 90 90 90 1 2
    }
    std::cout << std::endl;
    v3.erase(v3.begin() + 3);
    for(Vector<int>::iterator it = v3.begin(); it != v3.end(); ++it)
    {
        std::cout << *it << ' ';// 90 90 90 2
    }
    std::cout << std::endl;
    v3.erase(v3.begin(), v3.end());
    std::cout << v3.empty() << std::endl; // 0
    v3.push_back(78);
    std::cout << v3.at(0) << std::endl; // 78
    v3.pop_back();
    std::cout << v3.empty() << std::endl; // 0
    std::cout << v3.size() << std::endl; // 0
    v3.resize(10);
    std::cout << v3.size() << std::endl; // 10

    std::cout << (v2 > v0) << (v2 >= v0) <<std::endl; //11
    std::cout << (v3 < v1) << (v0 != v3) << std::endl; //01
}