#ifndef ORDER_H
#define ORDER_H

#include <iostream>

// Enum to define the different types of orders easily
enum OrderType {
    TYPE_ODG, // General Dine-in
    TYPE_ODN, // Normal Dine-in
    TYPE_OT,  // Takeaway
    TYPE_OVN, // Normal Delivery
    TYPE_OVC  // VIP Delivery
};

// Forward declaration of resources
class Chef;
class Table;
class Scooter;

class Order {
private:
    int id;           // Order ID
    OrderType type;   // Type of the order

    // Timestamps (Will be fully used in Phase 2)
    int RequestTime;
    int FinishTime;

    // Assigned Resources (To avoid busy lists as requested in the DS sheet)
    Chef* assignedChef;
    Table* assignedTable;
    Scooter* assignedScooter;

public:
    // Constructor
    Order(int orderID, OrderType orderType);

    // Getters
    int GetID() const;
    OrderType GetType() const;

    // Setters for assigned resources
    void AssignChef(Chef* c);
    void AssignTable(Table* t);
    void AssignScooter(Scooter* s);

    // Destructor
    ~Order();
};

// Overloading the << operator to easily print the Order pointer in the UI
// The project description specifically asked to overload << for order*
std::ostream& operator<<(std::ostream& os, const Order* order);

#endif // ORDER_H