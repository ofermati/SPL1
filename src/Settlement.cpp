#include "Settlement.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

Settlement::Settlement(const string &name, SettlementType type) 
    : name(name), type(type){}

const string &Settlement::getName() const{
    return name;
}

SettlementType Settlement::getType() const{
    return type;
}

const string Settlement::toString() const{
    return name + "settlement from type" + STtostring(type);  
}
//because its an enum its okay to pass by value
string Settlement::STtostring (SettlementType type) const{
    switch (type) {
        case SettlementType::VILLAGE: return "Village";
        case SettlementType::CITY: return "City";
        case SettlementType::METROPOLIS: return "Metropolis";
    }
    return "Unknown";
}