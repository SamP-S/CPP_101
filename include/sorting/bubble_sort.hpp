#pragma once

// internal
#include "common/global.hpp"

// O(n^2) bubble sort, no optimisations
template<typename T>
void bubble_sort(T* _pArr, size_t _size) {
	for (size_t i = 0; i < _size; i++) {
		for (size_t j = 0; j < _size - 1; j++) {
			if (_pArr[j] > _pArr[j+1]) {
				swap(_pArr, j, j+1);
			}
		}
	}
}

// O(n^2) bubble sort, optimised (closing check area, swap check)
template<typename T>
void bubble_sort_fast(T* _pArr, size_t _size) {
	for (size_t i = 0; i < _size - 1; i++) {
		bool noSwap = true;
		// closing swap window
		for (size_t j = 0; j < _size - i - 1; j++) {
			if (_pArr[j] > _pArr[j+1]) {
				swap(_pArr, j, j+1);
				noSwap = false;
			}
		}
		// early exit if sorted
		if (noSwap) {
			return;
		}
	}
}
