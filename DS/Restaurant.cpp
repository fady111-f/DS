#include "Restaurant.h"

Restaurant::Restaurant() {
    pUI = new UI();
}

Restaurant::~Restaurant() {
    delete pUI;
}

void Restaurant::RunSimulation() {
    // --- PHASE 1.2 TESTING: Dummy Data ---

    // 1. Add some Pending Orders
    pendODG.enqueue(new Order(333, TYPE_ODG));
    pendODG.enqueue(new Order(334, TYPE_ODG));
    pendOVC.enqueue(new Order(79, TYPE_OVC));

    // 2. Add some Available Chefs
    availNormChefs.enqueue(new Chef(2, 'N'));
    availNormChefs.enqueue(new Chef(7, 'N'));

    // 3. Add some Cooking Orders (Priority Queue: higher number = higher priority)
    cookingOrders.enqueue(new Order(55, TYPE_ODN), 5);  // Priority 5
    cookingOrders.enqueue(new Order(56, TYPE_ODN), 10); // Priority 10 (Will print first)

    // 4. Add some Available Tables
    // Table arguments: (ID, Capacity). Priority here is usually (1/seats) or something similar for best fit.
    availableTables.enqueue(new Table(7, 8), 5);
    availableTables.enqueue(new Table(3, 4), 10);

    // 5. Add some Finished Orders (Stack: LIFO - Last In First Out)
    finishedOrders.push(new Order(1, TYPE_ODG));
    finishedOrders.push(new Order(19, TYPE_OVC));
    finishedOrders.push(new Order(2, TYPE_ODG));
    finishedOrders.push(new Order(39, TYPE_OT));

    // Print the state using UI
    int timestep = 1;
    pUI->PrintState(timestep, pendODG, pendOVC, availNormChefs, cookingOrders, availableTables, finishedOrders);

    std::cout << "PRESS ANY KEY TO MOVE TO NEXT..." << std::endl;
    std::cin.get(); // Waits for user input
}