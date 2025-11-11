// std lib
#include <iostream>
// internal
#include "common/i_data_structure.hpp"
#include "array.hpp"
#include "sequence/i_sequence.hpp"
#include "sequence/dynamic_array.hpp"
#include "sequence/circular_dynamic_array.hpp"
#include "sequence/linked_list.hpp"
#include "sequence/circular_linked_list.hpp"
#include "sequence/doubly_linked_list.hpp"
#include "sequence/circular_doubly_linked_list.hpp"

#define TEST_ARRAY 			false
#define TEST_ARRAY_SIZE 	16
#define TEST_ARRAY_RANGE 	12

#define TEST_SEQUENCE	true
#define TEST_PUSHES 	7
#define TEST_POPS		3

void printDS(std::string _name, IDataStructure<int>* _ds) {
	std::cout << _name << " = " << _ds->toString() << std::endl;
}

void printSeq(std::string _name, ISequence<int>* _seq) {
	std::cout << _name << " = " << _seq->toString() << std::endl;
}

void testArray(std::string _name, Array<int, TEST_ARRAY_SIZE>* _array) {
	std::cout << "START TEST: " << _name << std::endl;
    std::cout << _name << " = " << _array->toString() << std::endl;
    _array->fill(1);
    std::cout << _name << " = " << _array->toString() << std::endl;
    _array->clear();
    std::cout << _name << " = " << _array->toString() << std::endl;
    for (int i = 0; i < TEST_ARRAY_RANGE; i++) {
		(*_array)[i] = TEST_ARRAY_RANGE - i - 1;
	}
	std::cout << _name << " = " << _array->toString() << std::endl;
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

void testSequence(std::string _name, ISequence<int>* _seq) {
    std::cout << "START TEST: " << _name << std::endl;
    printSeq("init", _seq);
    for (int i = 0; i < TEST_PUSHES; i++) {
		_seq->push_back(TEST_PUSHES - i - 1);
	}
	printSeq("push-back\t", _seq);
	for (int i = 0; i < TEST_POPS; i++) {
		_seq->pop_back();
	}
	printSeq("pop-back\t", _seq);
	_seq->push_front(99);
	printSeq("push-front\t", _seq);
	_seq->pop_front();
	printSeq("pop-front\t", _seq);
	_seq->insert(2, 999);
	printSeq("insert\t\t", _seq);
	_seq->remove(2);
	printSeq("remove\t\t", _seq);
	_seq->insert(_seq->size() + 4, 9999);
	printSeq("insert-end\t", _seq);
	_seq->remove(_seq->size());
	printSeq("remove-end\t", _seq);
	_seq->fill(1);
    printSeq("fill\t\t", _seq);
    _seq->clear();
    printSeq("clear\t\t", _seq);
	
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

int main() {
	// fixed sized array
	if (TEST_ARRAY) {
		Array<int, 16>* array = new Array<int, 16>();
		testArray("array", array);
	}

	// dynamically sized array
	if (TEST_SEQUENCE) {
		DynamicArray<int>* da = new DynamicArray<int>();
		testSequence("dynamic-array", da);
		CircularDynamicArray<int>* cda = new CircularDynamicArray<int>();
		LinkedList<int>* ll = new LinkedList<int>();
		testSequence("linked-list", ll);
		CircularLinkedList<int>* cll = new CircularLinkedList<int>();
		testSequence("circular-linked-list", cll);
		DoublyLinkedList<int>* dll = new DoublyLinkedList<int>();
		testSequence("doubly-linked-list", dll);
		CircularDoublyLinkedList<int>* cdll = new CircularDoublyLinkedList<int>();
		testSequence("circular-doubly-linked-list", cdll);
	}	

	// if (TEST_ORDERED) {
	// 	// fifo queue
	// 	Queue<int>* queue = new Queue<int>(4);
	// 	testDS("queue", queue);
	// 	// filo stack
	// 	Stack<int>* stack = new Stack<int>(4);
	// 	testDS("stack", stack);
	// }
}
