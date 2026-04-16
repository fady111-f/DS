#ifndef CHEF_H
#define CHEF_H

#include <iostream>

class Chef {
private:
    int id;
    char type; // 'N' for Normal, 'S' for VIP/Special, etc.

public:
    Chef(int id, char type);
    int GetID() const;
    char GetType() const;
    void setType(char newType);
};

// Overloading << to print the Chef ID easily
std::ostream& operator<<(std::ostream& os, const Chef* chef);

#endif // CHEF_H