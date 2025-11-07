#pragma once

#include <exception>
#include <cstring>
#include <sstream>

/*
    Interface: Indexed Data Structures
*/

template<typename T>
class IIndexed {
public:
    // constructor
    IIndexed() = default;

    // destructor
    ~IIndexed() = default;

    // get fixed size of array
    virtual size_t size() = 0;

    // fill all elements with value
    virtual void fill(T _value) = 0;
    
    // set all values to default "0"
    virtual void clear() = 0;

	// overload index operator
	virtual T& operator[](size_t _index) = 0;

    // convert to string for debug
    virtual std::string toString() = 0;
};
