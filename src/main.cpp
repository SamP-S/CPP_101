// std lib
#include <iostream>
// internal
#include "array.hpp"
#include "queue.hpp"
#include "stack.hpp"

void testArray() {
    std::cout << "START TEST: ARRAY" << std::endl;
    Array<int, 3> array;
    std::cout << "array = " << array.toString() << std::endl;
    array.fill(1);
    std::cout << "array = " << array.toString() << std::endl;
    array.clear();
    std::cout << "array = " << array.toString() << std::endl;
    array[1] = 2;
    std::cout << "array = " << array.toString() << std::endl;
    array[2] = 3;
    std::cout << "array = " << array.toString() << std::endl;
    std::cout << "END TEST: ARRAY" << std::endl << std::endl;
}

void testQueue() {
    std::cout << "START TEST: QUEUE" << std::endl;
    Queue<int> queue(5);
    std::cout << "queue = " << queue.toString() << std::endl;
    for (int i = 0; i < 12; i++) {
        queue.push(i);
        std::cout << "queue = " << queue.toString() << std::endl;
    }
    for (int i = 0; i < 5; i++) {
        queue.pop();
        std::cout << "queue = " << queue.toString() << std::endl;
    }
    std::cout << "END TEST: QUEUE" << std::endl << std::endl;
}

void testStack() {
    std::cout << "START TEST: STACK" << std::endl;
    Stack<int> stack(5);
    std::cout << "stack = " << stack.toString() << std::endl;
    for (int i = 0; i < 12; i++) {
        stack.push(i);
        std::cout << "stack = " << stack.toString() << std::endl;
    }
    for (int i = 0; i < 5; i++) {
        stack.pop();
        std::cout << "stack = " << stack.toString() << std::endl;
    }
    std::cout << "END TEST: STACK" << std::endl << std::endl;
}

int main() {
    testArray();
    testQueue();
    testStack();
}
