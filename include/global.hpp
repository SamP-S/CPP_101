#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
#include <iostream>

// resize memory at pointer keeping existing data in place and default new elements
template<typename T>
void memresize(T** _p, size_t _size, size_t _newSize) {
    // allocate new memory and copy
	T* pNew = (T*)malloc(_newSize * sizeof(T));
    std::memcpy((void*)pNew, (void*)*_p, _size * sizeof(T));
    T* pTmp = *_p;
    *_p = pNew;
    free(pTmp);
	// back fill new elements with default value
	std::memset((void*)(*_p + _size), T(), (_newSize - _size) * sizeof(T)); 
}

// round to next highest base 2
size_t nearestBase2(size_t _n) {	
	if (_n == 0) {
		_n = 1;
	} else {
		_n--;
		_n |= _n >> 1;
		_n |= _n >> 2;
		_n |= _n >> 4;
		_n |= _n >> 8;
		_n |= _n >> 16;
		_n |= _n >> 32;
	}
	_n++;
	return _n;
}

