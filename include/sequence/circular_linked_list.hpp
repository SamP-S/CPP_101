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
	Data Structure: Circular Linked List
*/
	
template<typename T>
class CircularLinkedList : public ISequence<T> {
private: 
	
	struct LinkedNode {
		T data;
		LinkedNode* pNext;
	};

	LinkedNode* m_pFirst;
	LinkedNode* m_pLast;
	size_t m_size;

public:
	// o(1): constructor
	CircularLinkedList() {
		m_pFirst = nullptr;
		m_pLast = nullptr;
		m_size = 0;
	} 
	
	// o(n): destructor
	~CircularLinkedList() {
		this->clear();
	}

	// o(1): get used size of dynamic array
	size_t size() override {
		return m_size;
	}

	// o(1): get allocated memory size of dynamic array
	size_t allocated() override {
		return m_size * sizeof(LinkedNode) + sizeof(CircularLinkedList);
	}

	// o(1): check if used dynamic array is empty
	bool empty() override {
		return m_size == 0;
	}

	// o(n): remove all elements from array
	void clear() override {
		while (!this->empty()) {
			this->pop_front();
		}
	}

	// o(n): fill all elements with value
	void fill(T _value) override {
		// iterate through list, set value
		if (m_pFirst == nullptr) {
			return;
		}
		LinkedNode* pNode = m_pFirst;
		do {
			pNode->data = _value;
			pNode = pNode->pNext;
		} while (pNode != m_pFirst);
	}
	
	// o(n): overload index operator
	T& operator[](size_t _index) override {
		if (_index >= m_size) {
			throw std::out_of_range("cannot access element out of range");
		}
		LinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < _index; ++i) {
			pNode = pNode->pNext;
		}
		return pNode->data;
	}

	// o(1): push front
	void push_front(T _elem) override {
		LinkedNode* pNew = new LinkedNode();
		pNew->data = _elem;
		if (this->empty()) {
			pNew->pNext = pNew; // point to itself
			m_pFirst = pNew;
			m_pLast = pNew;
		} else {
			pNew->pNext = m_pFirst;
			m_pFirst = pNew;
			m_pLast->pNext = m_pFirst; // update last node's next pointer
		}
		m_size++;
	}

	// o(1): pop front
	T pop_front() override {
		if (this->empty()) {
			throw std::out_of_range("cannot pop from empty list");
		}
		LinkedNode* pTmp = m_pFirst;
		T ret = m_pFirst->data;
		if (m_size == 1) {
			m_pFirst = nullptr;
			m_pLast = nullptr;
		} else {
			m_pFirst = m_pFirst->pNext;
			m_pLast->pNext = m_pFirst; // update last node's next pointer
		}
		m_size--;
		delete pTmp;
		return ret;
	}

	// o(1): push back
	void push_back(T _elem) override {
		LinkedNode* pNew = new LinkedNode();
		pNew->data = _elem;
		if (this->empty()) {
			pNew->pNext = pNew; // point to itself
			m_pFirst = pNew;
			m_pLast = pNew;
		} else {
			pNew->pNext = m_pFirst;
			m_pLast->pNext = pNew;
			m_pLast = pNew;
		}
		m_size++;
	}

	// o(n): pop back
	T pop_back() override {
		if (this->empty()) {
			throw std::out_of_range("cannot pop from empty list");
		}
		LinkedNode* pTmp = m_pLast;
		T ret = m_pLast->data;
		if (m_size == 1) {
			m_pFirst = nullptr;
			m_pLast = nullptr;
		} else {
			LinkedNode* pNode = m_pFirst;
			while (pNode->pNext != m_pLast) {
				pNode = pNode->pNext;
			}
			pNode->pNext = m_pFirst;
			m_pLast = pNode;
		}
		m_size--;
		delete pTmp;
		return ret;
	}

	// o(n): insert element at index
	void insert(size_t _index, T _elem) override {
		if (_index == 0) {
			this->push_front(_elem);
			return;
		}
		if (_index >= m_size) {
			this->push_back(_elem);
			return;
		}
		LinkedNode* pNode = m_pFirst;
		for (size_t i = 1; i < _index; ++i) {
			pNode = pNode->pNext;
		}
		LinkedNode* pNew = new LinkedNode();
		pNew->data = _elem;
		pNew->pNext = pNode->pNext;
		pNode->pNext = pNew;
		m_size++;
	}

	// o(n): remove element at index
	T remove(size_t _index) override {
		if (_index == 0) {
			return this->pop_front();
		}
		if (_index >= m_size - 1) {
			return this->pop_back();
		}
		LinkedNode* pNode = m_pFirst;
		for (size_t i = 1; i < _index; ++i) {
			pNode = pNode->pNext;
		}
		LinkedNode* pTmp = pNode->pNext;
		T ret = pTmp->data;
		pNode->pNext = pTmp->pNext;
		delete pTmp;
		m_size--;
		return ret;
	}

	// o(n): convert array to string
	std::string toString() override {
		std::stringstream ss;
		ss << "{ size=" << m_size << "; alloc=" << this->allocated() << "; ";
		if (!this->empty()) {
			LinkedNode* pNode = m_pFirst;
			do {
				ss << pNode->data;
				pNode = pNode->pNext;
				if (pNode != m_pFirst) {
					ss << ", ";
				}
			} while (pNode != m_pFirst);
		}
		ss << " }";
		return ss.str();
	}
};
