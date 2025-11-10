#pragma once

// std lib
#include <cstring>

/*
    Interface: Universal Data Structure Base
*/

template<typename T>
class IDataStructure {
public:
    // constructor/destructor
    virtual IDataStructure() = default;
    virtual ~IDataStructure() = default;

    // get number of elements in data structure
    virtual size_t size() = 0;

	// get allocated memory size of data structure
	virtual size_t allocated() = 0;

	// bool test if data structure contains any elements
	virtual bool empty() = 0;

    // remove all elements from data structure
    virtual void clear() = 0;

	/// TODO:
	// - iterators
	// - begin/end
	
    // convert to string
    virtual std::string toString() = 0;
};

