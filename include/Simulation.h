#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);

        //rule of 5:
        Simulation(const Simulation& other);
        Simulation(Simulation&& other);
        Simulation& operator=(const Simulation& other);
        Simulation& operator=(const Simulation&& other);

        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        bool isFacilityExists(FacilityType facility);
        Settlement *getSettlement(const string &settlementName);
        FacilityType *getFacility(const string &facilityName);
        Plan &getPlan(const int planID);
        void step();
        void close();
        void open();
        SelectionPolicy* ToSelectionPolicy(const string& str, int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        const string PrintTheLogs() const;
        int getplanCounter();

        ~Simulation();

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
};