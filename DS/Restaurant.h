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

class Restaurant {
private:
    UI* pUI;

    // Data Structures for Phase 1.2 Testing
    LinkedQueue<Order*> pendODG;
    Pend_OVC pendOVC;
    LinkedQueue<Chef*> availNormChefs;
    Cook_Ords cookingOrders;
    Fit_Tables availableTables;
    LinkedStack<Order*> finishedOrders;

public:
    Restaurant();
    ~Restaurant();
    void RunSimulation();
};

#endif // RESTAURANT_H