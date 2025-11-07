#pragma once

// std lib
#include <exception>
#include <cstring>
#include <sstream>
// internal
#include "global.hpp"
#include "i_ordered.hpp"

/*
    Data Structure: Queue
*/

template<typename T>
class Queue : public IOrdered<T> {
private:
    T* m_pData = nullptr;
    size_t m_front;
    size_t m_back;
    size_t m_numElems;
    size_t m_size;

public:
    // constructor, allow manual init size
    Queue(size_t _n = 4) {
        _n = nearestBase2(_n);
		// assign
        m_pData = (T*)malloc(_n * sizeof(T));
        m_size = _n;
        m_front = 0;
        m_back = m_size - 1;
        m_numElems = 0;
    }

    // destructor
    ~Queue() {
        free(m_pData);
    }

    // get number of elements in queue
    size_t size() override {
        return m_numElems;
    }

    // check if queue is empty
    bool empty() override {
        return m_numElems == 0;
    }

    // push element to back of queue
    void push(T _elem) override {
        if (m_numElems == m_size) {
            if (m_size == SIZE_MAX) {
                throw std::length_error("Queue: can't push elements beyond SIZE_MAX");
            } else {
                memresize<T>(&m_pData, m_size, m_size << 1);
                m_size = m_size << 1;
            }
        }
        m_back = (m_back + 1) % m_size;
        m_pData[m_back] = _elem;
        m_numElems++;
    }

    // pop element from front of list and return it
    T pop() override {
        if (m_numElems == 0) {
            throw std::range_error("Queue: no elements in queue");
        }
        size_t index = m_front;
        m_front = (m_front + 1) % m_size;
        m_numElems--;
        return m_pData[index];
    }

    // get a reference to front element
    T& front() override {
        if (m_numElems == 0) {
            throw std::range_error("Queue: no elements in queue");
        }
        return m_pData[m_front];
    }

    // get a reference to back element
    T& back() override {
        if (m_numElems == 0) {
            throw std::range_error("Queue: no elements in queue");
        }
        return m_pData[m_back];
    }

    std::string toString() override  {
        std::stringstream ss;
        ss << "{ size=" << m_size << "; ";
        for (size_t i = 0; i < m_numElems; i++) {
            size_t idx = (m_front + i) % m_size;
            ss << m_pData[idx];
            if (i != m_numElems - 1) {
                ss << ", ";
            }
        }
        ss << " }";
        return ss.str();
    }

};
