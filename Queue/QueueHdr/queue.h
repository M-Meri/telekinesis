#ifndef _QUEUE_H
#define _QUEUE_H

#include <vector>
#include <initializer_list>
#include <iostream>

template <typename T, typename Container = std::vector<T>>
class Queue
{
    public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = value_type* const;
    using container_type = Container;

    public:
    Queue();
    Queue(const std::initializer_list<value_type>&);
    Queue(const Queue&);
    Queue(Queue&&);
    ~Queue();

    const Queue& operator=(const Queue&);
    const Queue& operator=(Queue&&);

    public:
    bool empty() const;
    void clear();
    void push(value_type);
    void pop();
    size_type size() const;
    reference front();
    const_reference at(size_type) const;

    reference operator[](size_type);
    

    private:
    container_type queue;
};

template <typename T, typename Container = std::vector<T>>
bool operator==(const Queue<T, Container>&, const Queue<T, Container>&);
template <typename T, typename Container = std::vector<T>>
bool operator!=(const Queue<T, Container>&, const Queue<T, Container>&);
template <typename T, typename Container = std::vector<T>>
std::istream& operator>>(std::istream&, Queue<T, Container>&);
template <typename T, typename Container = std::vector<T>>
std::ostream& operator<<(std::ostream&, const Queue<T, Container>&);

#include "../QueueSrc/queue.hpp"

#endif