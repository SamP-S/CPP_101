// std lib
#include <iostream>
// internal
#include "i_indexed.hpp"
#include "array.hpp"
#include "list.hpp"
#include "queue.hpp"
#include "stack.hpp"


void testIndexed(std::string _name, IIndexed<int>* _indexed) {
    std::cout << "START TEST: " << _name << std::endl;
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    _indexed->fill(1);
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    _indexed->clear();
    std::cout << _name << " = " << _indexed->toString() << std::endl;
    for (int i = 0; i < 6; i++) {
		(*_indexed)[i] = i;
		std::cout << _name << " = " << _indexed->toString() << std::endl;
	}
   	std::cout << "END TEST: " << _name << std::endl << std::endl;
}

void testOrdered(std::string _name, IOrdered<int>* _ordered) {
	std::cout << "START TEST: " << _name << std::endl;
	std::cout << _name << " = " << _ordered->toString() << std::endl;
	for (int i = 0; i < 12; i++) {
		_ordered->push(i);
		std::cout << _name << " = " << _ordered->toString() << std::endl;
	}
	for (int i = 0; i < 5; i++) {
		_ordered->pop();
		std::cout << _name << " = " << _ordered->toString() << std::endl;
	}
	std::cout << "END TEST: " << _name << std::endl;
}

int main() {
	// // fixed sized array
	// Array<int, 8>* array = new Array<int, 8>();
    // testIndexed("array", array);
    // // dynamically sized array
	// List<int>* list = new List<int>(3);
	// testIndexed("list", list);
	
	// fifo queue
	Queue<int>* queue = new Queue<int>(4);
	testOrdered("queue", queue);
	// filo stack
    // Stack<int>* stack = new Stack<int>(4);
	// testOrdered("stack", stack);
}
