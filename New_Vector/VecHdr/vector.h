#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <iostream>
#include <memory>
#include "allocator.h"

template <typename T, typename Allocator = vectorAllocator<T>>
class Vector
{
    public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;    
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    public:
    class const_iterator;
    class iterator;
    class const_reverse_iterator;
    class reverse_iterator;

    public:

    Vector();
    Vector(std::initializer_list<value_type>);
    Vector(size_type, const_reference val = value_type{});
    template <typename InputIt>
    Vector(InputIt, InputIt);
    Vector(const Vector&);
    Vector(Vector&&);
    ~Vector();

    public:

    const Vector& operator=(const Vector&);
    const Vector& operator=(Vector&&);

    allocator_type get_allocator();

    public:
    reference at(size_type);
    const_reference at(size_type) const;

    reference operator[](size_type);
    const_reference operator[](size_type) const;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    public:
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;

    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    public:
    bool empty() const;
    size_type size() const;
    size_type capacity() const;

    void reserve(size_type);

    public:
    void clear() noexcept;

    iterator insert(const_iterator, const_reference);
    iterator insert(const_iterator, size_type, const_reference);
    iterator insert(const_iterator, std::initializer_list<value_type>);
    template <typename InputIt>
    iterator insert(const_iterator, InputIt, InputIt);

    iterator erase(const_iterator);
    iterator erase(const_iterator, const_iterator);

    void push_back(const_reference);
    void pop_back();

    void resize(size_type, const_reference val = value_type{});

    public:
    bool operator==(const Vector&) const;
    bool operator!=(const Vector&) const;
    bool operator<(const Vector&) const;
    bool operator<=(const Vector&) const;
    bool operator>(const Vector&) const;
    bool operator>=(const Vector&) const;

    private:
    int compare(const Vector&) const;

    private:
    allocator_type alloc;
    size_type size_;
    size_type capacity_;
    pointer arr_;
};

template <typename T, typename Allocator>
class Vector<T, Allocator>::const_iterator
{
    friend class Vector<T, Allocator>;
    protected:
    pointer ptr;
    private:
    const_iterator(pointer);
    public:
    const_iterator() = default;
    const_iterator(const const_iterator&) = default;      
    const_iterator(const_iterator&&) = default;

    const_iterator& operator=(const const_iterator&) = default;      
    const_iterator& operator=(const_iterator&&) = default;

    const_iterator operator+(size_type) const;      
    const_iterator operator-(size_type) const;
    int operator-(const const_iterator&) const;

    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);

    const_reference operator*() const;
    const_pointer operator->() const;

    const_reference operator[](size_type) const;

    bool operator==(const const_iterator&) const;      
    bool operator!=(const const_iterator&) const;      
    bool operator<(const const_iterator&) const;      
    bool operator<=(const const_iterator&) const;      
    bool operator>(const const_iterator&) const;      
    bool operator>=(const const_iterator&) const;      
};

template <typename T, typename Allocator>
class Vector<T, Allocator>::iterator : public Vector<T, Allocator>::const_iterator
{
    friend class Vector<T, Allocator>;
    private:
    iterator(pointer);
    public:
    iterator() = default;
    iterator(const iterator&) = default;      
    //iterator(iterator&&) = default;

    iterator& operator=(const iterator&) = default;      
    iterator& operator=(iterator&&) = default;

    iterator operator+(size_type) const;      
    iterator operator-(size_type) const;
    int operator-(const iterator&) const;

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);

    reference operator*();
    pointer operator->();

    reference operator[](size_type);
};


template <typename T, typename Allocator>
class Vector<T, Allocator>::const_reverse_iterator
{
    friend class Vector<T, Allocator>;
    protected:
    pointer ptr;
    private:
    const_reverse_iterator(pointer);
    public:
    const_reverse_iterator() = default;
    const_reverse_iterator(const const_reverse_iterator&) = default;      
    const_reverse_iterator(const_reverse_iterator&&) = default;

    const_reverse_iterator& operator=(const const_reverse_iterator&) = default;      
    const_reverse_iterator& operator=(const_reverse_iterator&&) = default;

    const_reverse_iterator operator+(size_type) const;      
    const_reverse_iterator operator-(size_type) const;
    int operator-(const const_reverse_iterator&) const;

    const_reverse_iterator& operator++();
    const_reverse_iterator operator++(int);
    const_reverse_iterator& operator--();
    const_reverse_iterator operator--(int);

    const_reference operator*() const;
    const_pointer operator->() const;

    const_reference operator[](size_type) const;

    bool operator==(const const_reverse_iterator&) const;      
    bool operator!=(const const_reverse_iterator&) const;      
    bool operator<(const const_reverse_iterator&) const;      
    bool operator<=(const const_reverse_iterator&) const;      
    bool operator>(const const_reverse_iterator&) const;      
    bool operator>=(const const_reverse_iterator&) const;      
};

template <typename T, typename Allocator>
class Vector<T, Allocator>::reverse_iterator : public Vector<T, Allocator>::const_reverse_iterator
{
    friend class Vector<T, Allocator>;
    private:
    reverse_iterator(pointer);
    public:
    reverse_iterator() = default;
    reverse_iterator(const reverse_iterator&) = default;      
    reverse_iterator(reverse_iterator&&) = default;

    reverse_iterator& operator=(const reverse_iterator&) = default;      
    reverse_iterator& operator=(reverse_iterator&&) = default;

    reverse_iterator operator+(size_type) const;      
    reverse_iterator operator-(size_type) const;
    int operator-(const reverse_iterator&) const;

    reverse_iterator& operator++();
    reverse_iterator operator++(int);
    reverse_iterator& operator--();
    reverse_iterator operator--(int);

    reference operator*();
    pointer operator->();

    reference operator[](size_type);
};

#include <vector.hpp>

#endif