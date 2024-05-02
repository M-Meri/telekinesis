#include <initializer_list>
#include <vector>
#include <iostream>
#include "../QueueHdr/queue.h"

int main()
{
    Queue<int> q1;
    std::cout << q1.empty() << std::endl;// 1
    q1.push(1);
    std::cout << q1[0] << std::endl;// 1
    Queue<int> q2 = q1;
    std::cout << (q1 != q2) << std::endl;// 0
    q2.push(2);
    std::cout << q2 << std::endl; // 1 2
    q2 = q1;
    std::cout << q2.size() << std::endl; // 1 
    q2.pop();
    q2.push(89);
    q2.push(3);
    std::cout << q2.at(1) << std::endl; // 3
    Queue<int> q3 = {1,2,3,4,5};
    q3.front() = 10;
    std::cout << q3 << std::endl; // 10 2 3 4 5
    Queue<int> q4;
    std::cin >> q4;
    std::cout << q4 << std::endl;
}