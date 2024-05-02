#ifndef __MYSTING_HPP
#define __MYSTING_HPP

#include <iostream>
#include <cstring>
#include "../StringHeaders/myString.h"

template <typename Allocator>
MyString<Allocator>::MyString():str{nullptr}, size{0}, cap{0}
{}

template <typename Allocator>
MyString<Allocator>::MyString(size_type count)
    :str{alloc.allocate(count * 2)}, size(count), cap(count*2)
{}

template <typename Allocator>
MyString<Allocator>::MyString(const char* s)
    :str{alloc.allocate(strlen(s)*2)}, size{strlen(s)}, cap{strlen(s)*2}
{
    for(size_type i = 0; i < size; ++i)
    {
        alloc.construct(str + i, s[i]);
    }
}

template <typename Allocator>
MyString<Allocator>::MyString(const MyString& rhv)
    :str{alloc.allocate(rhv.size*2)}, size{rhv.size}, cap{rhv.size*2}
{
    for(size_type i = 0; i < size; ++i)
    {
        alloc.construct(str + i, rhv.str[i]);
    }
}

template <typename Allocator>
MyString<Allocator>::MyString(MyString&& rhv)
    :str{rhv.str}, size{rhv.size}, cap{rhv.cap}
{
    rhv.str = nullptr;
    rhv.size = 0;
    rhv.cap = 0;
}

template <typename Allocator>
const MyString<Allocator>& MyString<Allocator>::operator=(const MyString& rhv)
{
    if(this != &rhv)
    {
        clear();
        str = alloc.allocate(rhv.size);
        size = rhv.size;
        cap = size * 2;
        for(size_type i = 0; i < size; ++i)
        {
            alloc.construct(str + i, rhv[i]);
        }
    }
    return *this;
}

template <typename Allocator>
const MyString<Allocator>& MyString<Allocator>::operator=(MyString&& rhv)
{
    if(this != &rhv)
    {
        clear();
        str = rhv.str;
        rhv.str = nullptr;
        rhv.size = 0;
        rhv.cap = 0;
    }
    return *this;
}

template <typename Allocator>
MyString<Allocator>::~MyString()
{
    clear();
}

template <typename Allocator>
void MyString<Allocator>::clear()
{
    for(size_type i = 0; i < size; ++i)
    {
        alloc.destroy(str);
    }
    alloc.deallocate(str);
    size = 0;
    cap = 0;
}

template <typename Allocator>
typename MyString<Allocator>::size_type MyString<Allocator>::length() const
{
    return size;
}

template <typename Allocator>
bool MyString<Allocator>::empty() const
{
    return size == 0;
}

template <typename Allocator>
char& MyString<Allocator>::operator[](size_type index) const
{
    return str[index];
}

template <typename Allocator>
char& MyString<Allocator>::at(size_type index) const
{
    if(index < size)
    {
        return str[index];
    }
    throw;
}

template <typename Allocator>
MyString<Allocator>::operator const char*() const
{
    return str;
}

template <typename Allocator>
void MyString<Allocator>::reserve(size_type count)
{
    if(count != 1)
    {
        char* tmp = alloc.allocate(count * cap);
        for(size_type i = 0; i < size; ++i)
        {
            alloc.construct(tmp + i, str[i]);
            alloc.destroy(str + i);
        }
        alloc.deallocate(str);
        str = tmp;
        cap *= count;
        tmp = nullptr;
    }
}

template <typename Allocator>
void MyString<Allocator>::resize(size_type count)
{
    if(cap == 0)
    {
        str = alloc.allocate(count * 2);
        size = count;
        cap = count * 2;
        return;
    }
    if(count > size)
    {
        size_type n = count/cap + 1;
        reserve(n);
        size = count;
        return;
    }
    if(count < size)
    {
        for(size_type i = count; i < size; ++i)
        {
            alloc.destroy(str + i);
        }
        size = count;
    }
}

template <typename Allocator>
void MyString<Allocator>::append(char ch)
{
    if(size == cap)
    {
        if(empty())
        {
            str = alloc.allocate(2);
            size = 0;
            cap = 2;
        } else {
            reserve();
        }
    }
    alloc.construct(str + size, ch);
    ++size;
}

template <typename Allocator>
void MyString<Allocator>::append(const MyString& second)
{
    size_type tmp = size;
    resize(size + second.size);
    for(size_type i = 0; i < second.size; ++i)
    {
        alloc.construct(str + i + tmp, second[i]);
    }
}

template <typename Allocator>
void MyString<Allocator>::append(const char* second)
{
    size_type tmp = size;
    resize(size + strlen(second));
    for(size_type i = 0; i < strlen(second); ++i)
    {
        alloc.construct(str + tmp + i, second[i]);
    }
}

template <typename Allocator>
void MyString<Allocator>::insert(size_type index, char ch)
{
    if(index > size)
    {
        throw;
    }
    if(size == cap)
    {
        if(empty() && index == 0)
        {
            str = alloc.allocate(2);
            alloc.construct(str, ch);
            size = 1;
            cap = 2;
            return;
        }
        reserve();
    }
    if(index != size && size != 0)
    {
        alloc.construct(str + size, str[size - 1]);
        for (int i = size - 1; i > index; --i)
        {
            str[i] = str[i-1];
        }
        str[index] = ch;
    } else 
    {
        alloc.construct(str + size, ch);
    }
    ++size;
}

template <typename Allocator>
void MyString<Allocator>::insert(size_type index, const char* other)
{
    if(index > size)
    {
        throw;
    }
    if(index == size && size != 0)
    {
        append(other);
        return;
    }
    
    /*size_type tmp = size;
    resize(size + strlen(other));
    if(tmp = 0)
    {
        for(size_type i = 0; i < size; ++i)
        {
            alloc.construct(str + i, other[i]);
        }
        return;
    }
    int i;
    for(i = tmp - 1; i >= index && i + strlen(other) >= tmp; --i)
    {
        alloc.construct(str + i + strlen(other), str[i]);
    }
    if(i == index -1)
    {
        int j;
        for(j = strlen(other) - 1; j + index >= tmp; --j, --i)
        {
            alloc.construct(str + i + strlen(other), other[j]);
        }
        for(; j >= 0; --j, --i)
        {
            str[i + strlen(other)] = other[j];
        }
        return;
    }
    int left = tmp - strlen(other);
    for(int i = index + left - 1, j = 1; i >= index; --i, ++j)
    {
        str[tmp - j] = str[i];
    }
    for(int i = 0; i < strlen(other); ++i)
    {
        str[i+index] = other[i];
    }*/
    size_type othersize = strlen(other);
    if(empty())
    {
        str = alloc.allocate(othersize * 2);
        size = othersize;
        cap = othersize * 2;
        for(size_type i = 0; i < size; ++i)
        {
            alloc.construct(str + i, other[i]);
        }
        return;
    }
    size_type oldsize = size;
    append(other);
    size_type left = (oldsize - index) > othersize ? oldsize - index: othersize;
    for (size_type i = 0; i < left ; ++i)
    {
        str[size - 1 - i] = str[oldsize - 1 - i];
    }
    for (size_type i = index; i < othersize + index; ++i)
    {
        str[i] = other[i - index];
    }
}

template <typename Allocator>
void MyString<Allocator>::insert(size_type index, const MyString& other)
{
    if(index > size)
    {
        throw;
    }
    if(index == size && size != 0)
    {
        append(other);
        return;
    }
    if(empty())
    {
        str = alloc.allocate(other.size * 2);
        size = other.size;
        cap = other.size * 2;
        for(size_type i = 0; i < size; ++i)
        {
            alloc.construct(str + i, other[i]);
        }
        return;
    }
    size_type oldsize = size;
    append(other);
    size_type left = (oldsize - index) > other.size ? oldsize - index: other.size;
    for (size_type i = 0; i < left; ++i)
    {
        str[size - 1 - i] = str[oldsize - 1 - i];
    }
    for (size_type i = index; i < other.size + index; ++i)
    {
        str[i] = other.str[i - index];
    }
}

template <typename Allocator>
void MyString<Allocator>::erase(size_type first, size_type second)
{
    if(first >= size || second > size || second <= first)
    {
        if (first >= size){std::cout << 1 << std::endl;}
        if (second > size){std::cout << 2 << std::endl;}
        if (second <= first){std::cout << 3 << std::endl;}
        throw -1;
    }
    int len = second - first;
    for(int i = 0; i < size - len - first; ++i)
    {
        str[first + i] = str[second + i]; 
    }
    for(int i = 0; i < len; ++i)
    {
        alloc.destroy(str + size - i - 1);
    }
    size -= len;
}

template <typename Allocator>
int MyString<Allocator>::find(char ch, size_type start) const
{
    for(size_type i = start; i < size; ++i)
    {
        if(str[i] == ch){
            return i;
        }
    }
    return -1;
}

template <typename Allocator>
int MyString<Allocator>::find(const MyString& other, size_type start) const
{
    if(size - start < other.size || other.size == 0)
    {
        return -1;
    }
    for(size_type i = start; i < size; ++i)
    {
        if(i > size - other.size)
        {
            return -1;
        }
        if(str[i] == other[0])
        {
            size_type tmp = i;
            bool flag = true;
            for(size_type j = 1; j < other.size; ++j)
            {
                if(str[++tmp] != other[j]){
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                return i;
            }
        }
    }
    return -1;
}

template <typename Allocator>
int MyString<Allocator>::find(const char* other, size_type start) const
{
    if(size - start < strlen(other) || strlen(other) == 0)
    {
        return -1;
    }
    for(size_type i = start; i < size; ++i)
    {
        if(i > size - strlen(other))
        {
            return -1;
        }
        if(str[i] == other[0])
        {
            size_type tmp = i;
            bool flag = true;
            for(size_type j = 1; j < strlen(other); ++j)
            {
                if(str[++tmp] != other[j]){
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                return i;
            }
        }
    }
    return -1;
}

template <typename Allocator>
void MyString<Allocator>::replace(const MyString& first, const MyString& second, size_type start)
{
    int index = find(first, start);
    if (index == -1)
    {
        return;
    }
    erase(index, index + first.size);
    insert(index, second);
}

template <typename Allocator>
void MyString<Allocator>::replace(const char* first, const char* second, size_type start)
{
    int index = find(first, start);
    if (index == -1)
    {
        return;
    }
    erase(index, index + strlen(first));
    insert(index, second);
}

template <typename Allocator>
void MyString<Allocator>::replaceAll(const MyString& first, const MyString& second)
{
    if(second.size == 0)
    {
        return;
    }
    size_type index = 0;
    while(index < size)
    {
        int i = find(first, index);
        if(i == -1)
        {
            return;
        }
        erase(i, first.size + i);
        insert(i, second);
        index = i + second.size;
    } 
}

template <typename Allocator>
void MyString<Allocator>::replaceAll(const char* first, const char* second)
{
    size_type firstsize = strlen(first); 
    size_type secondsize = strlen(second); 
    if(secondsize == 0)
    {
        return;
    }
    size_type index = 0;
    while(index < size)
    {
        int i = find(first, index);
        if(i == -1)
        {
            return;
        }
        erase(i, firstsize + i); 
        insert(i, second); 
        index = i + secondsize;
    } 
}

template <typename Allocator>
void MyString<Allocator>::reverse()
{
    if(size == 0 || size == 1)
    {
        return;
    }
    char* tmp = alloc.allocate(cap);
    for(size_type i = 0; i < size; ++i)
    {
        tmp[i] = str[size - i - 1];
        alloc.destroy(str + size - 1 - i);
    }
    alloc.deallocate(str);
    str = tmp;
    tmp = nullptr;
}

template <typename Allocator>
void MyString<Allocator>::swap(MyString& other)
{
    char* tmpstr = str;
    size_type tmpcap = cap;
    size_type tmpsize = size;
    str = other.str;
    cap = other.cap;
    size = other.size;
    other.str = tmpstr;
    other.cap = tmpcap;
    other.size = tmpsize;
    tmpstr = nullptr;
}

template <typename Allocator>
int MyString<Allocator>::rfind(char ch) const
{
    for(size_type i = size - 1; i >= 0; --i)
    {
        if(str[i] == ch){
            return i;
        }
    }
    return -1;
}

template <typename Allocator>
int MyString<Allocator>::rfind(const MyString& other) const
{
    if(size < other.size || other.size == 0)
    {
        return -1;
    }
    for(size_type i = size - other.size; i >= 0; --i)
    {
        if(str[i] == other[0])
        {
            size_type tmp = i;
            bool flag = true;
            for(size_type j = 1; j < other.size; ++j)
            {
                if(str[++tmp] != other[j]){
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                return i;
            }
        }
    }
}

template <typename Allocator>
int MyString<Allocator>::rfind(const char* other) const
{
    size_type s = strlen(other);
    if(size < s || s == 0)
    {
        return -1;
    }
    for(size_type i = size - s; i >= 0; --i)
    {
        if(str[i] == other[0])
        {
            size_type tmp = i;
            bool flag = true;
            for(size_type j = 1; j < s; ++j)
            {
                if(str[++tmp] != other[j]){
                    flag = false;
                    break;
                }
            }
            if(flag)
            {
                return i;
            }
        }
    }
}

template <typename Allocator>
const MyString<Allocator>& MyString<Allocator>::operator+=(const MyString& other)
{
    append(other);
    return *this;
}

template <typename Allocator>
const MyString<Allocator>& MyString<Allocator>::operator+=(const char* other)
{
    append(other);
    return *this;
}

template <typename Allocator>
const MyString<Allocator>& MyString<Allocator>::operator+=(char ch)
{
    append(ch);
    return *this;
}

template <typename Allocator>
const MyString<Allocator>& MyString<Allocator>::operator*=(size_t count)
{
    MyString tmp = *this;
    for(size_t i = 0; i < count - 1; ++i)
    {
        append(tmp);
    }
    return *this;
}

template <typename Allocator>
const MyString<Allocator>& operator+(const MyString<Allocator>& first, const MyString<Allocator>& second)
{
    MyString<Allocator> tmp = first;
    tmp.append(second);
    return tmp;
}

template <typename Allocator>
bool operator==(const MyString<Allocator>& first, const MyString<Allocator>& second)
{
    if(first.length() != second.length())
    {
        return false;
    }
    for(int i = 0; i < first.length(); ++i)
    {
        if(first[i] != second[i])
        {
            return false;
        }
    }
    return true;
}

template <typename Allocator>
bool operator!=(const MyString<Allocator>& first, const MyString<Allocator>& second)
{
    return !(first == second);
}

template <typename Allocator>
bool MyString<Allocator>::operator>(const MyString<Allocator>& second)
{
    if(length() > second.length())
    {
        return true;
    }
    if(length() < second.length())
    {
        return false;
    }
    bool notequal = false;
    for(MyString<Allocator>::size_type i = 0; i <length(); ++i)
    {
        if(str[i] < second[i])
        {
            return false;
        }
        if(str[i] > second[i])
        {
            notequal = true;
        }
    }
    if(notequal)
    {
        return true;
    }
    return false;
}

template <typename Allocator>
bool MyString<Allocator>::operator<(const MyString<Allocator>& second)
{
    return (*this != second) && !(*this > second);
}

template <typename Allocator>
bool MyString<Allocator>::operator>=(const MyString<Allocator>& other)
{
    return !(*this < other);
}

template <typename Allocator>
bool MyString<Allocator>::operator<=(const MyString<Allocator>& other)
{
    return !(*this > other);
}

template <typename Allocator>
const MyString<Allocator>& operator+(const MyString<Allocator>& first, const char* second)
{
    MyString tmp = first;
    tmp.append(second);
    return tmp; 
}

template <typename Allocator>
const MyString<Allocator>& operator+(const MyString<Allocator>& first,char second)
{
    MyString tmp = first;
    tmp.append(second);
    return tmp; 
}

template <typename Allocator>
const MyString<Allocator>& operator*(const MyString<Allocator>& first, size_t count)
{
    MyString tmp  = first;
    tmp *= count;
    return tmp;
}

template <typename Allocator>
std::ostream& operator<<(std::ostream& out, const MyString<Allocator>& str)
{
    for(int i = 0; i < str.length(); ++i)
    {
        out << str[i];
    }
    return out;
}

#endif