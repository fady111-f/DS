#include "Action.h"
class RequestAction : public Action
{
private:
    OrderType type;
	int timestep;
	double price;
	double size;
	double distance;
public:
    // Add a constructor matching the usage in Restaurant.cpp
    RequestAction(int ID, OrderType type, double s, double pr, double d)
        : Action(ID), type(type), size(s), price(pr), distance(d) {}

    void Act(Restaurant* res);
};
