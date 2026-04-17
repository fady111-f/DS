#pragma once
#include "Order.h"
#include "Restaurant.h"
class Action
{
protected:
	int OrderID;
public:
	Action(int ID)
	{
		OrderID = ID;
	}
	virtual void Act(Restaurant* res) = 0;
};
