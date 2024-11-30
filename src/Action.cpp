#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
using std::string;
using std::vector;
enum class SettlementType;
enum class FacilityCategory;

//Constructor
BaseAction::BaseAction(): errorMsg(""), status(ActionStatus::PENDING){}
ActionStatus BaseAction::getStatus() const{return status;}
void BaseAction::complete(){status = ActionStatus::COMPLETED;}
void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg; 
    cout << "Error: " << errorMsg << endl; 
}
const string &BaseAction::getErrorMsg() const{
    return errorMsg;
    





//Constructor
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps){}

void SimulateStep::act(Simulation &simulation) {
    if (numOfSteps <= 0) {
            error("Invalid number of steps: " + std::to_string(numOfSteps));
            return;
        }
    for (int i = 1; i <= numOfSteps; i++){
        simulation.step();
    }
}
const string SimulateStep::toString() const {
    return "SimulateStep: " + std::to_string(numOfSteps) + " steps";
}
SimulateStep* SimulateStep::clone() const {return new SimulateStep(*this);}