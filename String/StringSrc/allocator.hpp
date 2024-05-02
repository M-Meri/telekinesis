#ifndef __ALLOCATOR_HPP
#define __ALLOCATOR_HPP

#include "../StringHeaders/allocator.h"

char* allocator::allocate(size_type count)
{
    if(count <= 16)
    {
        int plus = flag * N/4;
        if(flag == 3)
        {
            flag = 0;
        } else {
            ++flag;
        }
        return storage + plus;
    }
    return static_cast<char*>(::operator new(count));
}

void allocator::deallocate(char* ptr, size_type)
{
    if(storage != ptr && storage +(N/4) != ptr && storage +(N/2) != ptr && storage + 3 * (N/4) != ptr)
    {
        ::operator delete(ptr); 
    }
}

void allocator::construct(char* ptr, char a)
{
    *ptr = a;
}

void allocator::destroy(char* ptr)
{
    std::destroy_at(ptr);
}

allocator::size_type allocator::maxsize()
{
    return static_cast<size_type> (N) / 4;
}

#endif