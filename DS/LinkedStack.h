#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "Node.h"
#include <iostream>

template <typename T>
class LinkedStack {
private:
    Node<T>* topPtr; // Pointer to the top of the stack
    int count;       // Added as requested in the project description

public:
    // Default constructor
    LinkedStack() {
        topPtr = nullptr;
        count = 0;
    }

    // Destructor to free memory
    ~LinkedStack() {
        T temp;
        while (pop(temp));
    }

    // Checks if the stack is empty
    bool isEmpty() const {
        return (topPtr == nullptr);
    }

    // Adds a new item to the top of the stack
    bool push(const T& newEntry) {
        Node<T>* newNodePtr = new Node<T>(newEntry);
        newNodePtr->setNext(topPtr);
        topPtr = newNodePtr;
        count++; // Increment count
        return true;
    }

    // Removes the top item from the stack
    bool pop(T& TopEntry) {
        if (isEmpty()) return false;

        Node<T>* nodeToDeletePtr = topPtr;
        TopEntry = topPtr->getItem();
        topPtr = topPtr->getNext();

        delete nodeToDeletePtr;
        count--; // Decrement count
        return true;
    }

    // Retrieves the top item without removing it
    bool peek(T& TopEntry) const {
        if (isEmpty()) return false;

        TopEntry = topPtr->getItem();
        return true;
    }

    // Returns the number of elements in the stack (O(1) complexity)
    int GetCount() const {
        return count;
    }

    // Prints all elements in the stack (from top to bottom)
    // Note: This requires overloading the << operator for the data type T
    void print() const {
        Node<T>* temp = topPtr;
        while (temp != nullptr) {
            std::cout << temp->getItem();
            temp = temp->getNext();
            if (temp != nullptr) {
                std::cout << ", ";
            }
        }
    }
};

#endif // LINKED_STACK_H