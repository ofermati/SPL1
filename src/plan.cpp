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
    , facilityOptions(facilityOptions) , status(PlanStatus::AVALIABLE),
    facilities(), underConstruction(), 
    life_quality_score(0) , economy_score(0) , environment_score(0)
    {}

Plan::Plan():
    Plan(-1, Settlement(), nullptr, {})
    {}

Plan::Plan(Plan &other)
    : plan_id(other.plan_id),
      settlement(other.settlement),
      selectionPolicy(other.selectionPolicy->clone()),
      facilityOptions(other.facilityOptions),
      status(other.status),
      life_quality_score(other.life_quality_score),
      economy_score(other.economy_score),
      environment_score(other.environment_score) {
    // Deep copy facilities
    for (auto facility : other.facilities) {
        facilities.push_back(new Facility(*facility));
    }
    // Deep copy underConstruction facilities
    for (auto facility : other.underConstruction) {
        underConstruction.push_back(new Facility(*facility));
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


void Plan::step(){
    if (status == PlanStatus::AVALIABLE){
        while( underConstruction.size() <= static_cast<int>(settlement.getType())+1){
            Facility newFac = Facility(selectionPolicy->selectFacility(facilityOptions),settlement.getName());
            underConstruction.push_back(&newFac);
        }
    }
    for(int i=0 ; i<=underConstruction.size(); i++ ){
            Facility* newFac = new Facility(selectionPolicy->selectFacility(facilityOptions),settlement.getName());
            underConstruction.push_back(newFac);
        }
    for(int i = underConstruction.size() - 1; i >= 0; i-- ){
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

//void Plan::addFacility(Facility* facility){
 //   !!!!!!!!!!
//}

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

            result += "FacilityStatus: OPERATIONAL\n";  // Corrected spelling
        for (const Facility* facility : underConstruction) {
            result += "FacilityName: " + facility->toString() + "\n";  
            result += "FacilityStatus: UNDER_CONSTRUCTION\n";  // Corrected spelling
        } 
    } else {
        result += "No facilities available.\n";  // Add a message if no facilities are present
    }
    return result;
}

Plan::~Plan() {
    delete selectionPolicy;
    for (auto facility : facilities) {
        delete facility;
    }
    for (auto facility : underConstruction) {
        delete facility;
    }
}

