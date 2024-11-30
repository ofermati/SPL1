#include "Simulation.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
using std::string;


Simulation::Simulation(const string &configFilePath)
    :isRunning(true), planCounter(0){

    std::ifstream file(configFilePath); //לפתוח את הקובץ שקיבלנו
    if (!file.is_open()) { //לבדוק שהוא פתיח
        throw std::runtime_error("Unable to open config file: " + configFilePath); //not sure if needed
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; //כדי להתעלם מהערות שהם הוסיפו או משורות ריקות

        std::istringstream ss(line); //אובייקט מיוחד שמאפשר לנו לחלץ מילה מילה מהשורה
        std::string type; //נאתחל משתנה שישמש לאחסון המילה שנחלץ בכל פעם מן השורה
        ss >> type; //שומר את המילה המחולצת כל פעם במשתנה TYPE

        if(type == "settlement"){
            std::string name;
            int settlementType;
            ss >> name >> SettlementType;
            Settlement *settlement = new Settlement(name, static_cast<SettlementType>(settlementType)); //יוצרים ומוסיפים את היישוב לרשימת היישובים מבצעים קאסטינג כדי להפוך מint לenum
            // המרה סטטית היא כזו שקוראת בזמן כתיבת הקימפול לפני שהתכנית ממש רצה
            addSettlement(settlement);
            //  if (!addSettlement(settlement)) {
            //       delete settlement; //(אולי לא חייב) במקרה של כישלון, מוודאים שלא נשאר זיכרון יתום
            //     }
        } else if (type == "facility") {
            std::string name;
            int category, price, lifeqImpact, ecoImpact, envImpact;
            ss >> name >> category >> price >> lifeqImpact >> ecoImpact >> envImpact;
            //הופך את מה שהתקבל מהמסמך למתקן ולאחר מכן מוסיף אותי
            FacilityType facility(name, static_cast<FacilityCategory>(category), price, lifeqImpact, ecoImpact, envImpact);
            addFacility(facility);

        } else if (type == "plan") {
            std::string settlementName, selectionPolicy;
            ss >> settlementName >> selectionPolicy;
            //הופך את מה שהתקבל לטיפוס הראוי
            Settlement& settlement = getSettlement(settlementName);
            SelectionPolicy* policy = ToSelectionPolicy(selectionPolicy);
            addPlan(settlement, policy);
        }else {
            std::cerr << "Unknown entry type in config file: " << type << std::endl;
        }
        }
        file.close();
    }

//turning string into selectionPolicy
SelectionPolicy* Simulation::ToSelectionPolicy(const string& str) {
    if (str == "nve") {
        return new NaiveSelection();
    } else if (str == "bal") {
        return new BalancedSelection();
    } else if (str == "eco") {
        return new EconomySelection();
    } else if (str == "env") {
        return new SustainabilitySelection();
    } else {
        throw std::runtime_error("Unknown selection policy: " + str);
    }
}
