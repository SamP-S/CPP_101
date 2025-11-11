#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
#include <cassert>
//internal
#include "common/global.hpp"
#include "sequence/i_sequence.hpp"

/*
	Data Structure: Circular Dynamically Sized Array
*/

template<typename T>
class CircularDynamicArray : public ISequence<T> {
private: 
	T* m_pData;
	size_t m_allocated;
	size_t m_size;
	size_t m_front;
	size_t m_back;

	// O(n): resize data structure
	void resize(size_t _n) {
		size_t newSize = nearestBase2(_n);
		T* newData = memalloc<T>(newSize);
		// copy elements in circular order to the new array
		for (size_t i = 0; i < m_size; i++) {
			newData[i] = m_pData[(m_front + i) % m_allocated];
		}
		memfree<T>(m_pData);
		m_pData = newData;
		m_allocated = newSize;
		m_front = 0;
		m_back = m_size - 1;
	}

public:
	// O(n): constructor, allow manual init alloc size
	CircularDynamicArray() {
		m_allocated = nearestBase2(0);
		m_pData = memalloc<T>(m_allocated);
		m_size = 0;
		m_front = 0;
		m_back = m_allocated - 1;
	}

	// O(1): destructor
	~CircularDynamicArray() {
		memfree<T>(m_pData);
	}

	// O(1): get used size of dynamic array
	size_t size() override {
		return m_size;
	}

	// O(1): get allocated memory size of dynamic array
	size_t allocated() override {
		return m_allocated * sizeof(T) + sizeof(CircularDynamicArray);
	}

	// O(1): check if used dynamic array is empty
	bool empty() override {
		return m_size == 0;
	}

	// O(1): remove all elements from array
	void clear() override {
		assert(m_pData != nullptr && "Can't clear unallocated memory");
		memfree<T>(m_pData);
		m_pData = memalloc<T>(m_allocated);
		m_size = 0;
		m_front = 0;
		m_back = m_allocated - 1;
	}

	// O(n): fill all elements with value
	void fill(T _value) override {
		for (size_t i = 0; i < m_size; i++) {
			m_pData[(m_front + i) % m_allocated] = _value;
		}
	}

	// O(1): overload index operator
	T& operator[](size_t _index) override {
		if (_index >= m_size) {
			throw std::out_of_range("Can't index outside of used range");
		}
		return m_pData[(m_front + _index) % m_allocated];
	}

	// O(1): push front
	void push_front(T _elem) override {
		if (m_size >= m_allocated) {
			this->resize(m_allocated << 1);
		}
		m_front = (m_front == 0) ? m_allocated - 1 : m_front - 1;
		m_pData[m_front] = _elem;
		m_size++;
	}

	// O(1): pop front
	T pop_front() override {
		if (m_size == 0) {
			throw std::out_of_range("Can't pop from dynamic array of size 0");
		}
		T ret = m_pData[m_front];
		m_front = (m_front + 1) % m_allocated;
		m_size--;
		return ret;
	}

	// Amortized O(1): push back
	void push_back(T _elem) override {
		if (m_size >= m_allocated) {
			this->resize(m_allocated << 1);
		}
		m_back = (m_back + 1) % m_allocated;
		m_pData[m_back] = _elem;
		m_size++;
	}

	// O(1): pop back
	T pop_back() override {
		if (m_size == 0) {
			throw std::out_of_range("Can't pop from dynamic array of size 0");
		}
		T ret = m_pData[m_back];
		m_back = (m_back == 0) ? m_allocated - 1 : m_back - 1;
		m_size--;
		return ret;
	}

	// O(n): insert element at index
	void insert(size_t _index, T _elem) override {
		if (_index > m_size) {
			throw std::out_of_range("Can't insert outside of used range");
		}
		if (m_size >= m_allocated) {
			this->resize(m_allocated << 1);
		}
		if (_index == 0) {
			this->push_front(_elem);
			return;
		}
		if (_index == m_size) {
			this->push_back(_elem);
			return;
		}

		size_t actualIndex = (m_front + _index) % m_allocated;
		size_t range = m_size - _index;
		T* pTmp = memalloc<T>(range);
		memcpy<T>(pTmp, m_pData + actualIndex, range);
		memcpy<T>(m_pData + actualIndex + 1, pTmp, range);
		memfree<T>(pTmp);
		m_pData[actualIndex] = _elem;
		m_size++;
	}

	// O(n): remove element at index
	T remove(size_t _index) override {
		if (_index >= m_size) {
			throw std::out_of_range("Can't remove an element out of used range");
		}
		size_t actualIndex = (m_front + _index) % m_allocated;
		T ret = m_pData[actualIndex];
		for (size_t i = _index; i < m_size - 1; i++) {
			size_t currentIndex = (m_front + i) % m_allocated;
			size_t nextIndex = (m_front + i + 1) % m_allocated;
			m_pData[currentIndex] = m_pData[nextIndex];
		}
		m_back = (m_back == 0) ? m_allocated - 1 : m_back - 1;
		m_size--;
		return ret;
	}

	// O(n): convert array to string
	std::string toString() override {
		std::stringstream ss;
		ss << "{ size=" << m_size << "; alloc=" << this->allocated() << "; ";
		if (m_size > 0) {
			ss << m_pData[m_front];
			for (size_t i = 1; i < m_size; i++) {
				ss << ", " << m_pData[(m_front + i) % m_allocated];
			}
		}
		ss << " }";
		return ss.str();
	}
};
