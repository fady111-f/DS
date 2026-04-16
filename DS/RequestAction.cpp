#include "RequestAction.h"

void RequestAction::Act()
{
	Order* ord = new Order(OrderID, type, price, size, distance);
	switch (type) {
		case TYPE_ODG:
		res->add_odg(ord);
		break;
		case TYPE_ODN:
		res->add_odn(ord);
		break;
		case TYPE_OT:
		res->add_ot(ord);
		break;
		case TYPE_OVN:
		res->add_ovn(ord);
		break;
		case TYPE_OVC:
		res->add_ovc(ord);
		break;
		case TYPE_OVG:
		double priority = price * size * distance;
		res->add_ovg(ord, priority);
		break;
	}
}
