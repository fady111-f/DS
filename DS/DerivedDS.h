#ifndef DERIVED_DS_H
#define DERIVED_DS_H

#include "LinkedQueue.h"
#include "PriQueue.h"
#include "Order.h"
#include "Table.h"

// Forward declaration of classes so the compiler knows they exist
class Order;
class Table;

// 1. Pend_OVC: Derived from Queue
// FCFS orders but require a CancelOrder function to remove them if a cancellation action arrives.
class Pend_OVC : public LinkedQueue<Order*> {
public:
    // Function to cancel an order by its ID
    bool CancelOrder(int orderID) {
        // Implementation Logic for later: 
        // 1. Dequeue elements one by one into a temporary queue.
        // 2. If the element's ID matches orderID, do NOT enqueue it in the temp queue (this removes it).
        // 3. Enqueue all elements from the temp queue back to this queue.
		LinkedQueue<Order*> tempQueue;
		Order* currentOrder = nullptr;
		bool found = false;
        while (dequeue(currentOrder)) {
            if (currentOrder->GetID() == orderID) {
                found = true; // Mark as found but do not enqueue back
            } else {
				tempQueue.enqueue(currentOrder); // Enqueue back to temp queue
            }
        }
        // Enqueue all elements from the temp queue back to this queue
        while (tempQueue.dequeue(currentOrder)) {
            enqueue(currentOrder);
        }
        return found;
    }
};

// 2. RDY_OV: Derived from Queue
// Orders waiting for service. Needs a function to search and remove a specific order.
class RDY_OV : public LinkedQueue<Order*> {
public:
    // Search and remove a specific order by ID
    bool SearchAndRemove(int orderID) {
        // Implementation Logic for later:
        // Traverse the queue to find the order by ID, remove it, and return it.
         // Placeholder for Phase 2
        LinkedQueue<Order*> tempQueue;
        Order* currentOrder = nullptr;
        bool found = false;
        while (dequeue(currentOrder)) {
            if (currentOrder->GetID() == orderID) {
                returnedOrder = currentOrder;
                found = true; // Mark as found but do not enqueue back
            }
            else {
                tempQueue.enqueue(currentOrder); // Enqueue back to temp queue
            }
        }
        // Enqueue all elements from the temp queue back to this queue
        while (tempQueue.dequeue(currentOrder)) {
            enqueue(currentOrder);
        }
        return found;
    }
    
};

// 3. Cook_Ords: Derived from Priority Queue
// Contains cooking orders (Highest priority finishes first). Needs cancellation.
class Cook_Ords : public PriQueue<Order*> {
public:
    // Function to cancel an order by its ID
    bool CancelOrder(int orderID) {
        // Implementation Logic for later:
        // Dequeue all items, filter out the cancelled ID, and enqueue the rest back.
        // Placeholder for Phase 2
        PriQueue<Order*> tempQueue;
        Order* currentOrder = nullptr;
        bool found = false;
        while (dequeue(currentOrder)) {
            if (currentOrder->GetID() == orderID) {
                found = true; // Mark as found but do not enqueue back
            }
            else {
                tempQueue.enqueue(currentOrder, currentOrder->GetPriority()); // Enqueue back to temp queue
            }
        }
        // Enqueue all elements from the temp queue back to this queue
        while (tempQueue.dequeue(currentOrder)) {
            enqueue(currentOrder, currentOrder->GetPriority());
        }
        return found;
    }
    
};

// 4. Fit_Tables: Derived from Priority Queue
// Tables are prioritized by least number of available seats (Best fit).
class Fit_Tables : public PriQueue<Table*> {
public:
    // Returns the best-fit table for a given order size
    bool getBest(int requiredSeats, Table*& bestTable) {
        // Implementation Logic for later:
        // The item at the head may not fit the current order.
        // Dequeue until you find a table with (available seats >= requiredSeats).
        // Enqueue the other tables back.
        // Placeholder for Phase 2
		PriQueue<Table*> tempQueue;
        Table* currenttable = nullptr;
        bool found = false;
        while (dequeue(currenttable))
        {
            if (currenttable->GetFreeSeats() >= requiredSeats)
            {
                bestTable = currenttable;
                found = true;
            }
            else
            {
                tempQueue.enqueue(currenttable, currenttable->GetFreeSeats());
            }
        }
        while (tempQueue.dequeue(currenttable)) {
            enqueue(currenttable, currenttable->GetFreeSeats());
        }
        return found;
    }
};

#endif // DERIVED_DS_H