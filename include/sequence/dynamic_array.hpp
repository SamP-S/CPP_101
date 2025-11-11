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
    Data Structure: Dynamically Sized Array
*/
	
template<typename T>
class DynamicArray : public ISequence<T> {
private: 
    T* m_pData;
    size_t m_allocated;
	size_t m_size;

	// O(n): resize data structure
	void resize(size_t _n) {
		size_t newSize = nearestBase2(_n);
		memresize<T>(&m_pData, m_allocated, newSize);
		m_allocated = newSize;
	}

public:
    // O(n): constructor, allow manual init alloc size
    DynamicArray() {
		m_allocated = nearestBase2(0);
		m_pData = memalloc<T>(m_allocated);
		m_size = 0; 
	}

    // O(1): destructor
    ~DynamicArray() {
		memfree<T>(m_pData);
	}

    // O(1): get used size of dynamic array
    size_t size() override {
        return m_size;
    }

	// O(1): get allocated memory size of dynamic array
	size_t allocated() override {
		return m_allocated * sizeof(T) + sizeof(DynamicArray);
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
    }

    // O(n): fill all elements with value
    void fill(T _value) override {
        for (size_t i = 0; i < m_size; i++) {
            m_pData[i] = _value;
        }
    }
    
    // O(1): overload index operator
    T& operator[](size_t _index) override {
        if (_index >= m_size) {
			throw std::out_of_range("Can't index outside of used range");
		}
        return m_pData[_index];
    }

	// O(n): push front
	void push_front(T _elem) override {
		this->insert(0, _elem);
	}

	// O(n): pop front
	T pop_front() override {
		if (m_size == 0) {
			throw std::out_of_range("Can't pop from dynamic array of size 0");
		}
		return this->remove(0);
	}

	// Amortized O(1): push back
	void push_back(T _elem) override {
		if (m_size >= m_allocated) {
			this->resize(m_allocated << 1);
		}
		m_pData[m_size] = _elem;
		m_size++;
	}

	// O(1): pop back
	T pop_back() override {
		if (m_size == 0) {
			throw std::out_of_range("Can't pop from dynamic array of size 0");
		}
		T ret = m_pData[m_size - 1];
		m_size--;
		return ret;
	}

	// O(n): insert element at index
	void insert(size_t _index, T _elem) override {
		// resize if necessary
		if (m_size >= m_allocated) {
			this->resize(m_allocated << 1);
		}
		// push if index at end
		if (_index >= m_size) {
			this->push_back(_elem);
			return;
		}
		// copy forward and insert
		size_t range = m_size - _index;
		T* pTmp = memalloc<T>(range);
		memcpy<T>(pTmp, m_pData + _index, range);
		memcpy<T>(m_pData + _index + 1, pTmp, range);
		memfree<T>(pTmp);
		m_pData[_index] = _elem;
		m_size++;
	}

	// O(n): remove element at index
	T remove(size_t _index) override {
		// throw error if out of range
		if (_index > m_size) {
			throw std::out_of_range("Can't remove an element out of used range");
		}
		// pop if index at end
		if (_index >= m_size) {
			return this->pop_back();
		}
		// copy backward and return
		T ret = m_pData[_index];
		size_t range = m_allocated - _index - 1;
		T* pTmp = memalloc<T>(range);
		memcpy<T>(pTmp, m_pData + _index + 1, range);
		memcpy<T>(m_pData + _index, pTmp, range);
		memfree<T>(pTmp);
		m_pData[m_allocated - 1] = T();
		m_size--;
		return ret;
	}

    // O(n): convert array to string
    std::string toString() override {
        std::stringstream ss;
      	ss << "{ size=" << m_size << "; alloc=" << this->allocated() << "; "; 
		if (m_size > 0) {
			ss << m_pData[0];
			for (size_t i = 1; i < m_size; i++) {
				ss << ", " << m_pData[i];
			}
		}
        ss << " }";
        return ss.str();
    }
};
