#pragma once
#include "Plan.h"
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>  // for cout
using namespace std;  // to use cout directly without std::
using std::vector;

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
    plan_id(planId) , settlement(settlement) , selectionPolicy(selectionPolicy) 
    , facilityOptions(facilityOptions) , status(PlanStatus::AVALIABLE) //האם צריך את שאר השדות לאתחל כרשימות ריקות 
    , life_quality_score(0) , economy_score(0) , environment_score(0)
    {}

Plan& Plan::operator=(const Plan& other) {
    if (this == &other) { // Self-assignment check
        return *this; // Return the current object as a reference
    }

    // Clean up existing resources
    delete selectionPolicy;
    for (auto facility : facilities) {
        delete facility;
    }
    facilities.clear();
    for (auto facility : underConstruction) {
        delete facility;
    }
    underConstruction.clear();

    // Copy non-heap members
    this->plan_id = other.plan_id;
    this->status = other.status;
    this->life_quality_score = other.life_quality_score;
    this->economy_score = other.economy_score;
    this->environment_score = other.environment_score;
    this->facilityOptions = other.facilityOptions;

    // Deep copy the selectionPolicy
    if (other.selectionPolicy) {
        this->selectionPolicy = other.selectionPolicy->clone();
    } else {
        this->selectionPolicy = nullptr;
    }

    // Deep copy facilities
    for (auto facility : other.facilities) {
        this->facilities.push_back(new Facility(*facility));
    }

    // Deep copy underConstruction facilities
    for (auto facility : other.underConstruction) {
        this->underConstruction.push_back(new Facility(*facility));
    }
    
    return *this; // Return the current object as a reference
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


void Plan::step(){
    if (status == PlanStatus::AVALIABLE){
        while( underConstruction.size() <= static_cast<int>(settlement.getType())+1){
            Facility newFac = Facility(selectionPolicy->selectFacility(facilityOptions),settlement.getName());
            underConstruction.push_back(&newFac);
        }
    }
    for(int i=0 ; i<=underConstruction.size(); i++ ){
        if (underConstruction[i]->step() == FacilityStatus::OPERATIONAL){
            facilities.push_back(underConstruction[i]);
            underConstruction.erase(underConstruction.begin()+i);
        }
    }
    if (underConstruction.size() == static_cast<int>(settlement.getType())+1){
        status = PlanStatus::BUSY;
    }else {
        status = PlanStatus::AVALIABLE;
    }
}

void Plan::printStatus() {
    string output;
    if (status == PlanStatus::AVALIABLE)
        output = "Available";
    else
        output = "Busy";
    cout << output;
}

const vector<Facility*> &Plan::getFacilities() const{
    return facilities;
}

void Plan::addFacility(Facility* facility){
    !!!!!!!!!!
}

const string Plan::toString() const {
    string result = "PlanID: " + std::to_string(plan_id) + "\n";
    result += "SettlementName: " + settlement.getName() + "\n"; 
    result += "PlanStatus: " + std::string((status == PlanStatus::AVALIABLE ? "AVAILABLE" : "BUSY")) + "\n";
    result += "SelectionPolicy: " + selectionPolicy->toString() + "\n"; 
    result += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    result += "EconomyScore: " + std::to_string(economy_score) + "\n";
    result += "EnvironmentScore: " + std::to_string(environment_score) + "\n";
    
    // Checking if facilities is not empty before looping through it
    if (!facilities.empty()) {
        for (const Facility* facility : facilities) {
            result += "FacilityName: " + facility->toString() + "\n";  
            result += "FacilityStatus: " + std::string((facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS ? "UNDER_CONSTRUCTION" : "OPERATIONAL")) + "\n";  // Corrected spelling
        }
    } else {
        result += "No facilities available.\n";  // Add a message if no facilities are present
    }

    return result;