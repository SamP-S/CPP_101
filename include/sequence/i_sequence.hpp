#pragma once

// std lib
#include <cstring>
// internal
#include "common/i_data_structure.hpp"

/*
    Interface: Linear Indexed Sequentially Packed
*/

template<typename T>
class ISequence : public IDataStructure {
public:
    // constructor/destructor
    virtual ISequence() = default;
    virtual ~ISequence() = default;

    // fill all used elements with value
    virtual void fill(T _value) = 0;
    
	// access existing element
	virtual T& operator[](size_t _index) = 0;

	// front/end operations
	virtual void push_front(T _elem) = 0;
	virtual T pop_front() = 0;
	virtual void push_back(T _elem) = 0;
	virtual T pop_back() = 0;

	// insert/remove at arbitrary index
	virtual void insert(size_t _index, T _elem) = 0;
	virtual T remove(size_t _index) = 0;
};

