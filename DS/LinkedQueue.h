#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "Node.h"
#include <iostream>

template <typename T>
class LinkedQueue {
private:
    Node<T>* frontPtr;
    Node<T>* backPtr;
    int count; // Added as requested in the project description

public:
    // Default constructor
    LinkedQueue() {
        frontPtr = nullptr;
        backPtr = nullptr;
        count = 0;
    }

    // Destructor to free memory
    ~LinkedQueue() {
        T temp;
        while (dequeue(temp));
    }

    // Checks if the queue is empty
    bool isEmpty() const {
        return (frontPtr == nullptr);
    }

    // Adds a new item to the back of the queue
    bool enqueue(const T& newEntry) {
        Node<T>* newNodePtr = new Node<T>(newEntry);
        if (isEmpty()) {
            frontPtr = newNodePtr;
        }
        else {
            backPtr->setNext(newNodePtr);
        }
        backPtr = newNodePtr;
        count++; // Increment count
        return true;
    }

    // Removes the front item from the queue
    bool dequeue(T& frontEntry) {
        if (isEmpty()) return false;

        Node<T>* nodeToDeletePtr = frontPtr;
        frontEntry = frontPtr->getItem();
        frontPtr = frontPtr->getNext();

        // If the queue becomes empty
        if (nodeToDeletePtr == backPtr) {
            backPtr = nullptr;
        }

        delete nodeToDeletePtr;
        count--; // Decrement count
        return true;
    }

    // Retrieves the front item without removing it
    bool peek(T& frontEntry) const {
        if (isEmpty()) return false;

        frontEntry = frontPtr->getItem();
        return true;
    }

    // Returns the number of elements in the queue (O(1) complexity)
    int GetCount() const {
        return count;
    }

    // Prints all elements in the queue
    // Note: This requires overloading the << operator for the data type T
    void print() const {
        Node<T>* temp = frontPtr;
        while (temp != nullptr) {
            std::cout << temp->getItem();
            temp = temp->getNext();
            if (temp != nullptr) {
                std::cout << ", ";
            }
        }
    }
};

#endif // LINKED_QUEUE_H
