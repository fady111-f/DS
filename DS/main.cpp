#include "Restaurant.h"

int main() {
    // Create the Restaurant object
    Restaurant* pRest = new Restaurant();

    // Start the simulation
    pRest->RandomSimulator();

    // Clean up
  
	delete pRest;
    return 0;
}