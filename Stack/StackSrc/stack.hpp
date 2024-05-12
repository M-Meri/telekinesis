#ifndef __STACK_HPP
#define __STACK_HPP

#include <initializer_list>
#include <deque>
#include "stack.h"

template <typename T, typename Container>
Stack<T, Container>::Stack() : st{}
{}

template <typename T, typename Container>
Stack<T, Container>::Stack(const std::initializer_list<value_type>& init) : st{init}
{}

template <typename T, typename Container>
Stack<T, Container>::Stack(const Stack& rhv) : st{rhv.st}
{}

template <typename T, typename Container>
Stack<T, Container>::Stack(Stack&& rhv) : st{std::forward(rhv)}
{}

template <typename T, typename Container>
template <typename InputIt>
Stack<T, Container>::Stack(InputIt first, InputIt last) : st(first, last)
{}

template <typename T, typename Container>
Stack<T, Container>::~Stack()
{}

template <typename T, typename Container>
const Stack<T, Container>& Stack<T, Container>::operator=(const Stack& rhv)
{
    st = rhv.st;
    return *this;
}

template <typename T, typename Container>
const Stack<T, Container>& Stack<T, Container>::operator=(Stack&& rhv)
{
    st = std::move(rhv.st);
    return *this;
}

template <typename T, typename Container>
void Stack<T, Container>::push(const_reference val)
{
    st.push_back(val);
}

template <typename T, typename Container>
void Stack<T, Container>::pop()
{
    st.pop_back();
}

template <typename T, typename Container>
Stack<T, Container>::reference Stack<T, Container>::top()
{
    return st.back();
}

template <typename T, typename Container>
Stack<T, Container>::const_reference Stack<T, Container>::top() const
{
    return st.back();
}

template <typename T, typename Container>
bool Stack<T, Container>::empty() const
{
    return st.empty();
}

template <typename T, typename Container>
Stack<T, Container>::size_type Stack<T, Container>::size() const
{
    return st.size();
}

template <typename T, typename Container>
bool Stack<T, Container>::operator==(const Stack<T, Container>& other) const
{
    return st == other.st;
}

template <typename T, typename Container>
bool Stack<T, Container>::operator>(const Stack& other) const
{
    return !(*this <= other);
}

template <typename T, typename Container>
bool Stack<T, Container>::operator>=(const Stack& other) const
{
    return !(*this < other);
}

template <typename T, typename Container>
bool Stack<T, Container>::operator<=(const Stack& other) const
{
    if(size() < other.size())
    {
        return true;
    }
    if(size() > other.size())
    {
        return false;
    }
    for(int i = size() - 1; i >= 0; --i)
    {
        if(st[i] > other.st[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T, typename Container>
bool Stack<T, Container>::operator<(const Stack& other) const
{
    return (*this <= other) && (*this != other);
}

template <typename T, typename Container>
bool Stack<T, Container>::operator!=(const Stack& other) const
{
    return st != other.st;
}

#endif