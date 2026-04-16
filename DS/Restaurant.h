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

    LinkedQueue<Order*> PEND_ODG;
    LinkedQueue<Order*> PEND_ODN;
    LinkedQueue<Order*> PEND_OT;
    LinkedQueue<Order*> PEND_OVN;
    Pend_OVC PEND_OVC;
    PriQueue<Order*> PEND_OVG;
    LinkedQueue<Chef*> Free_CS;
    LinkedQueue<Chef*> Free_CN;
    LinkedQueue<Order*> Cancelled_Orders;
    LinkedStack<Order*> Finished_Orders;
    Cook_Ords Cooking_Orders;
    LinkedQueue<Order*> RDY_OT;
    RDY_OV RDY_OVL;
    LinkedQueue<Order*> RDY_OD;
    PriQueue<Order*> InServ_Orders;
    PriQueue<Scooter*> Free_Scooters;
    PriQueue<Scooter*> Back_Scooters;
    LinkedQueue<Scooter*> Maint_Scooters;
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
	void CancelOVC(int id);
};

#endif // RESTAURANT_H