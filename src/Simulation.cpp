#include "Simulation.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Auxiliary.cpp"
#include "Action.cpp"

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
            if (line.size() != 3){
                throw std::runtime_error("Elegal settlement in config file.");
            }
            std::string name;
            int settlementType;
            ss >> name >> settlementType;
            Settlement *settlement = new Settlement(name, static_cast<SettlementType>(settlementType)); //יוצרים ומוסיפים את היישוב לרשימת היישובים מבצעים קאסטינג כדי להפוך מint לenum
            // המרה סטטית היא כזו שקוראת בזמן כתיבת הקימפול לפני שהתכנית ממש רצה
            addSettlement(settlement);
            //  if (!addSettlement(settlement)) {
            //       delete settlement; //(אולי לא חייב) במקרה של כישלון, מוודאים שלא נשאר זיכרון יתום
            //     }
        } else if (type == "facility") {
            if (line.size() != 7){
                throw std::runtime_error("Elegal facility in config file.");
            }           
            std::string name;
            int category, price, lifeqImpact, ecoImpact, envImpact;
            ss >> name >> category >> price >> lifeqImpact >> ecoImpact >> envImpact;
            //הופך את מה שהתקבל מהמסמך למתקן ולאחר מכן מוסיף אותי
            FacilityType facility(name, static_cast<FacilityCategory>(category), price, lifeqImpact, ecoImpact, envImpact);
            addFacility(facility);

        } else if (type == "plan") {
            if (line.size() != 3){
                throw std::runtime_error("Elegal plan in config file.");
            }
            std::string settlementName, selectionPolicy;
            ss >> settlementName >> selectionPolicy;
            //הופך את מה שהתקבל לטיפוס הראוי
            Settlement& settlement = getSettlement(settlementName);
            SelectionPolicy* policy = ToSelectionPolicy(selectionPolicy, 0, 0, 0);
            addPlan(settlement, policy);
        }else {
            std::cerr << "Unknown entry type in config file: " << type << std::endl;
        }
        }
        file.close();
    }

//turning string into selectionPolicy
SelectionPolicy* Simulation::ToSelectionPolicy(const string& str, int LifeQualityScore, int EconomyScore, int EnvironmentScore) {
    if (str == "nve") {
        return new NaiveSelection();
    } else if (str == "bal") {
        return new BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
    } else if (str == "eco") {
        return new EconomySelection();
    } else if (str == "env") {
        return new SustainabilitySelection();
    } else {
        return nullptr;}
}

void Simulation::start(){
    open();
    while(isRunning){
        string line;
        std::cin >> line;
        vector<string> inputs = Auxiliary::parseArguments(line);

        if(inputs[0] == "step"){
            const int steps = std::stoi(inputs[1]);
            BaseAction *step = new SimulateStep(steps);
            step->act(*this);
            actionsLog.push_back(step);
        }

        if(inputs[0] == "plan"){
            const string settName = (inputs[1]);
            const string secPol = (inputs[2]);
            BaseAction *newPlan = new AddPlan(settName, secPol);
            newPlan->act(*this);
            actionsLog.push_back(newPlan);
        }        

        if(inputs[0] == "settlement"){
            const string settName = (inputs[1]);
            SettlementType settType = (static_cast<SettlementType>(std::stoi(inputs[2])));
            BaseAction *newSett = new AddSettlement(settName, settType);            
            newSett->act(*this);
            actionsLog.push_back(newSett);
        }

        if(inputs[0] == "facility"){
            const string facilityName = (inputs[1]);
            const FacilityCategory facilityCategory = (static_cast<FacilityCategory>(std::stoi(inputs[2])));
            const int price = std::stoi(inputs[3]);
            const int lifeQualityScore = std::stoi(inputs[4]);
            const int economyScore = std::stoi(inputs[5]);
            const int environmentScore = std::stoi(inputs[6]);
            BaseAction *newFaci = new AddFacility(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
            newFaci->act(*this);
            actionsLog.push_back(newFaci);
        }

        if(inputs[0] == "planStatus"){
            int planId = std::stoi(inputs[1]);
            BaseAction *printPlan = new PrintPlanStatus(planId);
            printPlan->act(*this);
            actionsLog.push_back(printPlan);
        }

        if(inputs[0] == "changePolicy"){
            const int planID = std::stoi(inputs[1]);
            const string newPol = (inputs[2]);
            BaseAction *ChangePol = new ChangePlanPolicy(planID, newPol);
            ChangePol->act(*this);
            actionsLog.push_back(ChangePol);
        }

        if(inputs[0] == "log"){
            BaseAction *printLog = new PrintActionsLog();
            printLog->act(*this);
            actionsLog.push_back(printLog);
        }

        if(inputs[0] == "close"){
            BaseAction *close = new Close();
            close->act(*this);
            actionsLog.push_back(close);
        }

        if(inputs[0] == "backup"){
            BaseAction *backUp = new BackupSimulation();
            backUp->act(*this);
            actionsLog.push_back(backUp);
        }        

        if(inputs[0] == "restore"){
            BaseAction *restore = new RestoreSimulation();
            restore->act(*this);
            actionsLog.push_back(restore);
        }

        //מניחים שכל הפקודות חוקיות ולכן אין else
    }
}

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    if(!isSettlementExists(settlement.getName())){
        throw std::runtime_error("Cannot create this plan.");//לפי מה שכתבו בעבודה
    }
    plans.emplace_back(Plan(planCounter, settlement, selectionPolicy, facilitiesOptions));//בגלל שיוצרים חדש עשיתי EMPLACE
    planCounter++;
}

void Simulation::addAction(BaseAction *action){
    actionsLog.push_back(action);
}

bool Simulation::addSettlement(Settlement *settlement){
    if(!isSettlementExists(settlement->getName())){
        return false;
    }
    settlements.emplace_back(new Settlement(settlement->getName(), settlement->getType()));
    return true;
}

 bool Simulation::addFacility(FacilityType facility){
    if(isFacilityExists(facility)){
        throw std::runtime_error("Facility already exists.");
    }
    facilitiesOptions.push_back(facility);
 }

 bool Simulation::isSettlementExists(const string &settlementName){
    for(const Settlement* sett : settlements){
        if(sett->getName() == settlementName){
            return true;
        }
    }
    return false;
 }

 bool Simulation::isFacilityExists(FacilityType facility){
    for(FacilityType faci : facilitiesOptions){
        if(faci.getName() == facility.getName()){
            return true;
        }
    }
    return false;   
 }

Settlement *Simulation::getSettlement(const string &settlementName){
    for(Settlement* sett : settlements){
        if((*sett).getName() == settlementName){
            return *sett;
        }
    }
    return nullptr;);
}

Plan &Simulation::getPlan(const int planID){
    for (Plan curr : plans){
        if(curr.getPlanId() == planID){
            return curr;
        }
    }
    return nullptr;
}

void Simulation::step(){
    for(Plan plan : plans){
        plan.step();
    }
}

void Simulation::open(){
    isRunning=true;
}

void Simulation::close(){
    for (Plan plan : plans) {
        string output = "planID: " + std::to_string(plan.getPlanId()) + "\n";
        output += "Settlement: " + (plan.getSttlement().toString()) + "\n";
        output += "LifeQuality_Score: " + std::to_string(plan.getlifeQualityScore()) + "\n";
        output += "Economy_Score: " + std::to_string(plan.getEconomyScore()) + "\n";
        output += "Environment_Score: " + std::to_string(plan.getEnvironmentScore()) + "\n";

    isRunning = false ;
    
    for (Settlement *settlement : settlements){
        delete settlement;
    }
    settlements.clear();
    
    for (Plan plan : plans){
        delete plan.getSelectionPolicy();
    }
    plans.clear();
    facilitiesOptions.clear();

    //Actionlog need to delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
