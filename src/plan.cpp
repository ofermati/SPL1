#pragma once
#include "Plan.h"
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
    plan_id(planId) , settlement(settlement) , selectionPolicy(selectionPolicy) 
    , facilityOptions(facilityOptions) , status(PlanStatus::AVALIABLE) , facilities(12) , underConstruction(static_cast<int>(settlement.getType())+1)))
    , life_quality_score(0) , economy_score(0) , environment_score(0)
    {}



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
!!!!!!!!!!
}


void Plan::step(){
    if (status == PlanStatus::AVALIABLE){
        while( underConstruction.size() <= static_cast<int>(settlement.getType())+1){
            Facility newFac = Facility(selectionPolicy->selectFacility(facilityOptions),settlement.getName());
            addFacility(&newFac);
        }
    }
    for()
}

void Plan::printStatus(){
    return status;
}
const vector<Facility*> &Plan::getFacilities() const{

}
void Plan::addFacility(Facility* facility){

}
const string Plan::toString() const{

}