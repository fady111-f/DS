#include "UI.h"

UI::UI() {}

UI::~UI() {}

// Print the current simulation state
void UI::PrintState(int timestep,
    LinkedQueue<Order*>& pendODG,
    Pend_OVC& pendOVC,
    LinkedQueue<Chef*>& availNormChefs,
    Cook_Ords& cookingOrders,
    Fit_Tables& availableTables,
    LinkedStack<Order*>& finishedOrders)
{
    std::cout << "========================================" << std::endl;
    std::cout << "Timestep: " << timestep << std::endl;
    std::cout << "========================================" << std::endl;

    // 1. Print Pending Orders
    std::cout << "Pending Orders IDs:" << std::endl;
    std::cout << pendODG.GetCount() << " ODG: ";
    pendODG.print();
    std::cout << std::endl;

    std::cout << pendOVC.GetCount() << " OVC: ";
    pendOVC.print();
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 2. Print Available Chefs
    std::cout << "Available Chefs IDs:" << std::endl;
    std::cout << availNormChefs.GetCount() << " CN: ";
    availNormChefs.print();
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 3. Print Cooking Orders
    std::cout << "Cooking Orders IDs:" << std::endl;
    std::cout << cookingOrders.GetCount() << " Cooking: ";
    cookingOrders.print();
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 4. Print Available Tables
    std::cout << "Available Tables:" << std::endl;
    std::cout << availableTables.GetCount() << " Tables: ";
    availableTables.print();
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 5. Print Finished Orders (Stack prints from newest to oldest)
    std::cout << "Finished Orders IDs (Newest to Oldest):" << std::endl;
    std::cout << finishedOrders.GetCount() << " Finished: ";
    finishedOrders.print();
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
}