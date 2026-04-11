#ifndef NODE_H
#define NODE_H

// Template class for the Node to handle any data type (e.g., Order*, Chef*)
template <typename T>
class Node {
private:
    T item;           // A data item
    Node<T>* next;    // Pointer to next node

public:
    // Default constructor
    Node() {
        next = nullptr;
    }

    // Constructor with an item
    Node(const T& newItem) {
        item = newItem;
        next = nullptr;
    }

    // Constructor with an item and a next pointer
    Node(const T& newItem, Node<T>* nextNodePtr) {
        item = newItem;
        next = nextNodePtr;
    }

    // Setters
    void setItem(const T& newItem) {
        item = newItem;
    }

    void setNext(Node<T>* nextNodePtr) {
        next = nextNodePtr;
    }

    // Getters
    T getItem() const {
        return item;
    }

    Node<T>* getNext() const {
        return next;
    }
};

#endif // NODE_H