#ifndef __STACK_H
#define __STACK_H

#include <initializer_list>
#include <deque>
#include <iostream>

template <typename T, typename Container = std::deque<T>>
class Stack
{
    public:
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using const_pointer = const value_type*;
    using size_type = size_t;
    
    public:
    Stack();
    Stack(const std::initializer_list<value_type>&);
    Stack(const Stack&);
    Stack(Stack&&);
    template <typename InputIt>
    Stack(InputIt, InputIt);
    ~Stack();

    const Stack& operator=(const Stack&);
    const Stack& operator=(Stack&&);

    public:
    void push(const_reference);
    void pop();
    reference top();
    const_reference top() const;
    bool empty() const;
    size_type size() const;
    
    bool operator==(const Stack&) const;
    bool operator!=(const Stack&) const;
    bool operator<(const Stack&)  const;
    bool operator<=(const Stack&) const;
    bool operator>(const Stack&)  const;
    bool operator>=(const Stack&) const;

    private:
    Container st;
};

#include "stack.hpp"

#endif