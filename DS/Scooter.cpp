#include "Scooter.h"

Scooter::Scooter(int id) {
    this->id = id;
}

int Scooter::GetID() const {
    return id;
}

std::ostream& operator<<(std::ostream& os, const Scooter* scooter) {
    if (scooter != nullptr) {
        os << scooter->GetID();
    }
    return os;
}