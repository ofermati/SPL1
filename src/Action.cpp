#pragma once
#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
#include "Settlement.h"
#include <iostream>
using std::string;
enum class SettlementType;
enum class FacilityCategory;
extern Simulation* backup;

//---------------------------BaseAction---------------------------לבדוק אם צריך
BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::PENDING) {}

ActionStatus BaseAction::getStatus() const {
    return status; 
}

void BaseAction::complete() {
    status = ActionStatus::COMPLETED; 
}

void BaseAction::error(string errorMsg){
    this->errorMsg = errorMsg;
    status = ActionStatus::ERROR;
    std::cout << "Error: " << errorMsg << std::endl;
}

const string &BaseAction::getErrorMsg() const{
    return errorMsg;
}

const string BaseAction::StatToST(ActionStatus status) const {
    if(status==ActionStatus::ERROR){
        return "ERROR";
    }
    else{
        return "COMPLETED";
    }
}

//---------------------------SimulationStep---------------------------

SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}

void SimulateStep::act(Simulation &simulation){
    for (int i = 1; i <= numOfSteps; i++){//הייתה הערה שמחקתי כי אמרו שמותר להניח שמספר הצעדים גדול מ0
        simulation.step();//קורא לסטפ של סימוליישן שקורה לספט של פלאנ שקורה לסטפ של פסיליטי ששם באמת מתבצע הסטפ
    }
    complete();
}

const string SimulateStep::toString() const{//צריך שנייה לדבר על מה נדפיס כי בהוראות כתוב בדיוק מה צריך להדפיס
<<<<<<< HEAD
    return "step" + std::to_string(numOfSteps) + StatToST(getStatus());
=======
    return "step" + std::to_string(numOfSteps) + BaseAction::StatToST(getStatus());
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
}

SimulateStep *SimulateStep::clone() const{//לא הבנתי למה צריך קלון או אם זה נכון אבל נזרום
    return new SimulateStep(*this);
}



//---------------------------AddPlan---------------------------//

AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
settlementName(settlementName), selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    Settlement *sett = simulation.getSettlement(settlementName);
<<<<<<< HEAD
    SelectionPolicy *policy = simulation.ToSelectionPolicy(selectionPolicy, 0, 0, 0); 
    if(sett == nullptr || policy == nullptr){
       error("”Cannot create this plan”");
=======
    SelectionPolicy *policy = simulation.ToSelectionPolicy(selectionPolicy); 
    if(sett == nullptr | policy == nullptr){
       error(getErrorMsg());
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
    }
    simulation.addPlan(*sett, policy);
    complete();  //הייתי צריכה לכלול את סימוליישנ בשביל שזה יעבוד אז מקווה שזה לא יעשה בעיות עם פרגמה וואנ ס וכאלה
}

const string AddPlan::toString() const{
<<<<<<< HEAD
    return "plan" + settlementName + selectionPolicy + StatToST(getStatus());
=======
    return "plan" + settlementName + selectionPolicy + BaseAction::StatToST(getStatus());
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
}

AddPlan *AddPlan::clone() const{
    return new AddPlan(*this);
}

<<<<<<< HEAD


=======
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
//---------------------------AddSettlement---------------------------

AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
    settlementName(settlementName), settlementType(settlementType){}

void AddSettlement::act(Simulation &simulation){
<<<<<<< HEAD

    Settlement *addMe = simulation.getSettlement(settlementName);
    if(addMe != nullptr){
       error("”Settlement already exists”");
    }
    simulation.addSettlement(addMe);
    complete();
}

AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(*this);
}

const string AddSettlement::toString() const{
    return "settlement" + settlementName + std::to_string(static_cast<int>(settlementType)) + BaseAction::StatToST(getStatus());
}

=======
    Settlement *addMe = new Settlement(settlementName, settlementType);
    if(addMe == nullptr){
        error(getErrorMsg());  
    }
    simulation.addSettlement(addMe);
}
AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(*this);
}
const string AddSettlement::toString() const{
    return "settlement" + settlementName + std::to_string(static_cast<int>(settlementType)) + BaseAction::StatToST(getStatus());
}

>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
//---------------------------AddFacility---------------------------

 AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
 facilityName(facilityName), facilityCategory(facilityCategory), price(price),
<<<<<<< HEAD
 lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore){}

void AddFacility::act(Simulation &simulation) {
    FacilityType *addMe = simulation.getFacility(facilityName);
    if (addMe != nullptr){
       error("Facility already exist");
=======
 lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore)
 {}
       
             
void AddFacility::act(Simulation &simulation) {
    FacilityType *addMe = new FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    if (addMe == nullptr){
       error(getErrorMsg()); 
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
    }
    simulation.addFacility(*addMe);
    string output = "The facility name is" + facilityName + " it category is" + addMe->categoryToString(facilityCategory) + " the price is" + std::to_string(price) + '\n';
    output += "life quality score" + std::to_string(lifeQualityScore) + '\n';
    output += "life economy score" + std::to_string(economyScore) + '\n';
    output += "life enviromnet score" + std::to_string(environmentScore) + '\n';
<<<<<<< HEAD
    complete();
    std::cout << output << std::endl;
=======
    cout << output << endl;
}

AddFacility *AddFacility::clone() const {
    return new AddFacility(*this);
}

const string AddFacility::toString() const {
    return "facility" + facilityName + std::to_string(static_cast<int>(facilityCategory)) + 
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
}

AddFacility *AddFacility::clone() const {
    return new AddFacility(*this);
}

const string AddFacility::toString() const {
    return "facility" + facilityName + std::to_string(static_cast<int>(facilityCategory)) + std::to_string(price) +std::to_string(lifeQualityScore) + std::to_string(economyScore) + std::to_string(environmentScore) + BaseAction::StatToST(getStatus());
}

//---------------------------PrintPlanStatus---------------------------
<<<<<<< HEAD

PrintPlanStatus::PrintPlanStatus(int planId): planId(planId){}

void PrintPlanStatus::act(Simulation &simulation) {
    simulation.getPlan(planId);
    if (planId < 0 || planId >= simulation.getplanCounter()) {//the id is not legal
        error("Plan doesn’t exist");
    }
    complete();
    simulation.getPlan(planId).printStatus();
=======
 PrintPlanStatus::PrintPlanStatus(int planId): planId(planId){}

void PrintPlanStatus::act(Simulation &simulation) {
    simulation.getPlan(planId);
        if (plan.getId() == nullptr){
        error(getErrorMsg());
        }
    plan.printStatus();
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
}

PrintPlanStatus *PrintPlanStatus::clone() const {
    return new PrintPlanStatus(*this);
}

const string PrintPlanStatus::toString() const {
<<<<<<< HEAD
    return "plan" + BaseAction::StatToST(getStatus());
=======
    return "this is plan number" + std::to_string(planId); //אולי ממש להוסיף את הסטטוס של הפלאן וכו
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
}

//---------------------------ChangePlanPolicy---------------------------
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy) : planId(planId), newPolicy(newPolicy){}

void ChangePlanPolicy::act(Simulation &simulation){
    Plan &plan = simulation.getPlan(planId);
    if (planId < 0 || planId >= simulation.getplanCounter()) {//the id is not legal
        error("Cannot change selection policy");
    }
    if(newPolicy == plan.getSelectionPolicy()->getName()){
        error("Cannot change selection policy");
    }
    string prev = plan.getSelectionPolicy()->getName();
    delete plan.getSelectionPolicy();//לוודא שזה באמת מוחק ושלא צריך להעביר את זה למחלקה סימוליישן ששם יצרנו את הסלקשן פוליסי
<<<<<<< HEAD
    plan.setSelectionPolicy(simulation.ToSelectionPolicy(newPolicy, plan.GetwithUnderQUA(), plan.GetwithUnderScoreECO(), plan.GetwithUnderENVI()));
    string output = std::to_string(plan.getPlanId()) + '\n';
    output += "previous Policy: " + prev + '\n';
    output += "new Policy: " + plan.getSelectionPolicy()->getName();
    complete();
=======
    plan.setSelectionPolicy(Simulation::ToSelectionPolicy(newPolicy, plan.GetwithUnderQUA(), plan.GetwithUnderScoreECO(), plan.GetwithUnderENVI()));
    string output = std::to_string(plan.getPlanId()) + '/n' + "previous Policy:" + prev +'/n' + "new Policy:" + plan.getSelectionPolicy()->getName();
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
    std::cout << output << std::endl;
}

ChangePlanPolicy *ChangePlanPolicy::clone() const{
    return new ChangePlanPolicy(*this);
}
<<<<<<< HEAD

const string ChangePlanPolicy::toString() const{
    return "changePolisy" + std::to_string(planId) + newPolicy + BaseAction::StatToST(getStatus());
}

=======
       
const string ChangePlanPolicy::toString() const{
    return "the plan number is" + std::to_string(planId) + "and the new policy is" + newPolicy;
}
>>>>>>> 58550330e11e908024ac43a3bde6b53e12290482
//---------------------------PrintActionsLog---------------------------
PrintActionsLog::PrintActionsLog() {}

void PrintActionsLog::act(Simulation &simulation){
    complete();
    string output= simulation.PrintTheLogs();
    std::cout << output << std::endl;
}

PrintActionsLog *PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);
}

const string PrintActionsLog::toString() const{
    return "log" + BaseAction::StatToST(getStatus());
}

//---------------------------Close---------------------------
Close::Close(){}

void Close::act(Simulation &simulation){
    complete();
    simulation.close();
}

Close *Close::clone() const{
    return new Close(*this);
}

const string Close::toString() const{
    return "close" + BaseAction::StatToST(getStatus());
}


//---------------------------Close---------------------------
BackupSimulation::BackupSimulation(){}

void BackupSimulation::act(Simulation &simulation) {
    // if the backup has a simulation we need to delete it first
    if (backup != nullptr) {
        delete backup; 
    }
    backup = new Simulation(simulation);   
    complete();
}

BackupSimulation *BackupSimulation::clone() const{
    return new BackupSimulation(*this);
}

const string BackupSimulation::toString() const{
    return "backup" + BaseAction::StatToST(getStatus());
}

//---------------------------Close---------------------------
RestoreSimulation::RestoreSimulation(){}

void RestoreSimulation::act(Simulation &simulation) {
    if (backup == nullptr) {
        error("No backup available");
    } else {
        simulation = *backup;
        complete();
    }

}

RestoreSimulation *RestoreSimulation::clone() const{
    return new RestoreSimulation(*this);
}

const string RestoreSimulation::toString() const{
    return "restore" + BaseAction::StatToST(getStatus());
}