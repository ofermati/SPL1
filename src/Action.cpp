#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
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

