#include "Restaurant.h"

Restaurant::Restaurant() {
    pUI = new UI();
}

Restaurant::~Restaurant() {
    delete pUI;
}

//void Restaurant::RunSimulation() {
//    // --- PHASE 1.2 TESTING: Dummy Data ---
//
//    // 1. Add some Pending Orders
//    PEND_OVG.enqueue(new Order(333, TYPE_ODG));
//    PEND_ODG.enqueue(new Order(334, TYPE_ODG));
//    PEND_OVC.enqueue(new Order(79, TYPE_OVC));
//
//    // 2. Add some Available Chefs
//    Free_CN.enqueue(new Chef(2, 'N'));
//    Free_CN.enqueue(new Chef(7, 'N'));
//
//    // 3. Add some Cooking Orders (Priority Queue: higher number = higher priority)
//    Cooking_Orders.enqueue(new Order(55, TYPE_ODN), 5);  // Priority 5
//    Cooking_Orders.enqueue(new Order(56, TYPE_ODN), 10); // Priority 10 (Will print first)
//
//    // 4. Add some Available Tables
//    // Table arguments: (ID, Capacity). Priority here is usually (1/seats) or something similar for best fit.
//    Free_Tables.enqueue(new Table(7, 8), 5);
//    Free_Tables.enqueue(new Table(3, 4), 10);
//
//    // 5. Add some Finished Orders (Stack: LIFO - Last In First Out)
//    Finished_Orders.push(new Order(1, TYPE_ODG));
//    Finished_Orders.push(new Order(19, TYPE_OVC));
//    Finished_Orders.push(new Order(2, TYPE_ODG));
//    Finished_Orders.push(new Order(39, TYPE_OT));
//
//    // Print the state using UI
//    int timestep = 1;
//    pUI->PrintState(timestep, PEND_ODG, PEND_OVC, Free_CN, Cooking_Orders, Free_Tables, Finished_Orders);
//    std::cout << "PRESS ANY KEY TO MOVE TO NEXT..." << std::endl;
//    std::cin.get(); // Waits for user input
//}

void Restaurant::add_odg(Order* o)
{
    PEND_ODG.enqueue(o);
}
void Restaurant::add_odn(Order* o)
{
    PEND_ODN.enqueue(o);
}
void Restaurant::add_ot(Order* o)
{
    PEND_OT.enqueue(o);
}
void Restaurant::add_ovn(Order* o)
{
    PEND_OVN.enqueue(o);
}
void Restaurant::add_ovc(Order* o)
{
    PEND_OVC.enqueue(o);
}
void Restaurant::add_ovg(Order* o, int priority)
{
    PEND_OVG.enqueue(o, priority);
}