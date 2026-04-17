#include "Restaurant.h"
#include "Action.h"
#include "RequestAction.h"
#include "CancelAction.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

// ==========================================================
// Constructor & Destructor
// ==========================================================
Restaurant::Restaurant()
{
    // If you have a UI class, initialize it here
    // pUI = new UI(); 
}

Restaurant::~Restaurant()
{
    // Clean up memory
    // if (pUI) delete pUI;

    Order* tempOrd;
    while (Finished_Orders.pop(tempOrd)) delete tempOrd;
    while (Cancelled_Orders.dequeue(tempOrd)) delete tempOrd;
}

// ==========================================================
// Adder Functions (Used by RequestAction)
// ==========================================================
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

void Restaurant::add_ovg(Order* o, double priority)
{
    PEND_OVG.enqueue(o, priority);
}

// ==========================================================
// Action Handling
// ==========================================================
void Restaurant::AddAction(Action* pAction)
{
    Actions.enqueue(pAction);
}

// ==========================================================
// Cancel Logic (Used by CancelAction)
// ==========================================================
void Restaurant::CancelOVC(int targetID)
{
    Order* tempOrd;
    bool found = false;

    // 1. Search in PEND_OVC
    if (PEND_OVC.CancelOrder(targetID))
        return;

    // 2. Search in RDY_OVL
    if (RDY_OVL.SearchAndRemove(targetID))
        return;

    // 3. Search in Cooking_Orders
   Chef* assignedChef = Cooking_Orders.CancelOrder(targetID);
      if (!assignedChef) return;
      // If found in Cooking_Orders, the assigned chef becomes free
    if (assignedChef->GetType() == 'S') {
        Free_CS.enqueue(assignedChef);
    }
    else {
        Free_CN.enqueue(assignedChef);
	}
}

// ==========================================================
// Print Information
// ==========================================================
void Restaurant::PrintAll(int timestep)
{
    std::cout << "Current Timestep:" << timestep << "\n";

    // Helper variables for printing
    int count;
    std::string listStr;
    Order* ord; Chef* chf; Scooter* sct; Table* tbl;

    // ==========================================
    // 1. Pending Orders
    // ==========================================
    std::cout << "Pending Orders IDs\n";
    LinkedQueue<Order*> tempQ_ord;

    // ODG
    count = 0; listStr = "";
    while (PEND_ODG.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) PEND_ODG.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " ODG: " << listStr << "\n";

    // ODN
    count = 0; listStr = "";
    while (PEND_ODN.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) PEND_ODN.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " ODN: " << listStr << "\n";

    // OT
    count = 0; listStr = "";
    while (PEND_OT.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) PEND_OT.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " OT: " << listStr << "\n";

    // OVN
    count = 0; listStr = "";
    while (PEND_OVN.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) PEND_OVN.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " OVN: " << listStr << "\n";

    // OVC
    count = 0; listStr = "";
    while (PEND_OVC.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) PEND_OVC.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " OVC: " << listStr << "\n";

    // OVG (Priority Queue)
    PriQueue<Order*> tempPriQ_ord;
    count = 0; listStr = "";
    while (PEND_OVG.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempPriQ_ord.enqueue(ord, ord->GetPriority());
    }
    while (tempPriQ_ord.dequeue(ord)) PEND_OVG.enqueue(ord, ord->GetPriority());
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " OVG: " << listStr << "\n";

    // ==========================================
    // 2. Available Chefs
    // ==========================================
    std::cout << "Available chefs IDs\n";
    LinkedQueue<Chef*> tempQ_chf;

    // CS
    count = 0; listStr = "";
    while (Free_CS.dequeue(chf)) {
        count++; listStr += std::to_string(chf->GetID()) + ", ";
        tempQ_chf.enqueue(chf);
    }
    while (tempQ_chf.dequeue(chf)) Free_CS.enqueue(chf);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " CS: " << listStr << "\n";

    // CN
    count = 0; listStr = "";
    while (Free_CN.dequeue(chf)) {
        count++; listStr += std::to_string(chf->GetID()) + ", ";
        tempQ_chf.enqueue(chf);
    }
    while (tempQ_chf.dequeue(chf)) Free_CN.enqueue(chf);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " CN: " << listStr << "\n";

    // ==========================================
    // 3. Cooking Orders
    // ==========================================
    std::cout << "Cooking orders [Orders ID, chef ID]\n";
    count = 0; listStr = "";
    while (Cooking_Orders.dequeue(ord)) {
        count++;
        int cID = (ord->AssignedChef() != nullptr) ? ord->AssignedChef()->GetID() : -1;
        listStr += "[" + std::to_string(ord->GetID()) + ", " + std::to_string(cID) + "], ";
        tempPriQ_ord.enqueue(ord, ord->GetPriority());
    }
    while (tempPriQ_ord.dequeue(ord)) Cooking_Orders.enqueue(ord, ord->GetPriority());
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " cooking orders: " << listStr << "\n";

    // ==========================================
    // 4. Ready Orders
    // ==========================================
    std::cout << "Ready Orders IDs\n";

    // OT
    count = 0; listStr = "";
    while (RDY_OT.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) RDY_OT.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " OT: " << listStr << "\n";

    // OV (from RDY_OVL)
    count = 0; listStr = "";
    while (RDY_OVL.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) RDY_OVL.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " OV: " << listStr << "\n";

    // OD
    count = 0; listStr = "";
    while (RDY_OD.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) RDY_OD.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " OD: " << listStr << "\n";

    // ==========================================
    // 5. Available Scooters
    // ==========================================
    std::cout << "Available scooters IDs\n";
    PriQueue<Scooter*> tempPriQ_sct;
    count = 0; listStr = "";
    while (Free_Scooters.dequeue(sct)) {
        count++; listStr += std::to_string(sct->GetID()) + ", ";
        tempPriQ_sct.enqueue(sct, -sct->GetDistance());
    }
    while (tempPriQ_sct.dequeue(sct)) Free_Scooters.enqueue(sct, -sct->GetDistance());
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " Scooters: " << listStr << "\n";

    // ==========================================
    // 6. Available Tables
    // ==========================================
    std::cout << "Available tables [ID, capacity, free seats]\n";
    Fit_Tables tempQ_tbl;
    count = 0; listStr = "";
    while (Free_Tables.dequeue(tbl)) {
        count++;
        listStr += "[T" + std::to_string(tbl->GetID()) + ", " +
            std::to_string(tbl->GetCapacity()) + ", " +
            std::to_string(tbl->GetFreeSeats()) + "], ";
        tempQ_tbl.enqueue(tbl, 1);
    }
    while (tempQ_tbl.dequeue(tbl)) Free_Tables.enqueue(tbl, 1);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " tables: " << listStr << "\n";

    // ==========================================
    // 7. In-Service Orders
    // ==========================================
    std::cout << "In-Service orders [order ID, scooter/Table ID]\n";
    count = 0; listStr = "";
    while (InServ_Orders.dequeue(ord)) {
        count++;
        std::string resID = "";
        if (ord->AssignedScooter() != nullptr) resID = "S" + std::to_string(ord->AssignedScooter()->GetID());
        else if (ord->AssignedTable() != nullptr) resID = "T" + std::to_string(ord->AssignedTable()->GetID());
        else resID = "None";

        listStr += "[" + std::to_string(ord->GetID()) + ", " + resID + "], ";
        tempPriQ_ord.enqueue(ord, ord->GetPriority());
    }
    while (tempPriQ_ord.dequeue(ord)) InServ_Orders.enqueue(ord, ord->GetPriority());
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " Orders: " << listStr << "\n";

    // ==========================================
    // 8. In-Maintenance Scooters
    // ==========================================
    std::cout << "In-maintainance scooters IDs\n";
    LinkedQueue<Scooter*> tempQ_sct;
    count = 0; listStr = "";
    while (Maint_Scooters.dequeue(sct)) {
        count++; listStr += std::to_string(sct->GetID()) + ", ";
        tempQ_sct.enqueue(sct);
    }
    while (tempQ_sct.dequeue(sct)) Maint_Scooters.enqueue(sct);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " scooters: " << listStr << "\n";

    // ==========================================
    // 9. Scooters Back to Restaurant
    // ==========================================
    std::cout << "Scooters Back to Restaurant IDs\n";
    count = 0; listStr = "";
    while (Back_Scooters.dequeue(sct)) {
        count++; listStr += std::to_string(sct->GetID()) + ", ";
        tempPriQ_sct.enqueue(sct, 1);
    }
    while (tempPriQ_sct.dequeue(sct)) Back_Scooters.enqueue(sct, 1);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " scooters: " << listStr << "\n";

    // ==========================================
    // 10. Cancelled Orders
    // ==========================================
    std::cout << "Cancelled Orders IDs\n";
    count = 0; listStr = "";
    while (Cancelled_Orders.dequeue(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempQ_ord.enqueue(ord);
    }
    while (tempQ_ord.dequeue(ord)) Cancelled_Orders.enqueue(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " cancelled: " << listStr << "\n";

    // ==========================================
    // 11. Finished Orders
    // ==========================================
    std::cout << "Finished orders IDs----\n";
    LinkedStack<Order*> tempS_ord;
    count = 0; listStr = "";
    // Using Stack pop/push gives them to us in descending finish time naturally [cite: 316]
    while (Finished_Orders.pop(ord)) {
        count++; listStr += std::to_string(ord->GetID()) + ", ";
        tempS_ord.push(ord);
    }
    while (tempS_ord.pop(ord)) Finished_Orders.push(ord);
    if (count > 0) listStr = listStr.substr(0, listStr.length() - 2);
    std::cout << count << " Orders: " << listStr << "\n";

    std::cout << "--------------------------------------------------------\n";
}

// ==========================================================
// Simulation Logic
// ==========================================================
void Restaurant::RunSimulation()
{
    // For Phase 1, we just call the RandomSimulator.
    // In Phase 2, this will read from the input file instead.
    RandomSimulator();
}

void Restaurant::RandomSimulator()
{
    srand((unsigned int)time(0));

    int totalOrders = 500;
    int finishedOrCancelled = 0;
    int timestep = 0;
    int maxTimesteps = 2000;

    // 1. Initialize Resources
    for (int i = 1; i <= 20; i++) Free_CN.enqueue(new Chef(i, 'N'));
    for (int i = 21; i <= 30; i++) Free_CS.enqueue(new Chef(i, 'S'));

    // Scooters with Priority 0 (distance 0)
    for (int i = 1; i <= 20; i++) Free_Scooters.enqueue(new Scooter(i, 0), 0);

    for (int i = 1; i <= 20; i++) Free_Tables.enqueue(new Table(i, (rand() % 5 + 1) * 2), rand() % 100 + 1);

    // 2. Randomly generate pending orders using RequestAction
    for (int i = 1; i <= totalOrders; i++)
    {
        int randomType = rand() % 6;
        int size = rand() % 5 + 1;
        double price = rand() % 200 + 50;
        int distance = rand() % 20 + 1;

        RequestAction* reqAct = new RequestAction(i, (OrderType)randomType, size, price, distance);
        reqAct->Act(this);
        delete reqAct;
    }

    std::cout << "\n========== Initial State (Timestep 0) ==========\n";
    PrintAll(timestep);
    std::cout << "\nPress [Enter] to advance to timestep 1...";
    std::cin.get();

    // 3. Main Loop
    while (finishedOrCancelled < totalOrders && timestep < maxTimesteps)
    {
        timestep++;

        // 3.1. Pick order and assign APPROPRIATE chef
        for (int i = 0; i < 30; i++)
        {
            int choice = rand() % 6;
            Order* ord = nullptr;
            Chef* chef = nullptr;
            bool gotOrder = false;

            switch (choice) {
            case 0: gotOrder = PEND_ODG.dequeue(ord); break;
            case 1: gotOrder = PEND_ODN.dequeue(ord); break;
            case 2: gotOrder = PEND_OT.dequeue(ord); break;
            case 3: gotOrder = PEND_OVN.dequeue(ord); break;
            case 4: gotOrder = PEND_OVC.dequeue(ord); break;
            case 5: gotOrder = PEND_OVG.dequeue(ord); break;
            }

            if (!gotOrder) continue;

            bool chefAssigned = false;

            if (ord->GetType() == TYPE_OT) {
                chefAssigned = Free_CN.dequeue(chef);
            }
            else if (ord->GetType() == TYPE_ODG) {
                chefAssigned = Free_CS.dequeue(chef);
            }
            else {
                if (rand() % 2 == 0) {
                    chefAssigned = Free_CN.dequeue(chef);
                    if (!chefAssigned) chefAssigned = Free_CS.dequeue(chef);
                }
                else {
                    chefAssigned = Free_CS.dequeue(chef);
                    if (!chefAssigned) chefAssigned = Free_CN.dequeue(chef);
                }
            }

            if (chefAssigned && chef) {
                ord->AssignChef(chef);
                int cookingPriority = rand() % 100 + 1;
                ord->SetPriority(cookingPriority);
                Cooking_Orders.enqueue(ord, cookingPriority);
            }
            else {
                switch (ord->GetType()) {
                case TYPE_ODG: PEND_ODG.enqueue(ord); break;
                case TYPE_ODN: PEND_ODN.enqueue(ord); break;
                case TYPE_OT:  PEND_OT.enqueue(ord); break;
                case TYPE_OVN: PEND_OVN.enqueue(ord); break;
                case TYPE_OVC: PEND_OVC.enqueue(ord); break;
                case TYPE_OVG: PEND_OVG.enqueue(ord, rand() % 100 + 1); break;
                }
            }
        }

        // 3.2. Move from cooking to ready
        for (int i = 0; i < 15; i++)
        {
            if ((rand() % 100) >= 75) continue;

            Order* ord = nullptr;
            if (Cooking_Orders.dequeue(ord)) {
                int listChoice = rand() % 3;
                if (listChoice == 0) RDY_OT.enqueue(ord);
                else if (listChoice == 1) RDY_OVL.enqueue(ord);
                else RDY_OD.enqueue(ord);

                Chef* c = ord->AssignedChef();
                if (c) {
                    if (c->GetType() == 'N') Free_CN.enqueue(c);
                    else Free_CS.enqueue(c);
                    ord->AssignChef(nullptr);
                }
            }
        }

        // 3.3. Pick from ready list & Assign Resources
        for (int i = 0; i < 10; i++)
        {
            int choice = rand() % 3;
            Order* ord = nullptr;
            bool gotOrder = false;

            if (choice == 0) gotOrder = RDY_OT.dequeue(ord);
            else if (choice == 1) gotOrder = RDY_OVL.dequeue(ord);
            else gotOrder = RDY_OD.dequeue(ord);

            if (!gotOrder) continue;

            if (ord->GetType() == TYPE_OT) {
                Finished_Orders.push(ord);
                finishedOrCancelled++;
            }
            else {
                if (ord->GetType() == TYPE_OVN || ord->GetType() == TYPE_OVC || ord->GetType() == TYPE_OVG) {
                    Scooter* s = nullptr;
                    if (Free_Scooters.dequeue(s)) {
                        ord->AssignScooter(s);
                        s->AddDistance(ord->GetDistance());
                        s->IncrementDeliveries();
                    }
                }
                else if (ord->GetType() == TYPE_ODG || ord->GetType() == TYPE_ODN) {
                    Table* t = nullptr;
                    if (Free_Tables.dequeue(t)) {
                        ord->AssignTable(t);
                        if (ord->GetType() == TYPE_ODG) {
                            Busy_Sharable.enqueue(t, t->GetFreeSeats());
                        }
                        else {
                            Busy_No_Share.enqueue(t, t->GetID());
                        }
                    }
                }
                InServ_Orders.enqueue(ord, rand() % 100 + 1);
            }
        }

        // 3.4, 3.5, 3.6. Cancel logic using CancelAction
        for (int k = 0; k < 3; k++)
        {
            int targetID = rand() % totalOrders + 1;
            CancelAction* cancelAct = new CancelAction(targetID);
            cancelAct->Act(this);
            delete cancelAct;
        }

        // 3.7. In Service processing
        for (int i = 0; i < 20; i++)
        {
            if ((rand() % 100) < 25) {
                Order* ord = nullptr;
                if (InServ_Orders.dequeue(ord)) {
                    Finished_Orders.push(ord);
                    finishedOrCancelled++;

                    Scooter* s = ord->AssignedScooter();
                    if (s) {
                        Back_Scooters.enqueue(s, rand() % 100 + 1);
                        ord->AssignScooter(nullptr);
                    }

                    Table* t = ord->AssignedTable();
                    if (t) {
                        Free_Tables.enqueue(t, rand() % 100 + 1);
                        Table* tempT = nullptr;
                        bool found = false;

                        if (ord->GetType() == TYPE_ODG) {
                            Fit_Tables tempQ;
                            while (Busy_Sharable.dequeue(tempT)) {
                                if (!found && tempT == t) found = true;
                                else tempQ.enqueue(tempT, tempT->GetFreeSeats());
                            }
                            while (tempQ.dequeue(tempT)) Busy_Sharable.enqueue(tempT, tempT->GetFreeSeats());
                        }
                        else if (ord->GetType() == TYPE_ODN) {
                            Fit_Tables tempQ;
                            while (Busy_No_Share.dequeue(tempT)) {
                                if (!found && tempT == t) found = true;
                                else tempQ.enqueue(tempT, tempT->GetID());
                            }
                            while (tempQ.dequeue(tempT)) Busy_No_Share.enqueue(tempT, tempT->GetID());
                        }
                        ord->AssignTable(nullptr);
                    }
                }
            }
        }

        // 3.8. Back to Free or Maintenance
        if ((rand() % 100) < 50) {
            Scooter* s = nullptr;
            if (Back_Scooters.dequeue(s)) {
                if ((rand() % 100) < 50) {
                    Free_Scooters.enqueue(s, -s->GetDistance());
                }
                else {
                    Maint_Scooters.enqueue(s);
                }
            }
        }

        // 3.9. Pick scooter from Maint to Free
        if ((rand() % 100) < 50) {
            Scooter* s = nullptr;
            if (Maint_Scooters.dequeue(s)) {
                Free_Scooters.enqueue(s, -s->GetDistance());
            }
        }

        // 3.10. Print info
        std::cout << "\n========== Snapshot at timestep " << timestep << " ==========\n";
        PrintAll(timestep);

        std::cout << "\nPress [Enter] to advance to timestep " << timestep + 1 << "...";
        std::cin.get();
    }

    // 4. End the simulation
    std::cout << "\n=====================================\n";
    std::cout << "Simulation Ended at timestep: " << timestep << "\n";
    std::cout << "Total Orders Generated: " << totalOrders << "\n";
    std::cout << "=====================================\n";
}