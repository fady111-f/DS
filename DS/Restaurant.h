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

// Forward Declaration عشان نمنع مشكلة الـ Circular Dependency
class Action;

class Restaurant
{
private:
    UI* pUI;

    // ==========================================================
    // 1. Action Lists (بناءً على الصورة)
    // ==========================================================
    LinkedQueue<Action*> RequestActions;  // Queue of actions for Request
    LinkedQueue<Action*> CancelActions;   // Queue for cancellation

    // ==========================================================
    // 2. Pending Orders -> 6 lists, a list for each type
    // ==========================================================
    LinkedQueue<Order*> PEND_ODG;
    LinkedQueue<Order*> PEND_ODN;
    LinkedQueue<Order*> PEND_OT;
    LinkedQueue<Order*> PEND_OVN;
    Pend_OVC PEND_OVC;
    PriQueue<Order*> PEND_OVG;

    // ==========================================================
    // 3. Available Chefs -> 2 lists, a list for each type
    // ==========================================================
    LinkedQueue<Chef*> Free_CS;
    LinkedQueue<Chef*> Free_CN;

    // ==========================================================
    // 4. Available Tables -> 3 lists
    // ==========================================================
    Fit_Tables Free_Tables;
    Fit_Tables Busy_Sharable;
    Fit_Tables Busy_No_Share;

    // ==========================================================
    // باقي القوائم الخاصة بالنظام (من الكود القديم بتاعك)
    // ==========================================================
    LinkedQueue<Order*> Cancelled_Orders;
    LinkedStack<Order*> Finished_Orders;
    Cook_Ords Cooking_Orders;
    LinkedQueue<Order*> RDY_OT;
    RDY_OV RDY_OVL;
    LinkedQueue<Order*> RDY_OD;
    PriQueue<Order*> InServ_Orders;
    PriQueue<Scooter*> Free_Scooters;
    PriQueue<Scooter*> Back_Scooters;
    LinkedQueue<Scooter*> Maint_Scooters;

public:
    Restaurant();
    ~Restaurant();

    // دوال إضافة الطلبات
    void add_odg(Order* o);
    void add_odn(Order* o);
    void add_ot(Order* o);
    void add_ovn(Order* o);
    void add_ovc(Order* o);
    // خليت الـ priority نوعها double عشان تقبل المعادلة اللي عملتها في RequestAction
    void add_ovg(Order* o, double priority);

    // دوال جديدة لإضافة الـ Actions للطوابير بتاعتها (هتحتاجها وقت قراءة الملف)
    void AddRequestAction(Action* pAction);
    void AddCancelAction(Action* pAction);

    // دوال المحاكاة الأساسية
    void PrintAll(int timestep);
    void RandomSimulator();
    void RunSimulation();
    void CancelOVC(int id);
};

#endif // RESTAURANT_H