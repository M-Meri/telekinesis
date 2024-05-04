#ifndef __ALLOCATOR_HPP
#define __ALLOCATOR_HPP

#include "../StringHeaders/allocator.h"

char* allocator::allocate(size_type count)
{
    if(count <= N/2)
    {
        if(flag == 1)
        {
            ++flag;
            return storage;
        }
        else if(flag == 2)
        {
            ++flag;
            return storage + N/2;
        }
        else if(flag == 3)
        {
            return static_cast<char*>(::operator new(count));
        }
        else if(flag == 4)
        {
            flag = 3;
            return storage;
        }
        else if(flag == 5)
        {
            flag = 3;
            return storage + N/2;
        }
    }
    return static_cast<char*>(::operator new(count));
}

void allocator::deallocate(char* ptr, size_type)
{
    if(storage != ptr && storage +(N/2) != ptr)
    {
        ::operator delete(ptr); 
    }
    else if(ptr == storage){
        flag = 4;
    }
    else {
        flag = 5;
    }
}

void allocator::construct(char* ptr, char a)
{
    *ptr = a;
}

void allocator::destroy(char* ptr)
{}

allocator::size_type allocator::maxsize()
{
    return static_cast<size_type> (N) / 2;
}

#endif