#ifndef __FORWARD_LIST_H
#define __FORWARD_LIST_H

#include <initializer_list>
#include <ostream>

template <typename T>
class Forward_list
{
    public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = value_type* const;

    public:
    Forward_list();
    Forward_list(size_type);
    Forward_list(size_type, const_reference);
    Forward_list(std::initializer_list<T>);
    Forward_list(const Forward_list<T>&);
    Forward_list(Forward_list<T>&&);

    const Forward_list<T>& operator=(const Forward_list<T>&);
    const Forward_list<T>& operator=(Forward_list<T>&&);

    ~Forward_list();

    public:
    void insert(size_type, const_reference);
    void push_back(const_reference);
    void pop_back();
    void push_front(const_reference);
    void pop_front();
    void remove(size_type);
    size_type length() const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    reference at(size_type);
    const_reference at(size_type) const;
    bool empty() const;
    void reverse();

    reference operator[](size_type);
    const_reference operator[](size_type) const;

    private:
    class Node
    {
        public:
        Node();
        Node(const value_type&);

        value_type value;
        Node* next;
    };


    private:
    Node* head;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Forward_list<T>& rhv);

template <typename T>
bool operator==(const Forward_list<T>&, const Forward_list<T>&);

#include "forward_list.hpp"

#endif