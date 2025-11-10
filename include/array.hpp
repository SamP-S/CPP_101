#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
// internal
#include "common/i_data_structure.hpp"

/*
    Data Structure: Statically Sized Array
*/

template<typename T, size_t SIZE>
class Array : public IDataStructure {
private: 
    T m_data[SIZE] = {};

public:
    // constructor/destructor
    Array() = default;
    ~Array() = default;

    // get fixed size of array
    size_t size() override {
        return SIZE;
    }

	// get allocated memory size of array
	size_t allocated() override {
		return SIZE * sizeof(T);
	}

	// reset to 0s
    void clear() {
        for (size_t i = 0; i < SIZE; i++) {
			m_data[i] = T();
		}
    }

    // fill all elements with value
    void fill(T _value) {
        for (size_t i = 0; i < SIZE; i++) {
            m_data[i] = _value;
        }
    }
    
    // overload index operator
    T& operator[](size_t _index) {
        if (_index >= SIZE) {
            throw std::out_of_range("Array: [] out of range");
        }
        return m_data[_index];
    }

    // convert array to string
    std::string toString() override {
        std::stringstream ss;
        ss << "{ size=" << SIZE << "; "; 
		ss << m_data[0];
        for (size_t i = 1; i < SIZE; i++) {
            ss << ", " << m_data[i];
        }
        ss << " }";
        return ss.str();
    }
};
