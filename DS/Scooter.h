#ifndef SCOOTER_H
#define SCOOTER_H

#include <iostream>

class Scooter {
private:
    int id;

public:
    Scooter(int id);
    int GetID() const;
};

std::ostream& operator<<(std::ostream& os, const Scooter* scooter);

#endif // SCOOTER_H