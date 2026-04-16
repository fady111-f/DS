#include "Chef.h"

Chef::Chef(int id, char type) {
    this->id = id;
    this->type = type;
}

int Chef::GetID() const {
    return id;
}

char Chef::GetType() const
{
    return type;
}

void Chef::setType(char newType)
{
    type = newType;
}

std::ostream& operator<<(std::ostream& os, const Chef* chef) {
    if (chef != nullptr) {
        os << chef->GetID();
    }
    return os;
}