#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "UI.h"
#include "LinkedQueue.h"
#include "LinkedStack.h"
#include "PriQueue.h"
#include "DerivedDS.h"

#include "Order.h"
#include "Chef.h"
#include "Table.h"
#include "Scooter.h"

class Restaurant
{
private:
    UI* pUI;

    // Pending Orders
    LinkedQueue<Order*> PEND_ODG;
    LinkedQueue<Order*> PEND_ODN;
    LinkedQueue<Order*> PEND_OT;
    LinkedQueue<Order*> PEND_OVN;
    Pend_OVC PEND_OVC_List;
    PriQueue<Order*> PEND_OVG;

    // Free Chefs
    LinkedQueue<Chef*> Free_CS;
    LinkedQueue<Chef*> Free_CN;

    // Cancelled / Finished
    LinkedQueue<Order*> Cancelled_Orders;
    LinkedStack<Order*> Finished_Orders;

    // Cooking / Ready / In-Service
    Cook_Ords Cooking_Orders;
    LinkedQueue<Order*> RDY_OT;
    RDY_OV RDY_OV_List;
    LinkedQueue<Order*> RDY_OD;
    PriQueue<Order*> InServ_Orders;

    // Scooters
    PriQueue<Scooter*> Free_Scooters;
    PriQueue<Scooter*> Back_Scooters;
    LinkedQueue<Scooter*> Maint_Scooters;

    // Tables
    Fit_Tables Free_Tables;
    Fit_Tables Busy_Sharable;
    Fit_Tables Busy_No_Share;

public:
    Restaurant();
    ~Restaurant();

    void add_odg(Order* o);
    void add_odn(Order* o);
    void add_ot(Order* o);
    void add_ovn(Order* o);
    void add_ovc(Order* o);
    void add_ovg(Order* o, int priority);

    void PrintAll(int timestep);
    void RandomSimulator();
    void RunSimulation();
};

#endif // RESTAURANT_H