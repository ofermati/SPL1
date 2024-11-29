#include "Simulation.h"

Simulation(const string &configFilePath)
    :isRunning(true){

    std::ifstream file(configFilePath); //לפתוח את הקובץ שקיבלנו
    if (!file.is_open()) { //לבדוק שהוא פתיח
        throw std::runtime_error("Unable to open config file: " + configFilePath); //not sure if needed
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0]==#) continue; //כדי להתעלם מהערות שהם הוסיפו

        std::istringstream ss(line); //אובייקט מיוחד שמאפשר לנו לחלץ מילה מילה מהשורה
        std::string type; //נאתחל משתנה שישמש לאחסון המילה שנחלץ בכל פעם מן השורה
        ss >> type; //שומר את המילה המחולצת כל פעם במשתנה TYPE

        if(type == "settlement"){
            std::string name;
            int SettlementType;
            ss >> name >> SettlementType;
        Settlement *settlement = new Settlement(name, static_cast<SettlementType>(settlementType)); //יוצרים ומוסיפים את היישוב לרשימת היישובים מבצעים קאסטינג כדי להפוך מint לenum
        // המרה סטטית היא כזו שקוראת בזמן כתיבת הקימפול לפני שהתכנית ממש רצה
        addSettlement(settlement);
        //  if (!addSettlement(settlement)) {
        //         delete settlement; //(אולי לא חייב) במקרה של כישלון, מוודאים שלא נשאר זיכרון יתום
        //     }
        }else if(type == "facility"){
            std::string name;
            int category;
            int price;
            int lifeq_impact;
            int eco_impact;
            int env_impact;
            ss >> name >> category >> price >> lifeq_impact >> eco_impact >>env_impact;
            FacilityType *facilityType = new FacilityType (name,static_cast<FacilityCategory>(category), price, lifeq_impact, eco_impact, env_impact);
            addFacility(facilityType);// הוספה לרשימת המתקנים
        }else if(type == "plan"){
            std::string settlement_name;
            std::string selection_policy;
            ss >> settlement_name >> selection_policy;
            // addPlan(getSettlement(settlement_name), policy);
        }else {
            std::cerr << "Unknown entry type in config file: " << type << std::endl;
        }
        }
        file.close();
    }