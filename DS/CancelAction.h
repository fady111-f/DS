#pragma once
#include "Action.h"
class CancelAction : public Action
{
    public:
    CancelAction(int ID) : Action(ID) {}
	void Act(Restaurant* res);
};

