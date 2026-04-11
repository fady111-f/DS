#ifndef UI_H
#define UI_H

#include <iostream>
// Including the Data Structures
#include "LinkedQueue.h"
#include "LinkedStack.h"
#include "PriQueue.h"
#include "DerivedDS.h"

// Including Entities
#include "Order.h"
#include "Chef.h"
#include "Scooter.h"
#include "Table.h"

class UI {
public:
    UI();
    ~UI();

    // Function to print the state of the restaurant at a specific timestep
    // We pass references to the lists so we don't copy them
    void PrintState(int timestep,
        LinkedQueue<Order*>& pendODG,
        Pend_OVC& pendOVC,
        LinkedQueue<Chef*>& availNormChefs,
        Cook_Ords& cookingOrders,
        Fit_Tables& availableTables,
        LinkedStack<Order*>& finishedOrders);
};

#endif // UI_H