#include <iostream>
#include <initializer_list>
#include "../StackHdr/stack.h"

int main()
{
    Stack<int> st1;
    std::cout << st1.empty() << std::endl; // 1
    st1.push(9);
    std::cout << st1[0] << std::endl; // 9
    Stack<int> st2 = st1;
    std::cout << st2.size() << std::endl; // 1
    Stack<int> st3 = {1, 2, 3, 4};
    std::cout << st3 << std::endl; // 4 3 2 1
    st3.pop();
    std::cout << st3 << std::endl; // 3 2 1
    std::cout << st3.top() << std::endl; // 3
    std::cout << st3.peek(2) << std::endl; // 1
    return 0;
}