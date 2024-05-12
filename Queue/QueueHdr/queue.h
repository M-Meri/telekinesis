#ifndef _QUEUE_H
#define _QUEUE_H

#include <deque>
#include <initializer_list>
#include <iostream>

template <typename T, typename Container = std::deque<T>>
class Queue
{
    public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using container_type = Container;

    public:
    Queue();
    Queue(const std::initializer_list<value_type>&);
    Queue(const Queue&);
    Queue(Queue&&);
    template <typename InputIt>
    Queue(InputIt, InputIt);
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
    const_reference front() const;
    reference back();
    const_reference back() const;
    
    bool operator==(const Queue&) const;
    bool operator!=(const Queue&) const;
    bool operator<(const Queue&) const;
    bool operator<=(const Queue&) const;
    bool operator>(const Queue&) const;
    bool operator>=(const Queue&) const;

    private:
    container_type queue;
};

#include "queue.hpp"

#endif