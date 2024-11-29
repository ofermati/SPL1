#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Plan.h"
using std::vector;

//Constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
planId(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions), status(PlanStatus::AVALIABLE), life_quality_score(0), economy_score(0), environment_score(0){}

// Destructor
// Move Constructor
// Move Assignment Operator
// Copy Constructor
// Copy Assignment Operator

const int Plan::getlifeQualityScore() const {return life_quality_score;}

const int Plan::getEconomyScore() const {return economy_score;}

const int Plan::getEnvironmentScore() const {return environment_score;}

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {this->selectionPolicy = selectionPolicy;}

void Plan::step(){
    //כל עוד אפשר להוסיף מבנה לבניה
    while (status == PlanStatus::AVALIABLE){
        if (dynamic_cast<BalancedSelection*>(this->selectionPolicy) != nullptr){//לבדוק האם זה הכרחי פה
            this->selectionPolicy->setScores(life_quality_score, economy_score, environment_score);// צריכה לקבל גם את כל מה שבבנייה
        }
        Facility &selectedFacility = (this->selectionPolicy->selectFacility(&facilitiesOptions), this->settlement->getName());
        underConstruction.push_back(&selectedFacility);
        if (underConstruction.size() = this->settlement->getLimit()){
            this->status = PlanStatus::BUSY; 
        }
    }
    // בכל מקרה, צריך לעבוד על כל מי שבבניה ולעשות לו צעד
    for (Facility* it = underConstruction.begin(); it != underConstruction.end(); ) {
    Facility& fac = *it; 
    fac.step(); 
    //האם המתקן סיים בנייה
    if (fac.getStatus() == FacilityStatus::OPERATIONAL) {
        facilities.push_back(&fac);  
        it = underConstruction.erase(it); 
        Plan::scoreUpdate(&fec);
    } else {
        ++it; 
    }
    //יכול להיות שמישהו יצא מהוקטור ועכשיו ניתן להוסיף בנייה חדשה בצעד הבא
    if (underConstruction.size() < this->settlement->getLimit()) {
    this->status = PlanStatus::AVAILABLE;
}

void Plan::printStatus(){
    if (status == PlanStatus::AVALIABLE) {cout << "plan id: " << plan_id << "settlement: " << settlement <<  "Status: Available" << endl;}
    else {cout << "Status: Busy" << endl;}
 }
const vector<Facility*>& Plan::getFacilities() const{return facilities;}

void Plan::addFacility(Facility* facility){
    facilities.push_back(facility);
}

const string Plan::toString() const{
    string result = "PlanID: " + std::to_string(plan_id) + "\n";
    result += "SettlementName: " + settlement->getName() + "\n"; 
    result += "PlanStatus: " + (status == PlanStatus::AVALIABLE ? "AVALIABLE" : "BUSY") + "\n";
    result += "SelectionPolicy: " + selectionPolicy->toString() + "\n"; 
    result += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    result += "EconomyScore: " + std::to_string(economy_score) + "\n";
    result += "EnvironmentScore: " + std::to_string(environment_score) + "\n";
    for (const Facility* facility : facilities) {
        result += "FacilityName: " + facility->toString() + "\n";  
        result += "FacilityStatus: " + (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTION ? "UNDER_CONSTRUCTION" : "OPERATIONAL") + "\n"; // Assuming Facility has a getStatus method
    }
    return result;
}

void Plan::scoreUpdate(Facility* facility) {// our method
    this->life_quality_score = facility->getLifeQualityScore();
    this->economy_score = facility->getEconomyScore();  
    this->environment_score = facility->getEnvironmentScore();  
}