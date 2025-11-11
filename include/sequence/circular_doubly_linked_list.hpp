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
	Data Structure: Circular Doubly Linked List
*/

template<typename T>
class CircularDoublyLinkedList : public ISequence<T> {
private: 
	
	struct DoublyLinkedNode {
		T data;
		DoublyLinkedNode* pNext;
		DoublyLinkedNode* pPrev;
	};

	DoublyLinkedNode* m_pFirst;
	DoublyLinkedNode* m_pLast;
	size_t m_size;

public:
	// O(1): constructor
	CircularDoublyLinkedList() {
		m_pFirst = nullptr;
		m_pLast = nullptr;
		m_size = 0;
	} 
	
	// O(n): destructor
	~CircularDoublyLinkedList() {
		this->clear();
	}

	// O(1): get used size of dynamic array
	size_t size() override {
		return m_size;
	}

	// O(1): get allocated memory size of dynamic array
	size_t allocated() override {
		return m_size * sizeof(DoublyLinkedNode) + sizeof(CircularDoublyLinkedList);
	}

	// O(1): check if used dynamic array is empty
	bool empty() override {
		return m_size == 0;
	}

	// O(n): remove all elements from array
	void clear() override {
		while (!this->empty()) {
			this->pop_front();
		}
	}

	// O(n): fill all elements with value
	void fill(T _value) override {
		DoublyLinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < m_size; i++) {
			pNode->data = _value;
			pNode = pNode->pNext;
		}
	}
	
	// O(n): overload index operator
	T& operator[](size_t _index) override {
		if (_index >= m_size) {
			throw std::out_of_range("Cannot access element out of range");
		}
		DoublyLinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < _index; i++) {
			pNode = pNode->pNext;
		}
		return pNode->data;
	}

	// O(1): push front
	void push_front(T _elem) override {
		DoublyLinkedNode* pFront = new DoublyLinkedNode();
		pFront->data = _elem;
		if (this->empty()) {
			pFront->pNext = pFront;
			pFront->pPrev = pFront;
			m_pFirst = pFront;
			m_pLast = pFront;
		} else {
			pFront->pNext = m_pFirst;
			pFront->pPrev = m_pLast;
			m_pFirst->pPrev = pFront;
			m_pLast->pNext = pFront;
			m_pFirst = pFront;
		}
		m_size++;
	}

	// O(1): pop front
	T pop_front() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty list");
		}
		DoublyLinkedNode* pTmp = m_pFirst;
		T ret = pTmp->data;
		if (m_size == 1) {
			m_pFirst = nullptr;
			m_pLast = nullptr;
		} else {
			m_pFirst = m_pFirst->pNext;
			m_pFirst->pPrev = m_pLast;
			m_pLast->pNext = m_pFirst;
		}
		m_size--;
		delete pTmp;
		return ret;
	}

	// O(1): push back
	void push_back(T _elem) override {
		if (this->empty()) {
			this->push_front(_elem);
			return;
		}
		DoublyLinkedNode* pBack = new DoublyLinkedNode();
		pBack->data = _elem;
		pBack->pNext = m_pFirst;
		pBack->pPrev = m_pLast;
		m_pLast->pNext = pBack;
		m_pFirst->pPrev = pBack;
		m_pLast = pBack;
		m_size++;
	}

	// O(1): pop back
	T pop_back() override {
		if (this->empty()) {
			throw std::out_of_range("Cannot pop from empty list");
		}
		if (m_size == 1) {
			return this->pop_front();
		}
		DoublyLinkedNode* pTmp = m_pLast;
		T ret = pTmp->data;
		m_pLast = m_pLast->pPrev;
		m_pLast->pNext = m_pFirst;
		m_pFirst->pPrev = m_pLast;
		m_size--;
		delete pTmp;
		return ret;
	}

	// O(n): insert element at index
	void insert(size_t _index, T _elem) override {
		if (_index >= m_size) {
			this->push_back(_elem);
			return;
		}
		if (_index == 0) {
			this->push_front(_elem);
			return;
		}
		DoublyLinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < _index; i++) {
			pNode = pNode->pNext;
		}
		DoublyLinkedNode* pNew = new DoublyLinkedNode();
		pNew->data = _elem;
		pNew->pNext = pNode;
		pNew->pPrev = pNode->pPrev;
		pNode->pPrev->pNext = pNew;
		pNode->pPrev = pNew;
		m_size++;
	}

	// O(n): remove element at index
	T remove(size_t _index) override {
		if (_index >= m_size) {
			return this->pop_back();
		}
		if (_index == 0) {
			return this->pop_front();
		}
		DoublyLinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < _index; i++) {
			pNode = pNode->pNext;
		}
		T ret = pNode->data;
		pNode->pPrev->pNext = pNode->pNext;
		pNode->pNext->pPrev = pNode->pPrev;
		delete pNode;
		m_size--;
		return ret;
	}

	// O(n): convert array to string
	std::string toString() override {
		std::stringstream ss;
		ss << "{ size=" << m_size << "; alloc=" << this->allocated() << "; ";
		DoublyLinkedNode* pNode = m_pFirst;
		for (size_t i = 0; i < m_size; i++) {
			ss << pNode->data;
			if (i < m_size - 1) {
				ss << ", ";
			}
			pNode = pNode->pNext;
		}
		ss << " }";
		return ss.str();
	}
};
