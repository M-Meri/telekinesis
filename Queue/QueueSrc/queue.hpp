#ifndef _QUEUE_HPP
#define _QUEUE_HPP

#include <initializer_list>
#include <iostream>
#include <vector>
#include "../QueueHdr/queue.h"

template <typename T, typename Container>
Queue<T, Container>::Queue():queue()
{}

template <typename T, typename Container>
Queue<T, Container>::Queue(const std::initializer_list<value_type>& rhv):queue(rhv)
{}

template <typename T, typename Container>
Queue<T, Container>::Queue(const Queue& rhv):queue(rhv.queue)
{}

template <typename T, typename Container>
Queue<T, Container>::Queue(Queue&& rhv):queue(std::move(rhv.queue))
{}

template <typename T, typename Container>
Queue<T, Container>::~Queue()
{}

template <typename T, typename Container>
const Queue<T, Container>& Queue<T, Container>::operator=(Queue&& rhv)
{
    queue = std::move(rhv.queue);
    return *this;
}

template <typename T, typename Container>
const Queue<T, Container>& Queue<T, Container>::operator=(const Queue& rhv)
{
    queue = rhv.queue;
    return *this;
}

template <typename T, typename Container>
bool Queue<T, Container>::empty() const
{
    return queue.empty();
}

template <typename T, typename Container>
void Queue<T, Container>::clear()
{
    queue.clear();
}

template <typename T, typename Container>
void Queue<T, Container>::push(value_type val)
{
    queue.push_back(val);
}

template <typename T, typename Container>
void Queue<T, Container>::pop()
{
    queue.pop_back();
}

template <typename T, typename Container>
Queue<T, Container>::size_type Queue<T, Container>::size() const
{
    return queue.size();
}

template <typename T, typename Container>
Queue<T, Container>::reference Queue<T, Container>::front()
{
    return queue[0];
}

template <typename T, typename Container>
Queue<T, Container>::const_reference Queue<T, Container>::front() const
{
    return queue[0];
}

template <typename T, typename Container>
Queue<T, Container>::reference Queue<T, Container>::back()
{
    return queue[size() - 1];
}

template <typename T, typename Container>
Queue<T, Container>::const_reference Queue<T, Container>::back() const
{
    return queue[size() - 1];
}

template <typename T, typename Container>
Queue<T, Container>::const_reference Queue<T, Container>::at(size_type index) const
{
    if(index < size())
    {
        return queue[index];
    }
    throw;
}

template <typename T, typename Container>
Queue<T, Container>::reference Queue<T, Container>::operator[](size_type index)
{
    return queue[index];
}

template <typename T, typename Container>
Queue<T, Container>::const_reference Queue<T, Container>::operator[](size_type index) const
{
    return queue[index];
}

template <typename T, typename Container>
bool Queue<T, Container>::operator==(const Queue& rhv) const
{
    if(size() != rhv.size())
    {
        return false;
    }
    for(size_t i = 0; i < size(); ++i)
    {
        if(at(i) != rhv.at(i))
        {
            return false;
        }
    }
    return true;
}

template <typename T, typename Container>
bool Queue<T, Container>::operator!=(const Queue<T, Container>& rhv) const
{
    return !(*this == rhv);
}

template <typename T, typename Container>
bool Queue<T, Container>::operator>=(const Queue& other) const
{
    if(size() < other.size())
    {
        return false;
    }
    if(size() > other.size())
    {
        return true;
    }
    for(size_type i = 0; i < size(); ++i)
    {
        if(queue[i] <  other[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T, typename Container>
bool Queue<T, Container>::operator>(const Queue<T, Container>& other) const
{
    return (*this >= other) && (*this != other);
}

template <typename T, typename Container>
bool Queue<T, Container>::operator<=(const Queue& other) const
{
    return !(*this > other);
}

template <typename T, typename Container>
bool Queue<T, Container>::operator<(const Queue& other) const
{
    return !(*this >= other);
}

template <typename T, typename Container = std::vector<T>>
std::istream& operator>>(std::istream& in, Queue<T, Container>& q)
{
    q.clear();
    T newval;
    while(in >> newval)
    {
        q.push(newval);
        if(in.peek() == '\n')
        {
            break;
        }
    }
    return in;
}

template <typename T, typename Container = std::vector<T>>
std::ostream& operator<<(std::ostream& out, Queue<T, Container>& q)
{
    for(size_t i = 0; i < q.size(); ++i)
    {
        out << q[i] << ' ';
    }
    return out;
}

#endif