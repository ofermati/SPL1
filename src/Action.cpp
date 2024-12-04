#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
#include "Settlement.h"
#include <iostream>
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

SimulateStep::SimulateStep(const int numOfSteps) : BaseAction(), numOfSteps(numOfSteps) {}

void SimulateStep::act(Simulation &simulation){
    for (int i = 1; i <= numOfSteps; i++){//הייתה הערה שמחקתי כי אמרו שמותר להניח שמספר הצעדים גדול מ0
        simulation.step();//קורא לסטפ של סימוליישן שקורה לספט של פלאנ שקורה לסטפ של פסיליטי ששם באמת מתבצע הסטפ
    }
    complete();
}

const string SimulateStep::toString() const{//צריך שנייה לדבר על מה נדפיס כי בהוראות כתוב בדיוק מה צריך להדפיס
    return "step " + std::to_string(numOfSteps) +" " + StatToST(getStatus());
}

SimulateStep *SimulateStep::clone() const{//לא הבנתי למה צריך קלון או אם זה נכון אבל נזרום
    return new SimulateStep(*this);
}



//---------------------------AddPlan---------------------------//

AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    Settlement *sett = simulation.getSettlement(settlementName);
    SelectionPolicy *policy = simulation.ToSelectionPolicy(selectionPolicy, 0, 0, 0); 
    if(sett == nullptr| policy == nullptr){
       error("Cannot create this plan");
    }else{
    simulation.addPlan(*sett, policy);
    complete();  //הייתי צריכה לכלול את סימוליישנ בשביל שזה יעבוד אז מקווה שזה לא יעשה בעיות עם פרגמה וואנ ס וכאלה
    }
}

const string AddPlan::toString() const{
    return "plan " + settlementName + selectionPolicy +" "+ StatToST(getStatus());
}

AddPlan *AddPlan::clone() const{
    return new AddPlan(*this);
}



//---------------------------AddSettlement---------------------------

AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
    BaseAction(), settlementName(settlementName), settlementType(settlementType){}

void AddSettlement::act(Simulation &simulation){

    Settlement *addMe = simulation.getSettlement(settlementName);
    if(addMe != nullptr){
       error("”Settlement already exists”");
    }else{
        simulation.addSettlement(new Settlement(settlementName, settlementType));
        complete();
    }
}

AddSettlement *AddSettlement::clone() const{
    return new AddSettlement(*this);
}

const string AddSettlement::toString() const{
    return "settlement " + settlementName +" "+ std::to_string(static_cast<int>(settlementType)) +" "+ BaseAction::StatToST(getStatus());
}

//---------------------------AddFacility---------------------------

 AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
 BaseAction(), facilityName(facilityName), facilityCategory(facilityCategory), price(price),
 lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore){}

void AddFacility::act(Simulation &simulation) {
    FacilityType *addMe = simulation.getFacility(facilityName);
    if (addMe != nullptr){
       error("Facility already exist");
    }else{
        simulation.addFacility(*addMe);
        string output = "The facility name is" + facilityName + " it category is" + addMe->categoryToString(facilityCategory) + " the price is" + std::to_string(price) + '\n';
        output += "life quality score" + std::to_string(lifeQualityScore) + '\n';
        output += "life economy score" + std::to_string(economyScore) + '\n';
        output += "life enviromnet score" + std::to_string(environmentScore) + '\n';
        complete();
        std::cout << output << std::endl;
    }
}

AddFacility *AddFacility::clone() const {
    return new AddFacility(*this);
}

const string AddFacility::toString() const {
    return "facility " + facilityName + std::to_string(static_cast<int>(facilityCategory)) +" "+ std::to_string(price) +std::to_string(lifeQualityScore) + std::to_string(economyScore) + std::to_string(environmentScore) + BaseAction::StatToST(getStatus());
}

//---------------------------PrintPlanStatus---------------------------

PrintPlanStatus::PrintPlanStatus(int planId): BaseAction(), planId(planId){}

void PrintPlanStatus::act(Simulation &simulation) {
    if (planId < 0 || planId >= simulation.getplanCounter()) {//the id is not legal
        error("Plan doesn’t exist");
    }
    else{
        simulation.getPlan(planId);
        complete();
        simulation.getPlan(planId).printStatus();
    }
}

PrintPlanStatus *PrintPlanStatus::clone() const {
    return new PrintPlanStatus(*this);
}

const string PrintPlanStatus::toString() const {
    return "plan "+ BaseAction::StatToST(getStatus());
}

//---------------------------ChangePlanPolicy---------------------------
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy) : BaseAction(), planId(planId), newPolicy(newPolicy){}

void ChangePlanPolicy::act(Simulation &simulation){
    Plan &plan = simulation.getPlan(planId);
    if (planId < 0 || planId >= simulation.getplanCounter()) {//the id is not legal
        error("Cannot change selection policy");
    }
    if(newPolicy == plan.getSelectionPolicy()->getName()){
        error("Cannot change selection policy");
    }else{
        string prev = plan.getSelectionPolicy()->getName();
        delete plan.getSelectionPolicy();//לוודא שזה באמת מוחק ושלא צריך להעביר את זה למחלקה סימוליישן ששם יצרנו את הסלקשן פוליסי
        plan.setSelectionPolicy(simulation.ToSelectionPolicy(newPolicy, plan.GetwithUnderQUA(), plan.GetwithUnderScoreECO(), plan.GetwithUnderENVI()));
        string output = std::to_string(plan.getPlanId()) + '\n';
        output += "previous Policy: " + prev + '\n';
        output += "new Policy: " + plan.getSelectionPolicy()->getName();
        complete();
        std::cout << output << std::endl;
    }
}

ChangePlanPolicy *ChangePlanPolicy::clone() const{
    return new ChangePlanPolicy(*this);
}

const string ChangePlanPolicy::toString() const{
    return "changePolisy " + std::to_string(planId) + " " + newPolicy +" "+ BaseAction::StatToST(getStatus());
}

//---------------------------PrintActionsLog---------------------------
PrintActionsLog::PrintActionsLog() :BaseAction(){}

void PrintActionsLog::act(Simulation &simulation){
    complete();
    string output= simulation.PrintTheLogs();
    std::cout << output << std::endl;
}

PrintActionsLog *PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);
}

const string PrintActionsLog::toString() const{
    return "log " + BaseAction::StatToST(getStatus());
}

//---------------------------Close---------------------------
Close::Close(): BaseAction(){}

void Close::act(Simulation &simulation){
    complete();
    simulation.close();
}

Close *Close::clone() const{
    return new Close(*this);
}

const string Close::toString() const{
    return "close " + BaseAction::StatToST(getStatus());
}


//---------------------------BackupSimulation---------------------------
BackupSimulation::BackupSimulation(): BaseAction(){}

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
    return "backup " + BaseAction::StatToST(getStatus());
}

//---------------------------RestoreSimulation---------------------------
RestoreSimulation::RestoreSimulation(): BaseAction(){}

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
    return "restore " + BaseAction::StatToST(getStatus());
}