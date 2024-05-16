#ifndef __VECTOR_HPP_
#define __VECTOR_HPP_

#include <iostream>
#include <initializer_list>
#include <memory>
#include "../VecHdr/vector.h"

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector():
    size_{0}, capacity_{0}, arr_{nullptr}
{}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<value_type> init):
    size_{init.size()},
    capacity_{init.size()}, 
    arr_{alloc.allocate(init.size())}
{
    size_type i = 0;
    for(const_reference val : init)
    {
        alloc.construct(arr_ + i, val);
        ++i;
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_type s, const_reference val):
    size_{s}, 
    capacity_{s}, 
    arr_{alloc.allocate(s)}
{
    for(size_type i = 0; i < size_; ++i)
    {
        alloc.construct(arr_ + i, val);
    }
}

template <typename T, typename Allocator>
template <typename InputIt>
Vector<T, Allocator>::Vector(InputIt first, InputIt last):
    size_{last - first},
    capacity_{last - first}, 
    arr_{alloc.allocate(last - first)}
{
    for(size_type i = 0; first != last; ++first, ++i)
    {
        alloc.construct(arr_ + i, *first);
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& rhv):
    size_{rhv.size()}, 
    capacity_{rhv.size()}, 
    arr_{alloc.allocate(rhv.size())}
{
    for(size_type i = 0; i < size_; ++i)
    {
        alloc.construct(arr_ + i, rhv.arr_[i]);
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& rhv):
    size_{rhv.size_}, 
    capacity_{rhv.capacity_}, 
    arr_{rhv.arr_}
{
    rhv.size_ = 0;
    rhv.capacity_ = 0;
    rhv.arr_ = nullptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector()
{
    clear();
}

template <typename T, typename Allocator>
const Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& rhv)
{
    if(this != &rhv)
    {
        clear();
        size_ = rhv.size_;
        capacity_ = rhv.size_;
        arr_ = alloc.allocate(size_);
        for(size_type i = 0; i < size_; ++i)
        {
            alloc.construct(arr_ + i, rhv.arr_[i]);
        }
    }
    return *this;
}

template <typename T, typename Allocator>
const Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& rhv)
{
    if(this != &rhv)
    {
        clear();
        size_ = rhv.size_;
        capacity_ = rhv.capacity_;
        arr_ = rhv.arr_;
        rhv.arr_ = nullptr;
        rhv.size_ = 0;
        rhv.capacity_ = 0;
    }
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::allocator_type Vector<T, Allocator>::get_allocator()
{
    return alloc;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reference Vector<T, Allocator>::at(size_type index)
{
    if(index < size_)
    {
        return arr_[index];
    }
    throw;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reference Vector<T, Allocator>::at(size_type index) const
{
    if(index < size_)
    {
        return arr_[index];
    }
    throw;
}
template <typename T, typename Allocator>
Vector<T, Allocator>::reference Vector<T, Allocator>::operator[](size_type index)
{
    return arr_[index];
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reference Vector<T, Allocator>::operator[](size_type index) const
{
    return arr_[index];
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reference Vector<T, Allocator>::front()
{
    if(empty())
    {
        throw;
    }
    return arr_[0];
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reference Vector<T, Allocator>::front() const
{
    if(size_ == 0)
    {
        throw;
    }
    return arr_[0];
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reference Vector<T, Allocator>::back()
{
    if(size == 0)
    {
        throw;
    }
    return arr_[size_ - 1];
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reference Vector<T, Allocator>::back() const
{
    if(size_ == 0)
    {
        throw;
    }
    return arr_[size_ - 1];
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::begin()
{
    iterator it = {arr_};
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator Vector<T, Allocator>::begin() const
{
    const_iterator it = {arr_};
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cbegin() const
{
    return begin();
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::end()
{
    iterator it = {arr_ + size_};
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator Vector<T, Allocator>::end() const
{
    const_iterator it = {arr_ + size_};
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cend() const
{
    return end();
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rbegin() const
{
    const_reverse_iterator it = {arr_ + size_ - 1};
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rbegin()
{
    reverse_iterator it = {arr_ + size_ - 1};
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crbegin() const
{
    return rbegin();
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rend() const
{
    const_reverse_iterator it = {arr_ - 1};
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rend()
{
    reverse_iterator it = {arr_ - 1};
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crend() const
{
    return rend();
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const
{
    return capacity_ == 0;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::size_type Vector<T, Allocator>::size() const
{
    return size_;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::size_type Vector<T, Allocator>::capacity() const
{
    return capacity_;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::reserve(size_type new_cap)
{
    if(new_cap <= capacity_)
    {
        return;
    }
    value_type* tmp = alloc.allocate(new_cap);
    for(size_type i = 0; i < size_; ++i)
    {
        alloc.construct(tmp + i, arr_[i]);
    }
    size_type old_size = size_;
    clear();
    size_ = old_size;
    capacity_ = new_cap;
    arr_ = tmp;
    tmp = nullptr;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::clear() noexcept
{
    for(size_type i = 0; i < size_; ++i)
    {
        alloc.destroy(arr_ + i);
    }
    alloc.deallocate(arr_, capacity_);
    arr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, const_reference val)
{
    insert(pos, 1, val);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, size_type count, const_reference val)
{
    if(pos > end())
    {
        throw;
    }
    pointer p = pos.ptr;
    int cnt = p - arr_;
    reserve(size_ + count);
    p = arr_ + cnt;
    for(pointer tmp = arr_ + size_ + count - 1; tmp != p + count - 1; --tmp)
    {
        *tmp = *(tmp - count);
    }
    for(iterator it = p; it != p + count; ++it)
    {
        *it = val;
    }
    iterator it = p;
    size_ += count;
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> init)
{
    if(pos > end())
    {
        throw;
    }
    pointer p = pos.ptr;
    int cnt = p - arr_;
    reserve(size_ + init.size());
    p = arr_ + cnt;
    for(pointer tmp = arr_ + size_ + init.size() - 1; tmp != p + init.size() - 1; --tmp)
    {
        *tmp = *(tmp - init.size());
    }
    iterator it = p;
    for(const value_type& item : init)
    {
        *it = item;
        ++it;
    }
    size_ += init.size();

    return it;
}

template <typename T, typename Allocator>
template <typename InputIt>
Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last)
{
    if(pos > end())
    {
        throw;
    }
    size_type count = last - first;
    pointer p = pos.ptr;
    int cnt = p - arr_;
    reserve(size_ + count);
    p = arr_ + cnt;
    for(pointer tmp = arr_ + size_ + count - 1; tmp != p + count - 1; --tmp)
    {
        *tmp = *(tmp - count);
    }
    iterator it = p;
    for(; first != last; ++first, ++it)
    {
        *it = *first;
    }
    size_ += count;
    return it;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator pos)
{
    return erase(pos, pos + 1);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator first, const_iterator last)
{
    int len = last - first;
    iterator tmp = first.ptr;
    for(;tmp != last; ++tmp)
    {
        *tmp = *(tmp + len);
    }
    for(size_type i = size_ - 1; i > size_ - 1 - len; --i)
    {
        alloc.destroy(arr_ + i);
    }
    size_ -= len;
    tmp = first.ptr;
    return tmp;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(const_reference val)
{
	reserve(size_ + 1);
	arr_[size_++] = val;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::pop_back(){
	if(size_ == 0){
		throw;
	}
    alloc.destroy(arr_ + size_ - 1);
    --size_;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(size_type new_size, const_reference val){
	if(new_size == size_)
    {
        return;
    }
    while(new_size < size_)
    {
        pop_back();
    }
    while(new_size > size_)
    {
        push_back(val);
    }
}

template <typename T, typename Allocator>
int Vector<T, Allocator>::compare(const Vector& other) const
{
    if(size_ > other.size_)
    {
        return 1;
    }
    if(size_ < other.size_)
    {
        return -1;
    }
    for(size_type i = 0; i < size_; ++i)
    {
        if(arr_[i] > other.arr_[i])
        {
            return 1;
        } else if(arr_[i] < other.arr_[i])
        {
            return -1;
        }
    }
    return 0;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator==(const Vector& other) const
{
    return !(compare(other));
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator>(const Vector& other) const
{
    return (compare(other) == 1) ? true : false;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator>=(const Vector& other) const
{
    return (compare(other) != -1) ? true : false;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator<(const Vector& other) const
{
    return (compare(other) == -1) ? true : false;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator<=(const Vector& other) const
{
    return (compare(other) != 1) ? true : false;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator!=(const Vector& other) const
{
    return (compare(other) != 0) ? true : false;
}


template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator::const_iterator(pointer ptr)
 : ptr{ptr}
{}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator Vector<T, Allocator>::const_iterator::operator+(size_type cnt) const
{
    return const_iterator(ptr + cnt);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator Vector<T, Allocator>::const_iterator::operator-(size_type cnt) const
{
    return const_iterator(ptr - cnt);
}

template <typename T, typename Allocator>
int Vector<T, Allocator>::const_iterator::operator-(const const_iterator& other) const
{
    return ptr - other.ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator& Vector<T, Allocator>::const_iterator::operator++()
{
    ++ptr;
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator Vector<T, Allocator>::const_iterator::operator++(int)
{
    const_iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator& Vector<T, Allocator>::const_iterator::operator--()
{
    --ptr;
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator Vector<T, Allocator>::const_iterator::operator--(int)
{
    const_iterator tmp = *this;
    --*this;
    return tmp;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reference Vector<T, Allocator>::const_iterator::operator*() const
{
    return *ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_pointer Vector<T, Allocator>::const_iterator::operator->() const
{
    return ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reference Vector<T, Allocator>::const_iterator::operator[](size_type pos) const
{
    return ptr[pos];
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator==(const const_iterator& other) const
{
    return ptr == other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator!=(const const_iterator& other) const
{
    return ptr != other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator>(const const_iterator& other) const
{
    return ptr > other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator<(const const_iterator& other) const
{
    return ptr < other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator>=(const const_iterator& other) const
{
    return ptr >= other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator<=(const const_iterator& other) const
{
    return ptr <= other.ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator::iterator(pointer ptr)
{
    this->ptr = ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::iterator::operator+(size_type cnt) const
{
    return iterator(this->ptr + cnt);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::iterator::operator-(size_type cnt) const
{
    return iterator(this->ptr - cnt);
}

template <typename T, typename Allocator>
int Vector<T, Allocator>::iterator::operator-(const iterator& other) const
{
    return this->ptr - other.ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator& Vector<T, Allocator>::iterator::operator++()
{
    ++(this->ptr);
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::iterator::operator++(int)
{
    iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator& Vector<T, Allocator>::iterator::operator--()
{
    --(this->ptr);
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::iterator Vector<T, Allocator>::iterator::operator--(int)
{
    iterator tmp = *this;
    --*this;
    return tmp;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reference Vector<T, Allocator>::iterator::operator*()
{
    return *(this->ptr);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::pointer Vector<T, Allocator>::iterator::operator->()
{
    return this->ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reference Vector<T, Allocator>::iterator::operator[](size_type pos)
{
    return (this->ptr)[pos];
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator::const_reverse_iterator(pointer ptr)
    :ptr{ptr}
{}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::const_reverse_iterator::operator+(size_type cnt) const
{
    return const_reverse_iterator(ptr - cnt);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::const_reverse_iterator::operator-(size_type cnt) const
{
    return const_reverse_iterator(ptr + cnt);
}

template <typename T, typename Allocator>
int Vector<T, Allocator>::const_reverse_iterator::operator-(const const_reverse_iterator& other) const
{
    return ptr - other.ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator& Vector<T, Allocator>::const_reverse_iterator::operator++()
{
    --ptr;
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator& Vector<T, Allocator>::const_reverse_iterator::operator--()
{
    ++ptr;
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator tmp = *this;
    --*this;
    return tmp;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reference Vector<T, Allocator>::const_reverse_iterator::operator*() const
{
    return *ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_pointer Vector<T, Allocator>::const_reverse_iterator::operator->() const
{
    return ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::const_reference Vector<T, Allocator>::const_reverse_iterator::operator[](size_type pos) const
{
    return *(ptr - pos);
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator==(const const_reverse_iterator& other) const
{
    return ptr == other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const
{
    return ptr != other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator>(const const_reverse_iterator& other) const
{
    return ptr < other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator<(const const_reverse_iterator& other) const
{
    return ptr > other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator>=(const const_reverse_iterator& other) const
{
    return ptr <= other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator<=(const const_reverse_iterator& other) const
{
    return ptr >= other.ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator::reverse_iterator(pointer ptr)
{
    this->ptr = ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::reverse_iterator::operator+(size_type cnt) const
{
    return reverse_iterator(this->ptr - cnt);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::reverse_iterator::operator-(size_type cnt) const
{
    return reverse_iterator(this->ptr + cnt);
}

template <typename T, typename Allocator>
int Vector<T, Allocator>::reverse_iterator::operator-(const reverse_iterator& other) const
{
    return this->ptr - other.ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator& Vector<T, Allocator>::reverse_iterator::operator++()
{
    --(this->ptr);
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::reverse_iterator::operator++(int)
{
    reverse_iterator tmp = *this;
    ++*this;
    return tmp;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator& Vector<T, Allocator>::reverse_iterator::operator--()
{
    ++(this->ptr);
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::reverse_iterator::operator--(int)
{
    reverse_iterator tmp = *this;
    --*this;
    return tmp;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reference Vector<T, Allocator>::reverse_iterator::operator*()
{
    return *(this->ptr);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::pointer Vector<T, Allocator>::reverse_iterator::operator->()
{
    return this->ptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::reference Vector<T, Allocator>::reverse_iterator::operator[](size_type pos)
{
    return *(this->ptr - pos);
}

#endif