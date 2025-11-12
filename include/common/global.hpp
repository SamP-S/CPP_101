#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
#include <iostream>
#include <cassert>

// template pair
template<typename S, typename T>
struct Pair {
	S first;
	T second;
};

// swap elements at index _a <---> _b, no bound checks
template<typename T>
void swap(T* _pArr, size_t _a, size_t _b) {
	T tmp = _pArr[_a];
	_pArr[_a] = _pArr[_b];
	_pArr[_b] = tmp;
}

// allocate memory
template<typename T>
T* memalloc(size_t _size) {
	return (T*)malloc(_size * sizeof(T));
}

template<typename T>
void memfree(T* _pData) {
	free((void*)_pData);
}

// resize memory at pointer keeping existing data in place and default new elements
template<typename T>
void memresize(T** _p, size_t _size, size_t _newSize) {
	assert(_newSize >= _size && "Must resize larger than existing");
    // allocate new memory and copy in place
	T* pNew = (T*)malloc(_newSize * sizeof(T));
    std::memcpy((void*)pNew, (void*)*_p, _size * sizeof(T));
    T* pTmp = *_p;
    *_p = pNew;
    memfree<T>(pTmp);
}

// copy memory from source to dest of size
template<typename T>
void memcpy(T* _pDest, T* _pSrc, size_t _size) {
	std::memcpy((void*)_pDest, (void*)_pSrc, _size * sizeof(T));
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

