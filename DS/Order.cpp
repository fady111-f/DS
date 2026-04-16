#include "Order.h"

// Constructor implementation
Order::Order(int orderID, OrderType orderType, double pr, double s, double d) {
    id = orderID;
    type = orderType;
    price = pr;
    size = s;
    distance = d;
    RequestTime = 0;
    FinishTime = 0;
	priority = pr * s * d; // Example priority calculation based on price, size, and distance
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
double Order::GetPrice() const {
    return price;
}
double Order::GetSize() const {
    return size;
}
double Order::GetDistance() const {
    return distance;
}
void Order::setPrice(double pr) {
    price = pr;
}
void Order::setSize(double s) {
    size = s;
}
void Order::setDistance(double d) {
    distance = d;
}
Chef* Order::AssignedChef() const {
    return assignedChef;
}
Table* Order::AssignedTable() const {
    return assignedTable;
}
Scooter* Order::AssignedScooter() const {
    return assignedScooter;
}
int Order::GetRequestTime() const {
    return RequestTime;
}
int Order::GetFinishTime() const {
    return FinishTime;
}
void Order::setRequestTime(int time) {
    RequestTime = time;
}
void Order::setFinishTime(int time) {
    FinishTime = time;
}
void Order::setAssignedChef(Chef* c) {
    assignedChef = c;
}
void Order::setAssignedTable(Table* t) {
    assignedTable = t;
}
void Order::setAssignedScooter(Scooter* s) {
    assignedScooter = s;
}

int Order::GetPriority() const
{
	return priority;
}
void Order::SetPriority(int p)
{
    priority = p;
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