#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::PrintState(
    int timestep,

    LinkedQueue<Order*>& PEND_ODG,
    LinkedQueue<Order*>& PEND_ODN,
    LinkedQueue<Order*>& PEND_OT,
    LinkedQueue<Order*>& PEND_OVN,
    LinkedQueue<Order*>& PEND_OVC,
    PriQueue<Order*>& PEND_OVG,

    LinkedQueue<Chef*>& Free_CS,
    LinkedQueue<Chef*>& Free_CN,

    PriQueue<Order*>& Cooking_Orders,

    LinkedQueue<Order*>& RDY_OT,
    LinkedQueue<Order*>& RDY_OV,
    LinkedQueue<Order*>& RDY_OD,

    PriQueue<Order*>& InServ_Orders,

    LinkedQueue<Order*>& Cancelled_Orders,
    LinkedStack<Order*>& Finished_Orders,

    PriQueue<Scooter*>& Free_Scooters,
    PriQueue<Scooter*>& Back_Scooters,
    LinkedQueue<Scooter*>& Maint_Scooters,

    PriQueue<Table*>& Free_Tables,
    PriQueue<Table*>& Busy_Sharable,
    PriQueue<Table*>& Busy_No_Share
)
{
    std::cout << "\n==============================\n";
    std::cout << "Current Timestep: " << timestep << "\n";
    std::cout << "==============================\n\n";

    std::cout << "---------- Pending Orders ----------\n";
    std::cout << "PEND_ODG (" << PEND_ODG.GetCount() << "): ";
    PEND_ODG.print();
    std::cout << "\n";

    std::cout << "PEND_ODN (" << PEND_ODN.GetCount() << "): ";
    PEND_ODN.print();
    std::cout << "\n";

    std::cout << "PEND_OT (" << PEND_OT.GetCount() << "): ";
    PEND_OT.print();
    std::cout << "\n";

    std::cout << "PEND_OVN (" << PEND_OVN.GetCount() << "): ";
    PEND_OVN.print();
    std::cout << "\n";

    std::cout << "PEND_OVC (" << PEND_OVC.GetCount() << "): ";
    PEND_OVC.print();
    std::cout << "\n";

    std::cout << "PEND_OVG (" << PEND_OVG.GetCount() << "): ";
    PEND_OVG.print();
    std::cout << "\n\n";

    std::cout << "---------- Free Chefs ----------\n";
    std::cout << "Free_CS (" << Free_CS.GetCount() << "): ";
    Free_CS.print();
    std::cout << "\n";

    std::cout << "Free_CN (" << Free_CN.GetCount() << "): ";
    Free_CN.print();
    std::cout << "\n\n";

    std::cout << "---------- Cooking Orders ----------\n";
    std::cout << "Cooking_Orders (" << Cooking_Orders.GetCount() << "): ";
    Cooking_Orders.print();
    std::cout << "\n\n";

    std::cout << "---------- Ready Orders ----------\n";
    std::cout << "RDY_OT (" << RDY_OT.GetCount() << "): ";
    RDY_OT.print();
    std::cout << "\n";

    std::cout << "RDY_OV (" << RDY_OV.GetCount() << "): ";
    RDY_OV.print();
    std::cout << "\n";

    std::cout << "RDY_OD (" << RDY_OD.GetCount() << "): ";
    RDY_OD.print();
    std::cout << "\n\n";

    std::cout << "---------- In-Service Orders ----------\n";
    std::cout << "InServ_Orders (" << InServ_Orders.GetCount() << "): ";
    InServ_Orders.print();
    std::cout << "\n\n";

    std::cout << "---------- Cancelled / Finished ----------\n";
    std::cout << "Cancelled_Orders (" << Cancelled_Orders.GetCount() << "): ";
    Cancelled_Orders.print();
    std::cout << "\n";

    std::cout << "Finished_Orders (" << Finished_Orders.GetCount() << "): ";
    Finished_Orders.print();
    std::cout << "\n\n";

    std::cout << "---------- Scooters ----------\n";
    std::cout << "Free_Scooters (" << Free_Scooters.GetCount() << "): ";
    Free_Scooters.print();
    std::cout << "\n";

    std::cout << "Back_Scooters (" << Back_Scooters.GetCount() << "): ";
    Back_Scooters.print();
    std::cout << "\n";

    std::cout << "Maint_Scooters (" << Maint_Scooters.GetCount() << "): ";
    Maint_Scooters.print();
    std::cout << "\n\n";

    std::cout << "---------- Tables ----------\n";
    std::cout << "Free_Tables (" << Free_Tables.GetCount() << "): ";
    Free_Tables.print();
    std::cout << "\n";

    std::cout << "Busy_Sharable (" << Busy_Sharable.GetCount() << "): ";
    Busy_Sharable.print();
    std::cout << "\n";

    std::cout << "Busy_No_Share (" << Busy_No_Share.GetCount() << "): ";
    Busy_No_Share.print();
    std::cout << "\n";

    std::cout << "\n========================================\n";
}