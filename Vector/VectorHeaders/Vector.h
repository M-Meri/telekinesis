#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <initializer_list>
#include "allocator.h"

template <typename T, typename Allocator = vectorAllocator<T>>
class vector {
	public:
		using value_type = T;
		using size_type = size_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = pointer const;
		using allocator_type = Allocator;
	public:
		vector();
        vector(size_type);
        vector(size_type, const_reference val);
        vector(std::initializer_list<value_type> init);
		vector(const vector<value_type>&);
		vector(vector<value_type>&&);
        ~vector();

		const vector& operator=(const vector<value_type>&);
		const vector& operator=(vector<value_type>&&);
	private:
		void reserve(size_type mul = 2);
	public:
		void push_back(value_type val);
		void pop_back();
		void resize(size_type s, value_type val = value_type());
    public:
		reference at(size_type index);
		reference front();
		reference back();
    public:
		void insert(size_type index, value_type val);
		void remove(size_type index);
        void clear();

    	bool empty();
	
    public:
    	size_type getSize();
		size_type capacity();

    private:
		allocator_type allocator; 

		value_type* arr;
		size_type size;
		size_type cap;
};
#include "Vector.hpp"
#endif