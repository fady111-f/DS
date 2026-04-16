#ifndef UI_H
#define UI_H

#include <iostream>
#include "LinkedQueue.h"
#include "LinkedStack.h"
#include "PriQueue.h"
#include "DerivedDS.h"

#include "Order.h"
#include "Chef.h"
#include "Scooter.h"
#include "Table.h"

class UI
{
public:
    UI();
    ~UI();

    void PrintState(
        int timestep,

        LinkedQueue<Order*>& PEND_ODG,
        LinkedQueue<Order*>& PEND_ODN,
        LinkedQueue<Order*>& PEND_OT,
        LinkedQueue<Order*>& PEND_OVN,
        LinkedQueue<Order*>& PEND_OVC,
        PriQueue<Order*>& PEND_OVG,

        LinkedQueue<Chef*>& Free_CS,
        LinkedQueue<Chef*>& Free_CN,

        PriQueue<Order*>& Cooking_Orders,

        LinkedQueue<Order*>& RDY_OT,
        LinkedQueue<Order*>& RDY_OV,
        LinkedQueue<Order*>& RDY_OD,

        PriQueue<Order*>& InServ_Orders,

        LinkedQueue<Order*>& Cancelled_Orders,
        LinkedStack<Order*>& Finished_Orders,

        PriQueue<Scooter*>& Free_Scooters,
        PriQueue<Scooter*>& Back_Scooters,
        LinkedQueue<Scooter*>& Maint_Scooters,

        PriQueue<Table*>& Free_Tables,
        PriQueue<Table*>& Busy_Sharable,
        PriQueue<Table*>& Busy_No_Share
    );
};

#endif // UI_H