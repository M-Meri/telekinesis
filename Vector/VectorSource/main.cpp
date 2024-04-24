#include <iostream>
#include "../VectorHeaders/Vector.hpp"

int main()
{
    vector<int> vec = {1, 2, 3};

    std::cout << vec.getSize() << ' ' << vec.capacity() << std::endl; // 3 6
    std::cout << std::boolalpha << vec.empty() << std::noboolalpha << std::endl; // fasle
    std::cout << vec.front() << "  " << vec.at(1) << "  " << vec.back() << std::endl; // 1 2 3

    vec.insert(3, 7);
    std::cout << vec.at(3) << std::endl; // 7

    vec.remove(1);
    std::cout << vec.at(1) << std::endl; // 3



    vector<int> vec2(2, 78);
    std::cout << vec2.at(1) << std::endl; // 78

    vec2.clear();
    std::cout << vec2.empty() << std::endl; // 1


    vector<int> vec3(8);
    std::cout << vec3.getSize() << std::endl; // 8
}