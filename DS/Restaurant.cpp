#include "Restaurant.h"
#include <cstdlib>
#include <ctime>

Restaurant::Restaurant()
{
    pUI = new UI();
}

Restaurant::~Restaurant()
{
    delete pUI;
}

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

void Restaurant::PrintAll(int timestep)
{
    pUI->PrintState(
        timestep,

        PEND_ODG,
        PEND_ODN,
        PEND_OT,
        PEND_OVN,
        PEND_OVC,
        PEND_OVG,

        Free_CS,
        Free_CN,

        Cooking_Orders,

        RDY_OT,
        RDY_OV,
        RDY_OD,

        InServ_Orders,

        Cancelled_Orders,
        Finished_Orders,

        Free_Scooters,
        Back_Scooters,
        Maint_Scooters,

        Free_Tables,
        Busy_Sharable,
        Busy_No_Share
    );
}

void Restaurant::RandomSimulator()
{
    srand((unsigned int)time(0));

    int totalOrders = 500;
    int finishedOrCancelled = 0;
    int timestep = 0;
    int maxTimesteps = 1000;

    for (int i = 1; i <= 20; i++)
    {
        Free_CN.enqueue(new Chef(i, 'N'));
    }

    for (int i = 21; i <= 30; i++)
    {
        Free_CS.enqueue(new Chef(i, 'S'));
    }

    for (int i = 1; i <= 20; i++)
    {
        Free_Scooters.enqueue(new Scooter(i, 0), rand() % 100 + 1);
    }

    for (int i = 1; i <= 20; i++)
    {
        int capacity = (rand() % 5 + 1) * 2;
        int priority = 100 - capacity;
        Free_Tables.enqueue(new Table(i, capacity), priority);
    }

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

    while (finishedOrCancelled < totalOrders && timestep < maxTimesteps)
    {
        timestep++;

        for (int i = 0; i < 30; i++)
        {
            int choice = rand() % 6;
            Order* ord = nullptr;
            Chef* chef = nullptr;
            bool gotOrder = false;
            bool gotChef = false;

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

            if (rand() % 2 == 0) gotChef = Free_CN.dequeue(chef);
            else gotChef = Free_CS.dequeue(chef);

            if (!gotChef)
            {
                switch (ord->GetType())
                {
                case TYPE_ODG: PEND_ODG.enqueue(ord); break;
                case TYPE_ODN: PEND_ODN.enqueue(ord); break;
                case TYPE_OT: PEND_OT.enqueue(ord); break;
                case TYPE_OVN: PEND_OVN.enqueue(ord); break;
                case TYPE_OVC: PEND_OVC.enqueue(ord); break;
                case TYPE_OVG: PEND_OVG.enqueue(ord, rand() % 100 + 1); break;
                }
                continue;
            }

            ord->AssignChef(chef);
            Cooking_Orders.enqueue(ord, rand() % 100 + 1);
        }

        for (int i = 0; i < 15; i++)
        {
            if ((rand() % 100) >= 75) continue;

            Order* ord = nullptr;
            if (!Cooking_Orders.dequeue(ord)) continue;

            switch (ord->GetType())
            {
            case TYPE_OT: RDY_OT.enqueue(ord); break;
            case TYPE_OVN:
            case TYPE_OVC:
            case TYPE_OVG: RDY_OV.enqueue(ord); break;
            case TYPE_ODG:
            case TYPE_ODN: RDY_OD.enqueue(ord); break;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            int choice = rand() % 3;
            Order* ord = nullptr;
            bool gotOrder = false;

            switch (choice)
            {
            case 0: gotOrder = RDY_OT.dequeue(ord); break;
            case 1: gotOrder = RDY_OV.dequeue(ord); break;
            case 2: gotOrder = RDY_OD.dequeue(ord); break;
            }

            if (!gotOrder) continue;

            if (ord->GetType() == TYPE_OT)
            {
                Finished_Orders.push(ord);
                finishedOrCancelled++;

                Chef* chef = ord->AssignedChef();
                if (chef)
                {
                    if (chef->GetType() == 'N') Free_CN.enqueue(chef);
                    else Free_CS.enqueue(chef);
                    ord->AssignChef(nullptr);
                }
            }
            else
            {
                InServ_Orders.enqueue(ord, rand() % 100 + 1);
            }
        }

        if ((rand() % 100) < 10)
        {
            Order* ord = nullptr;
            if (PEND_OVC.dequeue(ord))
            {
                Cancelled_Orders.enqueue(ord);
                finishedOrCancelled++;
            }
        }
        if ((rand() % 100) < 10)
        {
            Order* ord = nullptr;
            if (RDY_OV.dequeue(ord))
            {
                Cancelled_Orders.enqueue(ord);
                finishedOrCancelled++;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            if ((rand() % 100) >= 25) continue;

            Order* ord = nullptr;
            if (!InServ_Orders.dequeue(ord)) continue;

            Finished_Orders.push(ord);
            finishedOrCancelled++;

            Chef* chef = ord->AssignedChef
            
            
            
            
            
            
            
            ();
            if (chef)
            {
                if (chef->GetType() == 'N') Free_CN.enqueue(chef);
                else Free_CS.enqueue(chef);
                ord->AssignChef(nullptr);
            }
        }

        std::cout << "\n========== Snapshot at timestep " << timestep << " ==========\n";
        PrintAll(timestep);

        std::cout << "\nPress [Enter] to advance to timestep " << timestep + 1 << "...";
        std::cin.get();
    }

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