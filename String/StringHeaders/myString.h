#ifndef __MYSTRING_H
#define __MYSTRING_H

#include <iostream>
#include "allocator.h"

template <typename Allocator = allocator>
class MyString
{
    public:
    using size_type = size_t;
    public:
    MyString(); 
    MyString(size_type); 
    MyString(const char*); 
    MyString(const MyString&);
    MyString(MyString&&);

    const MyString& operator=(const MyString&);
    const MyString& operator=(MyString&&);

    ~MyString();

    public:
    void append(char);
    void append(const MyString&);
    void append(const char*);
    void insert(size_type, char); 
    void insert(size_type, const char*); 
    void insert(size_type, const MyString&);
    void erase(size_type, size_type);
    void replace(const MyString&, const MyString&, size_type start = 0);
    void replace(const char*, const char*, size_type start = 0);
    void replaceAll(const MyString&, const MyString&);
    void replaceAll(const char*, const char*);
    void reverse();

    char& at(size_type) const;
    char& operator[](size_type) const;

    size_type length() const;
    bool empty() const;

    void clear();
    void resize(size_type);
    void swap(MyString&);

    int find(const MyString&, size_type start = 0) const;
    int find(char, size_type start = 0) const;
    int find(const char*, size_type start = 0) const;
    int rfind(const MyString&)const;
    int rfind(char)const;
    int rfind(const char*) const;

    const MyString& operator+=(const MyString&);
    const MyString& operator+=(const char*);
    const MyString& operator+=(char);
    const MyString& operator*=(size_t);
    bool operator>(const MyString<Allocator>&);
    bool operator<(const MyString<Allocator>&);
    bool operator>=(const MyString<Allocator>&);
    bool operator<=(const MyString<Allocator>&);

    operator const char*() const;

    private:
    void reserve(size_type count = 2);

    private:
    Allocator alloc;
    char* str;
    size_type size;
    size_type cap;
};

template <typename Allocator>
const MyString<Allocator>& operator+(const MyString<Allocator>&, const MyString<Allocator>&);
template <typename Allocator>
bool operator==(const MyString<Allocator>&, const MyString<Allocator>&);
template <typename Allocator>
bool operator!=(const MyString<Allocator>&, const MyString<Allocator>&);
template <typename Allocator>
const MyString<Allocator>& operator+(const MyString<Allocator>&, const char*);
template <typename Allocator>
const MyString<Allocator>& operator+(const MyString<Allocator>&, char);
template <typename Allocator>
const MyString<Allocator>& operator*(const MyString<Allocator>&, size_t);
template <typename Allocator>
std::ostream& operator<<(std::ostream&, const MyString<Allocator>&);

#include "../StringSrc/myString.hpp"

#endif