#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
#include <cassert>
#include <iostream>
//internal
#include "common/global.hpp"
#include "sequence/i_sequence.hpp"

/*
	Data Structure: Linked List
*/
	
template<typename T>
class LinkedList : public ISequence<T> {
private: 
	
	struct LinkedNode {
		T data;
		LinkedNode* pNext;
	};

	LinkedNode* m_pFirst;
	size_t m_size;

public:
	// O(1): constructor
	LinkedList() {
		m_pFirst = nullptr;
		m_size = 0;
	} 
	
	// O(n): destructor
	~LinkedList() {
		this->clear();
	}

	// O(1): get used size of dynamic array
	size_t size() override {
		return m_size;
	}

	// O(1): get allocated memory size of dynamic array
	size_t allocated() override {
		return m_size * sizeof(LinkedNode) + sizeof(LinkedList);
	}

	// O(1): check if used dynamic array is empty
	bool empty() override {
		return m_size == 0;
	}

	// O(n): remove all elements from array
	void clear() override {
		while (m_pFirst != nullptr) {
			this->pop_front();
		}
	}

	// O(n): fill all elements with value
	void fill(T _value) override {
		// iterate through list, set value
		for (LinkedNode* pNode = m_pFirst; pNode != nullptr; pNode = pNode->pNext) {
			pNode->data = _value;
		}
	}
	
	// O(n): overload index operator
	T& operator[](size_t _index) override {
		if (_index >= m_size) {
			throw std::out_of_range("Cannot access element out of range");
		}
		LinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < _index; ++i) {
			pNode = pNode->pNext;
		}
		return pNode->data;
	}

	// O(1): push front
	void push_front(T _elem) override {
		LinkedNode* pTmp = m_pFirst;
		LinkedNode* pFront = new LinkedNode();
		pFront->data = _elem;
		pFront->pNext = pTmp;
		m_pFirst = pFront;
		m_size++;
	}

	// O(1): pop front
	T pop_front() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty list");
		}
		LinkedNode* pTmp = m_pFirst;
		T ret = m_pFirst->data;
		m_pFirst = m_pFirst->pNext;
		m_size--;
		delete pTmp;
		return ret;
	}

	// O(n): push back
	void push_back(T _elem) override {
		// create new node
		LinkedNode* pNew = new LinkedNode();
		pNew->data = _elem;
		pNew->pNext = nullptr;
		// add to first if empty
		if (m_pFirst == nullptr) {
			m_pFirst = pNew;
			m_size++;
			return;
		}
		// find end and add node
		LinkedNode* pNode = m_pFirst;
		while (pNode->pNext != nullptr) {
			pNode = pNode->pNext;
		}
		pNode->pNext = pNew;
		m_size++;
	}

	// O(n): pop back
	T pop_back() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty list");
		}
		// remove from first if size 1
		if (m_size == 1) {
			assert(m_pFirst->pNext == nullptr && "Size mismatch");
			T ret = m_pFirst->data;
			delete m_pFirst;
			m_pFirst = nullptr;
			m_size--;
			return ret;
		}
		// find and remove end node
		LinkedNode* pNodeBefore = m_pFirst;
		LinkedNode* pNodeEnd = m_pFirst->pNext;
		while (pNodeEnd->pNext != nullptr) {
			pNodeBefore = pNodeEnd;
			pNodeEnd = pNodeEnd->pNext;
		}
		T ret = pNodeEnd->data;
		pNodeBefore->pNext = nullptr;
		delete pNodeEnd;
		m_size--;
		return ret;
	}

	// O(n): insert element at index
	void insert(size_t _index, T _elem) override {
		// push front if index 0
		if (_index == 0) {
			this->push_front(_elem);
			return;
		}
		// push back if index >= size
		if (_index >= m_size) {
			this->push_back(_elem);
			return;
		}
		// find node at index
		LinkedNode* pNodeBefore = m_pFirst;
		LinkedNode* pNodeKey = m_pFirst->pNext;
		for (size_t i = 1; i < _index; ++i) {
			pNodeBefore = pNodeKey;
			pNodeKey = pNodeKey->pNext;
		}
		// insert
		LinkedNode* pNew = new LinkedNode();
		pNew->data = _elem;
		pNew->pNext = pNodeKey;
		pNodeBefore->pNext = pNew;
		m_size++;
	}

	// O(n): remove element at index
	T remove(size_t _index) override {
		// pop front if index 0
		if (_index == 0) {
			return this->pop_front();
		}
		// remove from end if index >= size
		if (_index >= m_size) {
			return this->pop_back();
		}
		// find node at index
		LinkedNode* pNodeBefore = m_pFirst;
		LinkedNode* pNodeKey = m_pFirst->pNext;
		for (size_t i = 1; i < _index; ++i) {
			pNodeBefore = pNodeKey;
			pNodeKey = pNodeKey->pNext;
		}
		T ret = pNodeKey->data;
		// remove
		pNodeBefore->pNext = pNodeKey->pNext;
		delete pNodeKey;
		m_size--;
		return ret;
	}

	// O(n): convert array to string
	std::string toString() override {
		std::stringstream ss;
		ss << "{ size=" << m_size << "; alloc=" << this->allocated() << "; ";
		LinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < m_size; ++i) {
			ss << pNode->data;
			if (pNode->pNext != nullptr) {
				ss << ", ";
			}
			pNode = pNode->pNext;
		}
		ss << " }";
		return ss.str();
	}
};
