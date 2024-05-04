#ifndef __VECTOR_CPP__
#define __VECTOR_CPP__

#include <iostream>
#include <initializer_list>
#include "Vector.h"


//constructors
template <typename T, typename Allocator>
vector<T, Allocator>::vector(): arr(nullptr), size(0), cap(0) {}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type s):
    arr(allocator.allocate(s*2)), size(s), cap(s*2) {}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(size_type s, const_reference val):
    arr(allocator.allocate(s*2)), size(s), cap(s*2) 
{
    for (size_type i = 0; i < size; ++i)
    {
        allocator.construct(arr+i, val);
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(std::initializer_list<T> init) :
    arr(allocator.allocate(init.size()*2)), size(init.size()), cap(init.size() * 2)
{
    size_type i = 0;
    for (const_reference item :init)
    {
        allocator.construct(arr+(i++), item);
    }
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(const vector<value_type>& rhv): 
	arr{allocator.allocate(rhv.cap)}, size{rhv.size}, cap{rhv.cap}
{
	for (size_type i = 0; i < size; ++i)
	{
		allocator.construct(arr+i, rhv.arr[i]);
	}
}

template <typename T, typename Allocator>
vector<T, Allocator>::vector(vector<value_type>&& rhv) :
	arr{rhv.arr}, size{rhv.size}, cap{rhv.cap}
{
	rhv.arr = nullptr;
	rhv.size = 0;
	rhv.cap = 0;
}	

//destructor
template <typename T, typename Allocator>
vector<T, Allocator>::~vector()
{
    clear();
}

//assignments
template <typename T, typename Allocator>
const vector<T, Allocator>& vector<T, Allocator>::operator=(const vector<value_type>& rhv)
{
	if(this != &rhv)
	{
		clear();
		size = rhv.size;
		cap = rhv.cap;
		arr = allocator.allocate(cap);
		for(size_type i = 0; i < size; ++i)
		{
			allocator.construct(arr + i, rhv.arr[i]);
		}
	}
	return *this;
}

template <typename T, typename Allocator>
const vector<T, Allocator>& vector<T, Allocator>::operator=(vector<value_type>&& rhv)
{
	if(this != &rhv)
	{
		clear();
		size = rhv.size;
		cap = rhv.cap;
		arr = rhv.arr;
		rhv.arr = nullptr;
		rhv.cap = 0;
		rhv.size = 0;
	}
	return *this;
}

//member functions
template <typename T, typename Allocator>
void vector<T, Allocator>::reserve(size_type mul){
	if(size == cap){
		cap *= mul;
		pointer tmp = allocator.allocate(cap);
		for(size_type i = 0; i < size; i++){
			allocator.construct(tmp+i, arr[i]);
		}
		allocator.destroy(arr);
		allocator.deallocate(arr);
		arr = tmp;
	}
}

template <typename T, typename Allocator>
void vector<T, Allocator>::push_back(value_type val){
	reserve();
	arr[size] = val;
	++size;

}

template <typename T, typename Allocator>
void vector<T, Allocator>::pop_back(){
	if(size != 0){
		--size;
	}
}

template <typename T, typename Allocator>
void vector<T, Allocator>::resize(size_type s, value_type val){
	if(s > cap){
		size_type tmp = s/cap;	
    	reserve(tmp + 1);
	}
	while ( s > size){
		arr[size] = val;
		++size;
	}

	if(s < size){
    	size = s;
	}
}

template <typename T, typename Allocator>
T& vector<T, Allocator>::at(size_type index) { 
	if (index < size){ 
		return arr[index];
	}
	throw 1;
}

template <typename T, typename Allocator>
T& vector<T, Allocator>::front(){
	if(size > 0){
		return arr[0];
	}
	throw 1;
}

template <typename T, typename Allocator>
T& vector<T, Allocator>::back(){ 
	if(size > 0){
    	return arr[size - 1];
	}
	throw 1;
}

template <typename T, typename Allocator>
void vector<T, Allocator>::insert(size_type index, value_type val){
	if (index <= size){
		reserve();
		for (size_type i = size - 1; i >= index; --i){
			arr[i + 1] = arr[i];
		}
		arr[index] = val;
		++size;
	}
    else{
       throw 1;
    }
}

template <typename T, typename Allocator>
void vector<T, Allocator>::remove(size_type index){
	if (index < size){
		for (size_type i = index; i < size - 1; ++i){
			arr[i] = arr[i + 1];
		}
		--size;
	}
	else{ 
		throw 1;
	}
}

template <typename T, typename Allocator>
void vector<T, Allocator>::clear(){
	for(size_type i = 0; i < size; ++i)
	{
		allocator.destroy(arr);
	}
	allocator.deallocate(arr);
	arr = nullptr;
	cap = 0;
	size = 0;
}

template <typename T, typename Allocator>
bool vector<T, Allocator>::empty(){
	return size == 0;
}

template <typename T, typename Allocator>
size_t vector<T, Allocator>::getSize(){
	return size;
}

template <typename T, typename Allocator>
size_t vector<T, Allocator>::capacity(){
	return cap;
}

#endif