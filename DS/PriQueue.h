#ifndef PRI_QUEUE_H
#define PRI_QUEUE_H

#include <iostream>

// Priority Node class to hold the item and its priority
template <typename T>
class PriNode {
private:
    T item;             // A data item
    int priority;       // Priority of the item
    PriNode<T>* next;   // Pointer to next node

public:
    PriNode(const T& r_Item, int pr) {
        item = r_Item;
        priority = pr;
        next = nullptr;
    }
    void setItem(const T& r_Item) { item = r_Item; }
    T getItem() const { return item; }

    void setNext(PriNode<T>* nextNodePtr) { next = nextNodePtr; }
    PriNode<T>* getNext() const { return next; }

    int getPriority() const { return priority; }
};

// Priority Queue Class
template <typename T>
class PriQueue {
private:
    PriNode<T>* head; // Pointer to the front of the queue
    int count;        // Added to keep track of the number of elements

public:
    // Default constructor
    PriQueue() {
        head = nullptr;
        count = 0;
    }

    // Destructor to free memory
    ~PriQueue() {
        T temp;
        while (dequeue(temp));
    }

    // Checks if the queue is empty
    bool isEmpty() const {
        return (head == nullptr);
    }

    // Adds a new item according to its priority (higher priority value = closer to front)
    bool enqueue(const T& newEntry, int pr) {
        PriNode<T>* newNodePtr = new PriNode<T>(newEntry, pr);

        // If queue is empty or the new item has higher priority than the head
        if (isEmpty() || pr > head->getPriority()) {
            newNodePtr->setNext(head);
            head = newNodePtr;
        }
        else {
            // Find the correct position to insert the new node
            PriNode<T>* temp = head;
            while (temp->getNext() != nullptr && temp->getNext()->getPriority() >= pr) {
                temp = temp->getNext();
            }
            newNodePtr->setNext(temp->getNext());
            temp->setNext(newNodePtr);
        }
        count++; // Increment count
        return true;
    }

    // Removes the front item from the queue (highest priority item)
    bool dequeue(T& frontEntry) {
        if (isEmpty()) return false;

        PriNode<T>* nodeToDeletePtr = head;
        frontEntry = head->getItem();
        head = head->getNext();

        delete nodeToDeletePtr;
        count--; // Decrement count
        return true;
    }

    // Retrieves the front item without removing it
    bool peek(T& frontEntry) const {
        if (isEmpty()) return false;

        frontEntry = head->getItem();
        return true;
    }

    // Returns the number of elements in the queue (O(1) complexity)
    int GetCount() const {
        return count;
    }

    // Prints all elements in the priority queue
    // Note: This requires overloading the << operator for the data type T
    void print() const {
        PriNode<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->getItem();
            temp = temp->getNext();
            if (temp != nullptr) {
                std::cout << ", ";
            }
        }
    }
};

#endif // PRI_QUEUE_H