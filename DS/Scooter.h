#ifndef SCOOTER_H
#define SCOOTER_H

#include <iostream>

class Scooter {
private:
    int id;
    int NoOfDeliveries;
    int distance;
public:
    Scooter(int id, int noOfDeliveries);
    int GetID() const;
    int GetNoOfDeliveries() const;
    void setNoOfDeliveries(int noOfDeliveries);
	int GetDistance() const;
	void AddDistance(int dist) { distance += dist; }
	void IncrementDeliveries() { NoOfDeliveries++; }
};

std::ostream& operator<<(std::ostream& os, const Scooter* scooter);

#endif // SCOOTER_H