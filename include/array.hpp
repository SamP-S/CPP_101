#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
// internal
#include "i_indexed.hpp"

/*
    Data Structure: Statically Sized Array
*/

template<typename T, size_t SIZE>
class Array : public IIndexed<T> {
private: 
    T m_data[SIZE] = {};

public:
    // constructor
    Array() = default;

    // destructor
    ~Array() = default;

    // get fixed size of array
    size_t size() override {
        return SIZE;
    }

    // fill all elements with value
    void fill(T _value) override {
        for (size_t i = 0; i < SIZE; i++) {
            m_data[i] = _value;
        }
    }
    
    // set all values to default "0"
    void clear() override {
        this->fill(T());
    }
    
    // overload index operator
    T& operator[](size_t _index) override {
        if (_index >= SIZE) {
            throw std::out_of_range("Array: [] out of range");
        }
        return m_data[_index];
    }

    // convert array to string
    std::string toString() override {
        std::stringstream ss;
        ss << "{ " << m_data[0];
        for (size_t i = 1; i < SIZE; i++) {
            ss << ", " << m_data[i];
        }
        ss << " }";
        return ss.str();
    }
};
