#ifndef _QUEUE_HPP
#define _QUEUE_HPP

#include <initializer_list>
#include <iostream>
#include <vector>
#include "queue.h"

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
template <typename InputIt>
Queue<T, Container>::Queue(InputIt first, InputIt last):queue(first, last)
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
    return queue.front();
}

template <typename T, typename Container>
Queue<T, Container>::const_reference Queue<T, Container>::front() const
{
    return queue.front();
}

template <typename T, typename Container>
Queue<T, Container>::reference Queue<T, Container>::back()
{
    return queue.back();
}

template <typename T, typename Container>
Queue<T, Container>::const_reference Queue<T, Container>::back() const
{
    return queue.back();
}

template <typename T, typename Container>
bool Queue<T, Container>::operator==(const Queue& rhv) const
{
   return queue == rhv.queue;
}

template <typename T, typename Container>
bool Queue<T, Container>::operator!=(const Queue<T, Container>& rhv) const
{
    return queue != rhv.queue;
}

template <typename T, typename Container>
bool Queue<T, Container>::operator>=(const Queue& other) const
{
   return queue >= other.queue;
}

template <typename T, typename Container>
bool Queue<T, Container>::operator>(const Queue<T, Container>& other) const
{
    return queue > other.queue;
}

template <typename T, typename Container>
bool Queue<T, Container>::operator<=(const Queue& other) const
{
    return queue <= other.queue;
}

template <typename T, typename Container>
bool Queue<T, Container>::operator<(const Queue& other) const
{
    return queue < other.queue;
}

#endif