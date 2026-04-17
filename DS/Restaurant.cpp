#include "Restaurant.h"
#include "Action.h"  // ضروري للـ Actions
#include <cstdlib>
#include <ctime>
#include <iostream>

// ==========================================================
// Constructor & Destructor
// ==========================================================

Restaurant::Restaurant()
{
    pUI = new UI();
}

Restaurant::~Restaurant()
{
    delete pUI;
}

// ==========================================================
// Queue Additions (Orders)
// ==========================================================

void Restaurant::add_odg(Order* o) { PEND_ODG.enqueue(o); }
void Restaurant::add_odn(Order* o) { PEND_ODN.enqueue(o); }
void Restaurant::add_ot(Order* o) { PEND_OT.enqueue(o); }
void Restaurant::add_ovn(Order* o) { PEND_OVN.enqueue(o); }
void Restaurant::add_ovc(Order* o) { PEND_OVC.enqueue(o); }

// تم التعديل لـ double بناءً على الحسبة في الـ RequestAction
void Restaurant::add_ovg(Order* o, double priority) { PEND_OVG.enqueue(o, priority); }

// ==========================================================
// Queue Additions (Actions)
// ==========================================================

void Restaurant::AddRequestAction(Action* pAction)
{
    RequestActions.enqueue(pAction);
}

void Restaurant::AddCancelAction(Action* pAction)
{
    CancelActions.enqueue(pAction);
}

// ==========================================================
// Print State
// ==========================================================

void Restaurant::PrintAll(int timestep)
{
    pUI->PrintState(
        timestep,
        PEND_ODG, PEND_ODN, PEND_OT, PEND_OVN, PEND_OVC, PEND_OVG,
        Free_CS, Free_CN,
        Cooking_Orders,
        RDY_OT, RDY_OVL, RDY_OD,
        InServ_Orders,
        Cancelled_Orders, Finished_Orders,
        Free_Scooters, Back_Scooters, Maint_Scooters,
        Free_Tables, Busy_Sharable, Busy_No_Share
    );
}

// ==========================================================
// Cancel Logic
// ==========================================================

void Restaurant::CancelOVC(int id)
{
    PEND_OVC.CancelOrder(id);
    Cooking_Orders.CancelOrder(id);
    RDY_OVL.SearchAndRemove(id);
}

// ==========================================================
// Simulation Functions
// ==========================================================

void Restaurant::RandomSimulator()
{
    // 1. Perform any needed initializations
    srand((unsigned int)time(0));

    int totalOrders = 500;
    int finishedOrCancelled = 0;
    int timestep = 0;
    int maxTimesteps = 2000; // لضمان عدم الدخول في Infinite Loop

    for (int i = 1; i <= 20; i++) Free_CN.enqueue(new Chef(i, 'N'));
    for (int i = 21; i <= 30; i++) Free_CS.enqueue(new Chef(i, 'S'));
    for (int i = 1; i <= 20; i++) Free_Scooters.enqueue(new Scooter(i, 0), rand() % 100 + 1);
    for (int i = 1; i <= 20; i++) Free_Tables.enqueue(new Table(i, (rand() % 5 + 1) * 2), rand() % 100 + 1);

    // 2. Randomly generate at least 500 pending orders randomly distributed
    for (int i = 1; i <= totalOrders; i++)
    {
        int randomType = rand() % 6;
        Order* newOrder = new Order(i, (OrderType)randomType, rand() % 5 + 1, rand() % 200 + 50, rand() % 20 + 1);

        switch (randomType)
        {
        case TYPE_ODG: PEND_ODG.enqueue(newOrder); break;
        case TYPE_ODN: PEND_ODN.enqueue(newOrder); break;
        case TYPE_OT:  PEND_OT.enqueue(newOrder); break;
        case TYPE_OVN: PEND_OVN.enqueue(newOrder); break;
        case TYPE_OVC: PEND_OVC.enqueue(newOrder); break;
        case TYPE_OVG: PEND_OVG.enqueue(newOrder, rand() % 100 + 1); break;
        }
    }

    std::cout << "\n========== Initial State (Timestep 0) ==========\n";
    PrintAll(timestep);
    std::cout << "\nPress [Enter] to advance to timestep 1...";
    std::cin.get();

    // 3. At each time step follow the following algorithm:
    while (finishedOrCancelled < totalOrders && timestep < maxTimesteps)
    {
        timestep++;

        // 3.1. Repeat the following steps 30 times:
        // - Randomly pick top order from pending lists
        // - Pick a random chef and move to Cooking list
        for (int i = 0; i < 30; i++)
        {
            int choice = rand() % 6;
            Order* ord = nullptr;
            Chef* chef = nullptr;
            bool gotOrder = false;

            switch (choice)
            {
            case 0: gotOrder = PEND_ODG.dequeue(ord); break;
            case 1: gotOrder = PEND_ODN.dequeue(ord); break;
            case 2: gotOrder = PEND_OT.dequeue(ord); break;
            case 3: gotOrder = PEND_OVN.dequeue(ord); break;
            case 4: gotOrder = PEND_OVC.dequeue(ord); break;
            case 5: gotOrder = PEND_OVG.dequeue(ord); break;
            }

            if (!gotOrder) continue;

            if (rand() % 2 == 0) {
                if (!Free_CN.dequeue(chef)) Free_CS.dequeue(chef);
            }
            else {
                if (!Free_CS.dequeue(chef)) Free_CN.dequeue(chef);
            }

            if (chef) {
                ord->AssignChef(chef);
                Cooking_Orders.enqueue(ord, rand() % 100 + 1);
            }
            else {
                // Return if no chef available
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

        // 3.2. With probability 75%, Pick a random order from cooking list
        // and distribute it randomly on ready orders lists. Repeat 15 times.
        for (int i = 0; i < 15; i++)
        {
            if ((rand() % 100) >= 75) continue; // 75% probability

            Order* ord = nullptr;
            if (Cooking_Orders.dequeue(ord))
            {
                int listChoice = rand() % 3;
                if (listChoice == 0) RDY_OT.enqueue(ord);
                else if (listChoice == 1) RDY_OVL.enqueue(ord);
                else RDY_OD.enqueue(ord);
            }
        }

        // 3.3. Repeat the following steps 10 times:
        // - Pick from ready list. If OT -> finish. If OV -> scooter. If OD -> table. Move to In-service.
        for (int i = 0; i < 10; i++)
        {
            int choice = rand() % 3;
            Order* ord = nullptr;
            bool gotOrder = false;

            if (choice == 0) gotOrder = RDY_OT.dequeue(ord);
            else if (choice == 1) gotOrder = RDY_OVL.dequeue(ord);
            else gotOrder = RDY_OD.dequeue(ord);

            if (!gotOrder) continue;

            if (ord->GetType() == TYPE_OT)
            {
                Finished_Orders.push(ord);
                finishedOrCancelled++;
                Chef* c = ord->AssignedChef();
                if (c) {
                    if (c->GetType() == 'N') Free_CN.enqueue(c);
                    else Free_CS.enqueue(c);
                    ord->AssignChef(nullptr);
                }
            }
            else
            {
                if (ord->GetType() == TYPE_OVN || ord->GetType() == TYPE_OVC || ord->GetType() == TYPE_OVG) {
                    Scooter* s = nullptr;
                    if (Free_Scooters.dequeue(s)) ord->AssignScooter(s);
                }
                // =====================================================================
                // إضافة الطاولة لقائمة المشغولين (Busy)
                // =====================================================================
                else if (ord->GetType() == TYPE_ODG || ord->GetType() == TYPE_ODN) {
                    Table* t = nullptr;
                    if (Free_Tables.dequeue(t)) {
                        ord->AssignTable(t);

                        if (ord->GetType() == TYPE_ODG) {
                            Busy_Sharable.enqueue(t, rand() % 100 + 1);
                        }
                        else {
                            Busy_No_Share.enqueue(t, rand() % 100 + 1);
                        }
                    }
                }
                InServ_Orders.enqueue(ord, rand() % 100 + 1);
            }
        }

        // Helpers للمحاكاة عشان نعمل Cancel بدون ما نعدل الـ .h
        int targetID;
        Order* tempOrd;

        // 3.4. Cancel function of "pending OVC"
        targetID = rand() % totalOrders + 1;
        LinkedQueue<Order*> tempQ_OVC;
        bool foundOVC = false;
        while (PEND_OVC.dequeue(tempOrd)) {
            if (!foundOVC && tempOrd->GetID() == targetID) {
                Cancelled_Orders.enqueue(tempOrd);
                finishedOrCancelled++;
                foundOVC = true;
            }
            else {
                tempQ_OVC.enqueue(tempOrd);
            }
        }
        while (tempQ_OVC.dequeue(tempOrd)) PEND_OVC.enqueue(tempOrd);

        // 3.5. Cancel function of "ready OVC"
        targetID = rand() % totalOrders + 1;
        LinkedQueue<Order*> tempQ_RDY;
        bool foundRDY = false;
        while (RDY_OVL.dequeue(tempOrd)) {
            if (!foundRDY && tempOrd->GetID() == targetID) {
                Cancelled_Orders.enqueue(tempOrd);
                finishedOrCancelled++;
                foundRDY = true;
            }
            else {
                tempQ_RDY.enqueue(tempOrd);
            }
        }
        while (tempQ_RDY.dequeue(tempOrd)) RDY_OVL.enqueue(tempOrd);

        // 3.6. Cancel function of "cooking OV", place in cancel and release chef.
        targetID = rand() % totalOrders + 1;
        PriQueue<Order*> tempQ_Cook;
        bool foundCook = false;
        while (Cooking_Orders.dequeue(tempOrd)) {
            if (!foundCook && tempOrd->GetID() == targetID) {
                Cancelled_Orders.enqueue(tempOrd);
                finishedOrCancelled++;
                Chef* c = tempOrd->AssignedChef();
                if (c) {
                    if (c->GetType() == 'N') Free_CN.enqueue(c);
                    else Free_CS.enqueue(c);
                    tempOrd->AssignChef(nullptr);
                }
                foundCook = true;
            }
            else {
                tempQ_Cook.enqueue(tempOrd, rand() % 100 + 1);
            }
        }
        while (tempQ_Cook.dequeue(tempOrd)) Cooking_Orders.enqueue(tempOrd, rand() % 100 + 1);

        // =========================================================================
        // 3.7. اللوب اللي بتحل مشكلة الاختناق وبترجع الموارد
        // =========================================================================
        for (int i = 0; i < 20; i++)
        {
            if ((rand() % 100) < 25)
            {
                Order* ord = nullptr;
                if (InServ_Orders.dequeue(ord))
                {
                    Finished_Orders.push(ord);
                    finishedOrCancelled++;

                    // إرجاع الطباخ
                    Chef* c = ord->AssignedChef();
                    if (c) {
                        if (c->GetType() == 'N') Free_CN.enqueue(c);
                        else Free_CS.enqueue(c);
                        ord->AssignChef(nullptr);
                    }

                    // إرجاع الموتوسيكل
                    Scooter* s = ord->AssignedScooter();
                    if (s) {
                        Back_Scooters.enqueue(s, rand() % 100 + 1);
                        ord->AssignScooter(nullptr);
                    }

                    // =======================================================
                    // إرجاع الطاولة وإزالتها من الـ Busy بالاسم بالضبط (الحل النهائي)
                    // =======================================================
                    Table* t = ord->AssignedTable();
                    if (t) {
                        Free_Tables.enqueue(t, rand() % 100 + 1);

                        Table* tempT = nullptr;
                        bool found = false;

                        if (ord->GetType() == TYPE_ODG) {
                            Fit_Tables tempQ;
                            // بندور على الطاولة بالظبط
                            while (Busy_Sharable.dequeue(tempT)) {
                                if (!found && tempT == t) {
                                    found = true; // لقيناها مش هنضيفها في المؤقت
                                }
                                else {
                                    tempQ.enqueue(tempT, rand() % 100 + 1);
                                }
                            }
                            // نرجع الباقي
                            while (tempQ.dequeue(tempT)) Busy_Sharable.enqueue(tempT, rand() % 100 + 1);
                        }
                        else if (ord->GetType() == TYPE_ODN) {
                            Fit_Tables tempQ;
                            while (Busy_No_Share.dequeue(tempT)) {
                                if (!found && tempT == t) {
                                    found = true;
                                }
                                else {
                                    tempQ.enqueue(tempT, rand() % 100 + 1);
                                }
                            }
                            while (tempQ.dequeue(tempT)) Busy_No_Share.enqueue(tempT, rand() % 100 + 1);
                        }

                        ord->AssignTable(nullptr);
                    }
                }
            }
        }

        // 3.8. With probability 50%, pick scooter from Scooter_Back to Free or Maint.
        if ((rand() % 100) < 50)
        {
            Scooter* s = nullptr;
            if (Back_Scooters.dequeue(s))
            {
                if ((rand() % 100) < 50) Free_Scooters.enqueue(s, rand() % 100 + 1);
                else Maint_Scooters.enqueue(s);
            }
        }

        // 3.9. With probability 50%, pick scooter from Maint to Free.
        if ((rand() % 100) < 50)
        {
            Scooter* s = nullptr;
            if (Maint_Scooters.dequeue(s))
            {
                Free_Scooters.enqueue(s, rand() % 100 + 1);
            }
        }

        // 3.10. Print info of all lists
        std::cout << "\n========== Snapshot at timestep " << timestep << " ==========\n";
        PrintAll(timestep);

        std::cout << "\nPress [Enter] to advance to timestep " << timestep + 1 << "...";
        std::cin.get();
    }

    // 4. End the simulation when ALL generated orders are in finish or cancel lists.
    std::cout << "\n=====================================\n";
    std::cout << "Simulation Ended at timestep: " << timestep << "\n";
    std::cout << "Total Orders: " << totalOrders << "\n";
    std::cout << "Finished/Cancelled: " << finishedOrCancelled << "\n";
    std::cout << "=====================================\n";
}

void Restaurant::RunSimulation()
{
    std::cout << "Starting Random Simulation...\n";
    RandomSimulator();
    std::cout << "\nSimulation Finished.\n";
}