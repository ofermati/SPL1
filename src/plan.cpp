#pragma once
#include "Plan.h"
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>  // for cout
using namespace std; // to use cout directly without std::
using std::vector;

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
    plan_id(planId) , settlement(settlement) , selectionPolicy(selectionPolicy) 
    ,status(PlanStatus::AVALIABLE), facilityOptions(facilityOptions) ,
    facilities(), underConstruction(), 
    life_quality_score(0) , economy_score(0) , environment_score(0), withUnderQUA(0), withUnderScoreECO(0), withUnderENVI(0)
    {}

Plan::Plan():
    Plan(-1, Settlement(), nullptr, {})
    {}


Plan::Plan(const Plan &other):
    Plan(other.plan_id, other.settlement, other.selectionPolicy->clone(), other.facilityOptions){
    status= other.status;
    life_quality_score=other.life_quality_score;
    economy_score=other.economy_score;
    environment_score=other.environment_score;
    // Deep copy facilities
    for (auto facility : other.facilities) {
        facilities.push_back(new Facility(*facility));
    }
    // Deep copy underConstruction facilities
    for (auto facility : other.underConstruction) {
        underConstruction.push_back(new Facility(*facility));
    }
}

Plan::Plan(Plan&& other)
: Plan(other.plan_id, other.settlement, other.selectionPolicy->clone(), other.facilityOptions){
    status= other.status;
    life_quality_score=other.life_quality_score;
    economy_score=other.economy_score;
    environment_score=other.environment_score;
    facilities = other.facilities;
    underConstruction = other.underConstruction;

    other.selectionPolicy = nullptr;//deleting other
    for(Facility* fac : other.underConstruction){
        fac = nullptr;
    }
    for(Facility* fac : other.facilities){
        fac = nullptr;
    }
}

const int Plan::getlifeQualityScore() const{
    return life_quality_score;
}

const int Plan::getEconomyScore() const{
    return economy_score;
}

const int Plan::getEnvironmentScore() const{
    return environment_score;
}

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
    this->selectionPolicy = selectionPolicy;
}

void Plan::step() {
    if (status == PlanStatus::AVALIABLE) {
        size_t maxFacilities = static_cast<size_t>(settlement.getType()) + 1; 
        while (underConstruction.size() < maxFacilities && !facilityOptions.empty()) {
            Facility *newFac = new Facility(selectionPolicy->selectFacility(facilityOptions), settlement.getName());
            addFacility(newFac);
            withUnderENVI = withUnderENVI + newFac->getEnvironmentScore();
            withUnderQUA = withUnderQUA + newFac->getLifeQualityScore();
            withUnderScoreECO = withUnderScoreECO + newFac->getEconomyScore();
        }
    }
    for (int i = underConstruction.size() - 1; i >= 0; i--) {
        if (underConstruction[i]->step() == FacilityStatus::OPERATIONAL) {
            Facility* completedFacility = underConstruction[i];
            underConstruction.erase(underConstruction.begin() + i);//לוודא שלא יהיה בטעות ב2 הרשימות ויצור מחיקה כפולה שלו בסוף
            addFacility(completedFacility);
            life_quality_score = life_quality_score + completedFacility->getLifeQualityScore();
            economy_score = economy_score + completedFacility->getEconomyScore();
            environment_score = environment_score + completedFacility->getEnvironmentScore();
        }
    }
    if (underConstruction.size() == static_cast<int>(settlement.getType()) + 1) {
        status = PlanStatus::BUSY;
    } else {
        status = PlanStatus::AVALIABLE;
    }
}

std::string  Plan::PlanStatusToString(PlanStatus status) {
    switch (status) {
        case PlanStatus::AVALIABLE:
            return "Available";
        case PlanStatus::BUSY:
            return "Busy";
        default:
            return "Unknown";
    }
}

void Plan::printStatus() {
    std::string output;
    output += "PlanID: " + std::to_string(plan_id) + "\n";
    output += "Settlement Name: " + settlement.getName() + "\n";
    output += "Plan Status: " + PlanStatusToString(status) + "\n";
    output += "SelectionPolicy: " + selectionPolicy->getName() + "\n";
    output += "LifeQualityScore: " + std::to_string(getlifeQualityScore()) + "\n";
    output += "EconomyScore: " + std::to_string(getEconomyScore()) + "\n";
    output += "EnvironmentScore: " + std::to_string(getEnvironmentScore()) + "\n";

    for (Facility *fac : facilities) {
        output += "Facility: " + fac->getName() + " - OPERATIONAL\n";
    }

    for (Facility *fac : underConstruction) {
        output += "Facility: " + fac->getName() + " - UNDER CONSTRUCTION\n";
    }

    std::cout << output;
}



const vector<Facility *> &Plan::getFacilities() const{
    return facilities;
}

void Plan::addFacility(Facility* facility) {
    if (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS) {
        underConstruction.push_back(facility);
    } else if (facility->getStatus() == FacilityStatus::OPERATIONAL) {
        facilities.push_back(facility);
    } else { //למנוע שגיאות
        cout << "Unknown Facility status!" << endl;
    }
}

const int Plan::getPlanId() const{
    return plan_id;
}

const Settlement& Plan::getSttlement() const{
    return settlement;
}

const SelectionPolicy* Plan::getSelectionPolicy() const{
    return selectionPolicy;
}

const string Plan::toString() const{
    string result = "PlanID: " + std::to_string(plan_id) + "\n";
    result += "SettlementName: " + settlement.getName() + "\n";
    result += "PlanStatus: " + std::string((status == PlanStatus::AVALIABLE ? "AVAILABLE" : "BUSY")) + "\n";
    result += "SelectionPolicy: " + selectionPolicy->toString() + "\n";
    result += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    result += "EconomyScore: " + std::to_string(economy_score) + "\n";
    result += "EnvironmentScore: " + std::to_string(environment_score) + "\n";

    // Checking if facilities or underConstruction is not empty before looping through it
    if (!facilities.empty() || !underConstruction.empty()) {
        for (const Facility* facility : facilities) {
            result += "FacilityName: " + facility->toString() + "\n";  
            result += "FacilityStatus: OPERATIONAL\n";

        }
        for (const Facility* facility : underConstruction) {
            result += "FacilityName: " + facility->toString() + "\n";  
            result += "FacilityStatus: UNDER_CONSTRUCTION\n"; 
        }
    }else{
        result += "No facilities available.\n";  // Add a message if no facilities are present
    }
    return result;
}

Plan::~Plan() {
    for (Facility* facility : facilities) {
        delete facility;
    }
    for (Facility* facility : underConstruction) {
        delete facility;
    }
    delete selectionPolicy;
}
