#ifndef __ALLOCATOR_HPP
#define __ALLOCATOR_HPP

#include "allocator.h"
#include "construct_at.hpp"

template <typename T>
vectorAllocator<T>::pointer vectorAllocator<T>::allocate(size_type count)
{
    if (count * sizeof(value_type) > N/2) 
    {
        return static_cast<pointer>(::operator new(count * sizeof(value_type)));
    } 
    if(!flag)
    {
        flag = !flag;
        return static_cast<pointer>(reinterpret_cast<void*>(storage));
    } 
    flag = !flag;
    return static_cast<pointer>(reinterpret_cast<void*>(storage + N/2));
}

template <typename T>
void vectorAllocator<T>::deallocate(void* ptr, size_type)
{
    if (ptr != reinterpret_cast<void*>(storage) && ptr !=reinterpret_cast<void*>(storage + N/2))
    {
        ::operator delete(ptr);
    }
}

template <typename T>
template <typename ... Args>
void vectorAllocator<T>::construct(pointer ptr, Args ... args)
{
    construct_at(ptr, std::forward<Args>(args)...);
}

template <typename T>
void vectorAllocator<T>::destroy(pointer ptr)
{
    std::destroy_at(ptr);
}

template <typename T>
vectorAllocator<T>::size_type vectorAllocator<T>::max_size()
{
    return static_cast<size_type>(N) / 2;
}

#endif