#ifndef __STACK_HPP
#define __STACK_HPP

#include <initializer_list>
#include <deque>
#include <iostream>
#include "../StackHdr/stack.h"

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
Stack<T, Container>::~Stack()
{}

template <typename T, typename Container>
const Stack<T, Container>& Stack<T, Container>::operator=(const Stack& rhv)
{
    if(this != &rhv){
        st = rhv.st;
    }
    return *this;
}

template <typename T, typename Container>
const Stack<T, Container>& Stack<T, Container>::operator=(Stack&& rhv)
{
    if(this != &rhv)
    {
        st = std::move(rhv.st);
    }
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
    if(!empty())
    {
        st.pop_back();
    }
}

template <typename T, typename Container>
Stack<T, Container>::reference Stack<T, Container>::top()
{
    return st[st.size() - 1];
}

template <typename T, typename Container>
Stack<T, Container>::const_reference Stack<T, Container>::top() const
{
    return st[st.size() - 1];
}

template <typename T, typename Container>
bool Stack<T, Container>::empty() const
{
    return st.size() == 0;
}

template <typename T, typename Container>
Stack<T, Container>::size_type Stack<T, Container>::size() const
{
    return st.size();
}

template <typename T, typename Container>
Stack<T, Container>::reference Stack<T, Container>::peek(size_type index)
{
    return st.at(size() - 1 - index);
}

template <typename T, typename Container>
Stack<T, Container>::const_reference Stack<T, Container>::peek(size_type index) const
{
    return st.at(size() - 1 - index);
}

template <typename T, typename Container>
Stack<T, Container>::reference Stack<T, Container>::operator[](size_type index)
{
    return peek(index);
}

template <typename T, typename Container>
Stack<T, Container>::const_reference Stack<T, Container>::operator[](size_type index) const
{
    return peek(index);
}

template <typename T, typename Container>
bool Stack<T, Container>::operator==(const Stack<T, Container>& other) const
{
    if(size() != other.size())
    {
        return false;
    }
    for(size_type i = 0; i < size(); ++i)
    {
        if((*this)[i] != other[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T, typename Container>
bool Stack<T, Container>::operator>(const Stack& other) const
{
    if(size() > other.size())
    {
        return true;
    }
    if(size() < other.size())
    {
        return false;
    }
    for(size_type i = 0; i < size(); ++i)
    {
        if((*this)[i] < other[i])
        {
            return false;
        }
    }
    return (*this != other);
}

template <typename T, typename Container>
bool Stack<T, Container>::operator>=(const Stack& other) const
{
    return (*this == other) || (*this > other );
}

template <typename T, typename Container>
bool Stack<T, Container>::operator<=(const Stack& other) const
{
    return (*this == other) || (*this < other );
}

template <typename T, typename Container>
bool Stack<T, Container>::operator<(const Stack& other) const
{
    if(size() < other.size())
    {
        return true;
    }
    if(size() > other.size())
    {
        return false;
    }
    for(size_type i = 0; i < size(); ++i)
    {
        if((*this)[i] > other[i])
        {
            return false;
        }
    }
    return (*this != other);
}

template <typename T, typename Container>
bool Stack<T, Container>::operator!=(const Stack& other) const
{
    return !(*this == other);
}

template <typename T>
std::istream& operator>>(std::istream& in, Stack<T>& stack)
{
    stack.clear();
    T newval;
    while(in >> newval) 
    {
        stack.push(newval);
        if(in.peek() == '\n')
        {
            break;
        }
    }
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Stack<T>& stack)
{
    for(size_t i = 0; i < stack.size(); ++i)
    {
        out << stack[i] << ' ';
    }
    return out;
}

#endif