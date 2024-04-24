#ifndef __CONSTRUCT_AT
#define __CONSTRUCT_AT

#include <new>

template <typename T, typename ... Args>
void construct_at(T* ptr,Args&& ... args)
{
    ::new ((void*)ptr) T(std::forward<Args>(args)...);
}

#endif