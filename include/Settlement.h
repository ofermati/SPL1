#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS,
};

class Settlement {
    public:
        Settlement(const string &name, SettlementType type);
        Settlement()=default;
        const string &getName() const;
        SettlementType getType() const;
        const string toString() const;
        string Settlement::STtostring (SettlementType type) const;

        private:
            const string name;
            SettlementType type;
};