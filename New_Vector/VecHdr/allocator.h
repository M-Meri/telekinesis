#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

const int N = 100;


template <typename T>
class vectorAllocator
{
    public:
    using value_type = T;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using size_type = size_t;

    pointer allocate(size_type);

    void deallocate(void*, size_type count = 0);

    template <typename ... Args>
    void construct (pointer, Args... args);

    void destroy(pointer);

    size_type max_size();

    private:
    bool flag = false;
    char storage[N];
};

#include "allocator.hpp"

#endif