#include "Table.h"

Table::Table(int id, int cap) {
    this->id = id;
    this->capacity = cap;
    this->freeSeats = cap; // Initially, all seats are free
}

int Table::GetID() const { return id; }
int Table::GetCapacity() const { return capacity; }
int Table::GetFreeSeats() const { return freeSeats; }

void Table::setFreeSeats(int freeSeats)
{
    this->freeSeats = freeSeats;
}

int Table::getFreeSeats() const
{
    return freeSeats;
}

// Overloading << to format Table printing as requested: [ID, capacity, free seats]
std::ostream& operator<<(std::ostream& os, const Table* table) {
    if (table != nullptr) {
        os << "[T" << table->GetID() << ", " << table->GetCapacity() << ", " << table->GetFreeSeats() << "]";
    }
    return os;
}