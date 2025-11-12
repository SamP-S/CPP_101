#pragma once

// internal
#include "common/global.hpp"

// 5 4 3 12 3
// split 5 4 : 3 12 3
// sort 4 5	; split 3 : 12 3
// 			; sort 3; sort 3 12
// 			; merge 3 3 12
// merge 3 3 4 5 12

template<typename T>
void merge_sort_impl(T* _pArr, size_t _left, size_t _mid, size_t _right) {
	size_t leftSize = _mid - _left + 1;
	size_t rightSize = _right - _mid;

	// sort left sub array
	if (leftSize <= 1) {
		// skip
	} else if (leftSize == 2) {
		if (_pArr[_left] > _pArr[_mid]) {
			swap(_pArr, _left, _mid);
		}
	} else {
		size_t left = _left;
		size_t right = _mid;
		size_t mid = left + ((leftSize - 1) / 2);
		merge_sort_impl(_pArr, left, mid, right);
	}

	// sort right sub array
	if (rightSize <= 1) {
		// skip
	} else if (rightSize == 2) {
		if (_pArr[_mid+1] > _pArr[_right]) {
			swap(_pArr, _mid+1, _right);
		}
	} else {
		size_t left = _mid + 1;
		size_t right = _right;
		size_t mid = left + ((rightSize - 1) / 2);
		merge_sort_impl(_pArr, left, mid, right);
	}
	
	// merge
	size_t size = _right - _left + 1;
	size_t leftCursor = _left;
	size_t rightCursor = _mid + 1;
	T* tmp = memalloc<T>(size);
	for (size_t i = 0; i < size; i++) {
		if (rightCursor > _right) {
			tmp[i] = _pArr[leftCursor];
			leftCursor++;
		} else if (leftCursor > _mid) {
			tmp[i] = _pArr[rightCursor];
			rightCursor++;
		} else if (_pArr[leftCursor] <= _pArr[rightCursor]) {
			tmp[i] = _pArr[leftCursor];
			leftCursor++;
		} else {
			tmp[i] = _pArr[rightCursor];
			rightCursor++;
		}
	}
	memcpy<T>(_pArr + _left, tmp, size);
	memfree<T>(tmp);
}

template<typename T>
void merge_sort(T* _pArr, size_t _size) {
	// return if naturally sorted
	if (_size <= 1) {
		return;
	} else if (_size == 2) {
		// swap if pair if necessary
		if (_pArr[0] > _pArr[1]) {
			swap(_pArr, 0, 1);
		}
		return;
	}
	// apply merge sort w/ sub arrays
	size_t left = 0;
	size_t right = _size - 1;
	size_t mid = right / 2;
	merge_sort_impl(_pArr, left, mid, right);
}