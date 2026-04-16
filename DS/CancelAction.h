#pragma once
#include "Action.h"
class CancelAction :
    public Action
{
    public:
    CancelAction(int ID, OrderType type, int time, double pr, double s, double d) : Action(ID, type, time, pr, s, d) {}
	void Act();
};

