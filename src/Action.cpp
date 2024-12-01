#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
#include "Settlement.h"
#include <iostream>
enum class SettlementType;
enum class FacilityCategory;

//---------------------------BaseAction---------------------------
BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::PENDING) {}
ActionStatus BaseAction::getStatus() const { return status; }
void BaseAction::complete() { status = ActionStatus::COMPLETED; }
void BaseAction::error(string errorMsg){
    this->errorMsg = errorMsg;
    status = ActionStatus::ERROR;
    std::cout << "Error: " << errorMsg << std::endl;
}
const string &BaseAction::getErrorMsg() const{
    return errorMsg;
}

//---------------------------SimulationStep---------------------------
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}
void SimulateStep::act(Simulation &simulation){
    if (numOfSteps <= 0){
        error("Invalid number of steps: " + std::to_string(numOfSteps));
    }
    for (int i = 1; i <= numOfSteps; i++){
        simulation.step();
    }
}
const string SimulateStep::toString() const{
    return "SimulateStep: " + std::to_string(numOfSteps) + " steps";
}
SimulateStep *SimulateStep::clone() const{
    
}

//---------------------------AddPlan---------------------------
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
settlementName(settlementName), selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    Settlement addToMe = Settlement(settlementName,איך אנחנו יודעים מה הסוג של הישוב);
    SelectionPolicy addMe = SelectionPolicy(איזה סוג של סלקשין ופליסי?);
    simulation.addPlan(addToMe,&addMe);
}

const string AddPlan::toString() const{
    return "AddPlan: The settlement is" + settlementName + " and the selection policy is" + selectionPolicy;
}
AddPlan *AddPlan::clone() const{

}


//---------------------------AddSettlement---------------------------
AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
    settlementName(settlementName), settlementType(settlementType){}

void act(Simulation &simulation){
    Settlement addMe = new Settlement(settlementName, settlementType);
    simulation.addSettlement(addMe);
}
AddSettlement *clone() const{

}
const string toString() const{
    return "The settlement name is" + settlementName + " and the type is" + Settlement::STtostring(settlementType);
}