#include "Scooter.h"

Scooter::Scooter(int id, int noOfDeliveries) {
    this->id = id;
    this->NoOfDeliveries = noOfDeliveries;
}

int Scooter::GetID() const {
    return id;
}

int Scooter::GetNoOfDeliveries() const
{
    return NoOfDeliveries;
}

void Scooter::setNoOfDeliveries(int noOfDeliv)
{
    NoOfDeliveries = noOfDeliv;
}

std::ostream& operator<<(std::ostream& os, const Scooter* scooter) {
    if (scooter != nullptr) {
        os << scooter->GetID();
    }
    return os;
}