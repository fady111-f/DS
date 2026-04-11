#ifndef TABLE_H
#define TABLE_H

#include <iostream>

class Table {
private:
    int id;
    int capacity;
    int freeSeats;

public:
    Table(int id, int cap);
    int GetID() const;
    int GetCapacity() const;
    int GetFreeSeats() const;
};

std::ostream& operator<<(std::ostream& os, const Table* table);

#endif // TABLE_H