#include "Order.h"
#include "Restaurant.h"
class Action
{
protected:
	int OrderID;
	OrderType type;
	int timestep;
	Restaurant* res;
	double price;
	double size;
	double distance;
public:
	Action(int ID, OrderType type, int time, double pr, double s, double d)
	{
		OrderID = ID;
		this->type = type;
		timestep = time;
		price = pr;
		size = s;
		distance = d;
	}
	virtual void Act() = 0;
};
