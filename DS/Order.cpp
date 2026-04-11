#include "Order.h"

// Constructor implementation
Order::Order(int orderID, OrderType orderType) {
    id = orderID;
    type = orderType;
    RequestTime = 0;
    FinishTime = 0;

    // Initially, no resources are assigned
    assignedChef = nullptr;
    assignedTable = nullptr;
    assignedScooter = nullptr;
}

// Get order ID
int Order::GetID() const {
    return id;
}

// Get order type
OrderType Order::GetType() const {
    return type;
}

// Assign a chef to this order
void Order::AssignChef(Chef* c) {
    assignedChef = c;
}

// Assign a table to this order
void Order::AssignTable(Table* t) {
    assignedTable = t;
}

// Assign a scooter to this order
void Order::AssignScooter(Scooter* s) {
    assignedScooter = s;
}

// Destructor
Order::~Order() {
    // Resources are NOT deleted here because the order does not own them,
    // the Restaurant class owns the chefs, tables, and scooters.
}

// Overloading << operator to print the Order's ID
std::ostream& operator<<(std::ostream& os, const Order* order) {
    if (order != nullptr) {
        os << order->GetID(); // Printing just the ID as shown in the UI output sample
    }
    return os;
}