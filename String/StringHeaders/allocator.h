#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

const int N = 32;
char storage[N];
int flag = 1;
class allocator
{
    public: 
    using size_type = size_t;
    char* allocate(size_type);
    void deallocate(char* ptr, size_type a = 0);
    void construct(char* ptr, char);
    void destroy(char* ptr);

    size_type maxsize();

};

#include "../StringSrc/allocator.hpp"

#endif