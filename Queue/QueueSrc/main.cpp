#include <initializer_list>
#include <vector>
#include <iostream>
#include "../QueueHdr/queue.h"

int main()
{
    Queue<int> q1;
    std::cout << q1.empty() << std::endl;// 1
    q1.push(1);
    std::cout << q1.front() << std::endl;// 1
    Queue<int> q2 = q1;
    std::cout << (q1 != q2) << std::endl;// 0
    q2.push(2);
    std::cout << q2.back() << std::endl; // 2
    q2 = q1;
    std::cout << q2.size() << std::endl; // 1 
    q2.pop();
    q2.push(89);
    q2.push(3);
    std::cout << q2.back() << std::endl; // 3
    Queue<int> q3 = {1,2,3,4,5};
    q3.front() = 10;
    std::cout << q3.front() << std::endl; // 10
    q3.back() = 8;
    std::cout << q3.back() << std::endl; // 8
    Queue<int> q4 = {89, 90, 75};
    std::cout << q4.back() << std::endl;//75

    q4.push(8);
    q4.push(56);
    const Queue<int> q5 = q4;
    std::cout << (q5 == q4) << (q5 < q4) << std::endl;//10
    q4.push(8);
    std::cout << (q5 < q4) << (q5 <= q4)<< (q5 > q4) << std::endl; //110
    q4.pop();
    q4.pop();
    std::cout << (q5 >= q4) << (q5 > q4) <<std::endl;//11
}