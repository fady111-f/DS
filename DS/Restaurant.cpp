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
    PEND_OVC_List.enqueue(o);
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
        PEND_OVC_List,
        PEND_OVG,

        Free_CS,
        Free_CN,

        Cooking_Orders,

        RDY_OT,
        RDY_OV_List,
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

    // 1) Initialize chefs
    for (int i = 1; i <= 5; i++)
        Free_CN.enqueue(new Chef(i, 'N'));

    for (int i = 6; i <= 10; i++)
        Free_CS.enqueue(new Chef(i, 'S'));

    // 2) Initialize scooters
    for (int i = 1; i <= 5; i++)
        Free_Scooters.enqueue(new Scooter(i, 0), rand() % 100 + 1);

    // 3) Initialize tables
    for (int i = 1; i <= 5; i++)
    {
        int capacity = 2 * i;
        int priority = 100 - capacity;
        Free_Tables.enqueue(new Table(i, capacity), priority);
    }

    // 4) Generate random pending orders
    for (int i = 1; i <= 20; i++)
    {
        int randomType = rand() % 6;
        double price = rand() % 100 + 1;
        double size = rand() % 10 + 1;
        double distance = rand() % 20 + 1;
        Order* newOrder = new Order(i, (OrderType)randomType, price, size, distance);

        switch (randomType)
        {
        case TYPE_ODG:
            PEND_ODG.enqueue(newOrder);
            break;
        case TYPE_ODN:
            PEND_ODN.enqueue(newOrder);
            break;
        case TYPE_OT:
            PEND_OT.enqueue(newOrder);
            break;
        case TYPE_OVN:
            PEND_OVN.enqueue(newOrder);
            break;
        case TYPE_OVC:
            PEND_OVC_List.enqueue(newOrder);
            break;
        case TYPE_OVG:
            PEND_OVG.enqueue(newOrder, rand() % 100 + 1);
            break;
        }
    }

    // 5) Simulate multiple timesteps
    for (int timestep = 1; timestep <= 5; timestep++)
    {
        // -------------------------------
        // Move from Pending -> Cooking
        // -------------------------------
        for (int i = 0; i < 3; i++)
        {
            int choice = rand() % 6;
            Order* ord = nullptr;
            Chef* chef = nullptr;

            bool gotOrder = false;
            bool gotChef = false;

            switch (choice)
            {
            case 0:
                gotOrder = PEND_ODG.dequeue(ord);
                break;
            case 1:
                gotOrder = PEND_ODN.dequeue(ord);
                break;
            case 2:
                gotOrder = PEND_OT.dequeue(ord);
                break;
            case 3:
                gotOrder = PEND_OVN.dequeue(ord);
                break;
            case 4:
                gotOrder = PEND_OVC_List.dequeue(ord);
                break;
            case 5:
                gotOrder = PEND_OVG.dequeue(ord);
                break;
            }

            if (!gotOrder)
                continue;

            // get a chef
            if (rand() % 2 == 0)
                gotChef = Free_CN.dequeue(chef);
            else
                gotChef = Free_CS.dequeue(chef);

            if (!gotChef)
            {
                // if no chef available, put order back approximately
                switch (ord->GetType())
                {
                case TYPE_ODG:
                    PEND_ODG.enqueue(ord);
                    break;
                case TYPE_ODN:
                    PEND_ODN.enqueue(ord);
                    break;
                case TYPE_OT:
                    PEND_OT.enqueue(ord);
                    break;
                case TYPE_OVN:
                    PEND_OVN.enqueue(ord);
                    break;
                case TYPE_OVC:
                    PEND_OVC_List.enqueue(ord);
                    break;
                case TYPE_OVG:
                    PEND_OVG.enqueue(ord, rand() % 100 + 1);
                    break;
                }
                continue;
            }

            ord->AssignChef(chef);
            Cooking_Orders.enqueue(ord, rand() % 100 + 1);
        }

        // -------------------------------
        // Move from Cooking -> Ready
        // -------------------------------
        for (int i = 0; i < 2; i++)
        {
            Order* ord = nullptr;
            if (!Cooking_Orders.dequeue(ord))
                continue;

            switch (ord->GetType())
            {
            case TYPE_OT:
                RDY_OT.enqueue(ord);
                break;

            case TYPE_OVN:
            case TYPE_OVC:
            case TYPE_OVG:
                RDY_OV_List.enqueue(ord);
                break;

            case TYPE_ODG:
            case TYPE_ODN:
                RDY_OD.enqueue(ord);
                break;
            }
        }

        // -------------------------------
        // Move from Ready -> Finished / InService
        // -------------------------------
        for (int i = 0; i < 2; i++)
        {
            int choice = rand() % 3;
            Order* ord = nullptr;
            bool gotOrder = false;

            switch (choice)
            {
            case 0:
                gotOrder = RDY_OT.dequeue(ord);
                break;
            case 1:
                gotOrder = RDY_OV_List.dequeue(ord);
                break;
            case 2:
                gotOrder = RDY_OD.dequeue(ord);
                break;
            }

            if (!gotOrder)
                continue;

            // Takeaway goes directly to finished
            if (ord->GetType() == TYPE_OT)
            {
                Finished_Orders.push(ord);

                Chef* chef = ord->GetAssignedChef();
                if (chef)
                {
                    if (chef->GetType() == 'N')
                        Free_CN.enqueue(chef);
                    else
                        Free_CS.enqueue(chef);

                    ord->AssignChef(nullptr);
                }
            }
            else
            {
                // Delivery or Dine-in goes to In-Service
                InServ_Orders.enqueue(ord, rand() % 100 + 1);
            }
        }

        // -------------------------------
        // Move from In-Service -> Finished
        // -------------------------------
        for (int i = 0; i < 2; i++)
        {
            Order* ord = nullptr;
            if (!InServ_Orders.dequeue(ord))
                continue;

            Finished_Orders.push(ord);

            Chef* chef = ord->GetAssignedChef();
            if (chef)
            {
                if (chef->GetType() == 'N')
                    Free_CN.enqueue(chef);
                else
                    Free_CS.enqueue(chef);

                ord->AssignChef(nullptr);
            }
        }

        // Print current timestep
        PrintAll(timestep);

        std::cout << "\nPress Enter to continue...\n";
        std::cin.get();
    }
}

void Restaurant::RunSimulation()
{
    std::cout << "Starting Random Simulation...\n";
    RandomSimulator();
    std::cout << "\nSimulation Finished.\n";
}