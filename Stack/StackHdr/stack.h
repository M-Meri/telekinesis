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
   // template <typename InputIt>
   // Stack(InputIt, InputIt);
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
    reference peek(size_type);
    const_reference peek(size_type) const;

    public:
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;
    bool operator==(const Stack&) const;
    bool operator!=(const Stack&) const;
    bool operator<(const Stack&)  const;
    bool operator<=(const Stack&) const;
    bool operator>(const Stack&)  const;
    bool operator>=(const Stack&) const;


    private:
    Container st;
};

template <typename T>
std::istream& operator>>(std::istream&, Stack<T>&);
template <typename T>
std::ostream& operator<<(std::ostream&,  const Stack<T>&);

#include "../StackSrc/stack.hpp"

#endif