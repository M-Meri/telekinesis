#ifndef __STACK_H
#define __STACK_H

#include <initializer_list>
#include <vector>
#include <iostream>

template <typename T>
class Stack
{
    public:
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using const_pointer = value_type* const;
    using size_type = size_t;
    
    public:
    Stack();
    Stack(const std::initializer_list<value_type>&);
    Stack(const Stack&);
    Stack(Stack&&);
    ~Stack();

    const Stack& operator=(const Stack&);
    const Stack& operator=(Stack&&);

    public:
    void push(const_reference);
    void pop();
    reference top();
    bool empty() const;
    size_type size() const;
    reference peek(size_type);

    public:
    reference operator[](size_type index);


    private:
    std::vector<value_type> st;
};

template <typename T>
bool operator==(const Stack<T>&, const Stack<T>&);
template <typename T>
bool operator!=(const Stack<T>&, const Stack<T>&);
template <typename T>
std::istream& operator>>(std::istream&, Stack<T>&);
template <typename T>
std::ostream& operator<<(std::ostream&,  const Stack<T>&);

#include "../StackSrc/stack.hpp"

#endif