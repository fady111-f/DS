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
        Pend_OVC& PEND_OVC_List,
        PriQueue<Order*>& PEND_OVG,

        LinkedQueue<Chef*>& Free_CS,
        LinkedQueue<Chef*>& Free_CN,

        Cook_Ords& Cooking_Orders,

        LinkedQueue<Order*>& RDY_OT,
        RDY_OV& RDY_OV_List,
        LinkedQueue<Order*>& RDY_OD,

        PriQueue<Order*>& InServ_Orders,

        LinkedQueue<Order*>& Cancelled_Orders,
        LinkedStack<Order*>& Finished_Orders,

        PriQueue<Scooter*>& Free_Scooters,
        PriQueue<Scooter*>& Back_Scooters,
        LinkedQueue<Scooter*>& Maint_Scooters,

        Fit_Tables& Free_Tables,
        Fit_Tables& Busy_Sharable,
        Fit_Tables& Busy_No_Share
    );
};

#endif // UI_H