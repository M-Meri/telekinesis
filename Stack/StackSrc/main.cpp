#include <iostream>
#include <initializer_list>
#include "stack.h"

int main()
{
    Stack<int> st1;
    std::cout << st1.empty() << std::endl; // 1
    st1.push(9);
    Stack<int> st2 = st1;
    std::cout << st2.size() << std::endl; // 1
    Stack<int> st3 = {1, 2, 3, 4};
    std::cout << st3.top() << std::endl; // 4
    st3.pop();
    std::cout << st3.top() << std::endl; // 3

    Stack<int> st5 = {4, 5, 90};
    const Stack<int> st4 = st5;
    std::cout << (st4 == st5) << std::endl;//1
    std::cout << (st4 >= st5) << std::endl;//1
    st5.push(8); // 4, 5, 90, 8 
    std::cout << (st4 <= st5) << std::endl;//1
    std::cout << (st4 < st5) <<std::endl;//1
    st5.pop();
    st5.pop();
    st5.push(89); // 4, 5, 89
    std::cout << (st4 > st5) << (st4 != st5) <<std::endl;//11

    return 0;
}