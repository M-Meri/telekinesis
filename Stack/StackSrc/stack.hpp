#ifndef __STACK_HPP
#define __STACK_HPP

#include <initializer_list>
#include <vector>
#include <iostream>
#include "../StackHdr/stack.h"

template <typename T>
Stack<T>::Stack() : st{}
{}

template <typename T>
Stack<T>::Stack(const std::initializer_list<value_type>& init) : st{init}
{}

template <typename T>
Stack<T>::Stack(const Stack& rhv) : st{rhv.st}
{}

template <typename T>
Stack<T>::Stack(Stack&& rhv) : st{std::forward(rhv)}
{}

template <typename T>
Stack<T>::~Stack()
{}

template <typename T>
const Stack<T>& Stack<T>::operator=(const Stack& rhv)
{
    if(this != &rhv){
        st = rhv.st;
    }
    return *this;
}

template <typename T>
const Stack<T>& Stack<T>::operator=(Stack&& rhv)
{
    if(this != &rhv)
    {
        st = std::move(rhv.st);
    }
    return *this;
}

template <typename T>
void Stack<T>::push(const_reference val)
{
    st.push_back(val);
}

template <typename T>
void Stack<T>::pop()
{
    if(!empty())
    {
        st.pop_back();
    }
}

template <typename T>
Stack<T>::reference Stack<T>::top()
{
    return st[st.size() - 1];
}

template <typename T>
bool Stack<T>::empty() const
{
    return st.size() == 0;
}

template <typename T>
Stack<T>::size_type Stack<T>::size() const
{
    return st.size();
}

template <typename T>
Stack<T>::reference Stack<T>::peek(size_type index)
{
    return st.at(size() - 1 - index);
}

template <typename T>
Stack<T>::reference Stack<T>::operator[](size_type index)
{
    return peek(index);
}

template <typename T>
bool operator==(const Stack<T>& first, const Stack<T>& second)
{
    if(first.size() != second.size())
    {
        return false;
    }
    for(size_t i = 0; i < first.size(); ++i)
    {
        if(first[i] != second[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const Stack<T>& lhv, const Stack<T>& rhv)
{
    return !(lhv == rhv);
}

template <typename T>
std::istream& operator>>(std::istream& in, Stack<T>& stack)
{
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