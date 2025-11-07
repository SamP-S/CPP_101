#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
// internal
#include "global.hpp"

/*
    Interface: Ordered Data Structure
*/

template<typename T>
class IOrdered {
public:
    // constructor
    IOrdered() = default;
    
	// destructor
    ~IOrdered() = default;

    // get number of elements in queue
    virtual size_t size() = 0;

    // check if queue is empty
    virtual bool empty() = 0;

    // push element to back of queue
    virtual void push(T _elem) = 0;
 
    // pop element from front of list and return it
    virtual T pop() = 0;

    // get a reference to front element
    virtual T& front() = 0;

    // get a reference to back element
    virtual T& back() = 0;

	// convert to string for debug
    virtual std::string toString() = 0;

};
