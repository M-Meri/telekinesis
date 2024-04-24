#include <iostream>
#include "../Forward_List_Headers/forward_list.h"

int main()
{
    Forward_list<int> ob1(3, 10);
    Forward_list<int> ob2 = ob1;
    Forward_list<int> ob3 = {10, 10, 1};

    std::cout << ob1.length() << std::endl; // 3
    std::cout << ob2.length() << std::endl; // 3
    std::cout << ob3.length() << std::endl; // 3

    std::cout << (ob2 == ob1) << (ob3 == ob2) << std::endl; // 10

    std::cout << ob1[0] <<std::endl;//10
    std::cout << ob2[0] <<std::endl;//10
    ob1.reverse();
    ob2.reverse();
    ob3.reverse();
    std::cout << ob3 << std::endl; // 1 10 10

    ob1.insert(2, 7);
    std::cout << ob1 << std::endl; // 10 10 7 10

    ob3.pop_front();
    std::cout << ob3 << std::endl; // 10 10

    ob1.push_back(2);
    std::cout << ob1 << std::endl; // 10 10 7 10 2

    ob1.remove(1);
    std::cout << ob1 << std::endl; // 10 7 10 2

    std::cout << ob1.at(2) << ob1.back() << std::endl; // 102
}