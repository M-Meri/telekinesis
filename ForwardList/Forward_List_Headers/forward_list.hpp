#ifndef __FORWARD_LIST_HPP
#define __FORWARD_LIST_HPP

#include <initializer_list>
#include <algorithm>
#include <ostream>
#include "forward_list.h"

//Node
template <typename T>
Forward_list<T>::Node::Node(): value(value_type()), next(nullptr){}

template <typename T>
Forward_list<T>::Node::Node(const value_type& val): value(val), next(nullptr){}

//Forward list

//constructors
template <typename T>
Forward_list<T>::Forward_list(): head(nullptr) {}

template <typename T>
Forward_list<T>::Forward_list(size_type n)
{
    if(n == 0){
        head = nullptr;
        return;
    }
    head = new Node();
    Node* tmp = head;
    while(n-1)
    {
        tmp->next = new Node();
        tmp = tmp->next;
        --n;
    }
    tmp->next = nullptr;
} 

template <typename T>
Forward_list<T>::Forward_list(size_type count, const_reference val)
{
    if(count == 0)
    {
        head = nullptr;
        return;
    }
    head = new Node();
    Node* tmp = head;
    while(count-1)
    {
        tmp->value = val;
        tmp->next = new Node();
        tmp = tmp->next;
        --count;
    }
    tmp->value = val;
    tmp->next = nullptr;
}

template <typename T>
Forward_list<T>::Forward_list(std::initializer_list<T> init)
{
    if(init.size() == 0)
    {
        head = nullptr;
        return;
    }

    head = new Node();
    Node* tmp = head;
    Node* prev = head;
    
    for(const_reference item: init)
    {
        if(tmp == head){
            tmp->value = item;
            tmp = tmp->next;
        } else {
            prev->next = new Node();
            tmp = prev->next;
            tmp->value = item;
            prev = prev->next;
        }
    }
}

template <typename T>
Forward_list<T>::Forward_list(const Forward_list<T>& rhv)
{
    if(rhv.head == nullptr)
    {
        head = nullptr;
        return;
    }

    head = new Node();
    Node* tmp = head;
    head->value = rhv.head->value;
    Node* rhvtmp = rhv.head->next;
    while(rhvtmp)
    {
        tmp->next = new Node();
        tmp = tmp->next;
        tmp->value = rhvtmp->value;
        rhvtmp = rhvtmp->next;
    }
}

template <typename T>
Forward_list<T>::Forward_list(Forward_list<T>&& rhv):head(rhv.head)
{
    rhv.head = nullptr;
}


//assignments
template <typename T>
const Forward_list<T>& Forward_list<T>::operator=(const Forward_list<T>& rhv)
{
    if(this == &rhv)
    {
        return *this;
    }
    if(rhv.head == nullptr)
    {
        head = nullptr;
        return *this;
    }

    head = new Node();
    Node* tmp = head;
    head->value = rhv.head->value;
    Node* rhvtmp = rhv.head->next;
    while(rhvtmp)
    {
        tmp->next = new Node();
        tmp = tmp->next;
        tmp->value = rhvtmp->value;
        rhvtmp = rhvtmp->next;
    }
    return *this;
}

template <typename T>
const Forward_list<T>& Forward_list<T>::operator=(Forward_list<T>&& rhv)
{
    if(this != &rhv)
    {
        head = rhv.head;
        rhv.head = nullptr;
    }
    return *this;
}

//destructor
template <typename T>
Forward_list<T>::~Forward_list()
{
    Node* tmp = head;
    while(tmp)
    {
        Node* current = tmp;
        tmp = tmp->next;
        delete current;
    }
}

template <typename T>
void Forward_list<T>::insert(size_type index, const_reference val)
{
    if(index > length()){
        throw 1;
    }
    if(index == 0){
        push_front(val);
        return;
    }
    Node* tmp = head;
    for(int i = 0; i < index - 1; ++i)
    {
        tmp = tmp->next;
    }
    Node* nextNode = tmp->next;
    Node* current = new Node(val);
    tmp->next = current;
    current->next = nextNode;
}

template <typename T>
void Forward_list<T>::push_back(const_reference val)
{
    if(empty())
    {
        head = new Node(val);
        return;
    }
    Node* tmp = head;
    for(int i = 0; i < length() - 1; ++i)
    {
        tmp = tmp->next;
    }
    tmp->next = new Node(val);
}

template <typename T>
void Forward_list<T>::pop_back()
{
    if(*this.length() == 0)
    {
        throw;
    }
    if(*this.length() == 1)
    {
        *head.destroy();
        head = nullptr;
        return;
    }
    Node* tmp = head;
    for(int i = 0; i < length() - 2; ++i)
    {
        tmp = tmp->next;
    }
    *(tmp->next).destroy();
    tmp->next = nullptr;
}

template <typename T>
void Forward_list<T>::push_front(const_reference val)
{
    Node* current = new Node(val);
    current->next = head;
    head = current;
}

template <typename T>
void Forward_list<T>::pop_front()
{
    if(empty())
    {
        throw;
    }
    Node* tmp = head->next;
    delete head;
    head = tmp;
}

template <typename T>
void Forward_list<T>::remove(size_type index)
{
    if(index >= length())
    {
        throw;
    }
    if(index == 0)
    {
        pop_front();
        return;
    }
    Node* tmp = head;
    for(int i = 0; i < index - 1; ++i)
    {
        tmp = tmp->next;
    }
    Node* nextNode = tmp->next->next;
    delete tmp->next;
    tmp->next = nextNode;
}

template <typename T>
Forward_list<T>::reference Forward_list<T>::front()
{
    if(length() == 0)
    {
        throw;
    }
    return head->value;
}

template <typename T>
Forward_list<T>::const_reference Forward_list<T>::front() const
{
    if(length() == 0)
    {
        throw;
    }
    return head->value;
}

template <typename T>
Forward_list<T>::reference Forward_list<T>::back()
{
    if((*this).length() == 0)
    {
        throw;
    }
    Node* tmp = head;
    for(int i = 0; i < length() - 1; ++i)
    {
        tmp = tmp->next;
    }
    return tmp->value;
}


template <typename T>
Forward_list<T>::const_reference Forward_list<T>::back() const
{
    if(length() == 0)
    {
        throw;
    }
    Node* tmp = head;
    for(int i = 0; i < length() - 1; ++i)
    {
        tmp = tmp->next;
    }
    return tmp->value;
}

template <typename T>
Forward_list<T>::reference Forward_list<T>::at(size_type index)
{
    if(index >= length())
    {
        throw;
    }
    Node* tmp = head;
    for(int i = 0; i < index; ++i)
    {
        tmp = tmp->next;
    }
    return tmp->value;
}

template <typename T>
Forward_list<T>::const_reference Forward_list<T>::at(size_type index) const
{
    if(index >= *this.length())
    {
        throw;
    }
    Node* tmp = head;
    for(int i = 0; i < index; ++i)
    {
        tmp = tmp->next;
    }
    return tmp->value;
}

template <typename T>
bool Forward_list<T>::empty() const
{
    return head == nullptr;
}

template <typename T>
Forward_list<T>::size_type Forward_list<T>::length() const
{
    size_type size = 0;
    Node* tmp = head;
   /* while (tmp != nullptr) {
        ++size;
        if (tmp->next != nullptr) {
            tmp = tmp->next;
        } else {
            break; // Reached the end of the list
        }
    } */  
    while(tmp != nullptr)
    {
        ++size;
        tmp = tmp->next;
    }
    return size;
}

template <typename T>
void Forward_list<T>::reverse()
{
    for(size_type i = 0; i < length()/2; ++i)
    {
        std::swap((*this)[i], (*this)[length() - 1 - i]);
    }
}

template <typename T>
Forward_list<T>::reference Forward_list<T>::operator[](size_type index)
{
    Node* tmp = head;
    for(size_type i = 0; i < index; ++i)
    {
        tmp = tmp->next;
    }
    return tmp->value;
}

template <typename T>
Forward_list<T>::const_reference Forward_list<T>::operator[](size_type index) const
{
    Node* tmp = head;
    for(size_type i = 0; i < index; ++i)
    {
        tmp = tmp->next;
    }
    return tmp->value;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Forward_list<T>& rhv)
{
    for(int i = 0; i < rhv.length(); ++i)
    {
        out << rhv[i] << ' ';
    }
    return out;
}

template <typename T>
bool operator==(const Forward_list<T>& lhv, const Forward_list<T>& rhv)
{
    if(lhv.length() != rhv.length())
    {
        return false;
    }
    for(int i = 0; i < rhv.length(); ++i)
    {
        if(lhv[i] != rhv[i])
        {
            return false;
        }
    }
    return true;
}

#endif