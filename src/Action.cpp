#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.h"
#include "Settlement.h"
#include <iostream>
enum class SettlementType;
enum class FacilityCategory;

//---------------------------BaseAction---------------------------לבדוק אם צריך
/*
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
*/
//---------------------------SimulationStep---------------------------
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}
void SimulateStep::act(Simulation &simulation){
    for (int i = 1; i <= numOfSteps; i++){//הייתה הערה שמחקתי כי אמרו שמותר להניח שמספר הצעדים גדול מ0
        simulation.step();//קורא לסטפ של סימוליישן שקורה לספט של פלאנ שקורה לסטפ של פסיליטי ששם באמת מתבצע הסטפ
    }
    complete();
}
const string SimulateStep::toString() const{//צריך שנייה לדבר על מה נדפיס כי בהוראות כתוב בדיוק מה צריך להדפיס
    return "SimulateStep: " + std::to_string(numOfSteps) + " steps";
}
SimulateStep *SimulateStep::clone() const{//לא הבנתי למה צריך קלון או אם זה נכון אבל נזרום
    return new SimulateStep(*this);
}

//---------------------------AddPlan---------------------------//
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
settlementName(settlementName), selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    Settlement *sett = Simulation::getSettlement(settlementName);
    SelectionPolicy *selectionPolicy= Simulation::ToSelectionPolicy(selectionPolicy);
    if(sett == nullptr | selectionPolicy == nullptr){
       error(getErrorMsg());
    }
    simulation.addPlan(sett, selectionPolicy);
    complete();  //הייתי צריכה לכלול את סימוליישנ בשביל שזה יעבוד אז מקווה שזה לא יעשה בעיות עם פרגמה וואנ ס וכאלה
}

const string AddPlan::toString() const{
    return "AddPlan: The settlement is" + settlementName + " and the selection policy is" + selectionPolicy;
}
AddPlan *AddPlan::clone() const{
    return new AddPlan(*this);
}


//---------------------------AddSettlement---------------------------
AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
    settlementName(settlementName), settlementType(settlementType){}

void act(Simulation &simulation){
    Settlement *addMe = new Settlement(settlementName, settlementType);
    if(addMe == nullptr){
        error(getErrorMsg());  
    }
    simulation.addSettlement(addMe);
}
AddSettlement *clone() const{
      return new AddSettlement(*this);
}
const string toString() const{
    return "The settlement name is" + settlementName + " and the type is" + Settlement::STtostring(settlementType);
}


//---------------------------AddFacility---------------------------

 AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
 facilityName(facilityName), facilityCategory(facilityCategory), price(price),
 lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore)
 {}
       
             
void act(Simulation &simulation) {
    Facility *addMe = new Facility(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    if (addMe == nullptr){
       error(errorMsg); 
    }
    simulation.addFacility(*this);
}

AddFacility *clone() const {
    return new AddFacility(*this);
}

const string toString() const {
    string output = "The facility name is" + facilityName + " it category is" + Facility::categoryToString(facilityCategory) + " the price is" + std::to_string(price) + '\n';
    output += "life quality score" + std::to_string(lifeQualityScore) + '\n';
    output += "life economy score" + std::to_string(economyScore) + '\n';
    output += "life enviromnet score" + std::to_string(environmentScore) + '\n';
}


//---------------------------PrintPlanStatus---------------------------
 PrintPlanStatus(int planId): planId(planId){}

void act(Simulation &simulation) {
    simulation.getPlan(planId);
        if (plan.getId() == nullptr){
        error(errorMsg);
        }
    plan.printStatus();
}

PrintPlanStatus *clone() const {
    return new PrintPlanStatus(*this);
}

const string toString() const {
    return "this is plan number" + std::to_string(planId); //אולי ממש להוסיף את הסטטוס של הפלאן וכו
}


//---------------------------ChangePlanPolicy---------------------------

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy) : planId(planId), newPolicy(newPolicy){}

void act(Simulation &simulation){
    if(Simulation::getPlan(planId)==nullptr){
        error("Plan" + std::toString(planID) + "not found!");
    }
    Plan &plan = simulation.getPlan(planId);
    if(plan == nullptr || newPolicy==plan.getSelectionPolicy()->getName()){
        error("Cannot change selection policy");
    }
    string prev = plan.getSelectionPolicy()->getName();
    delete plan.getSelectionPolicy();//לוודא שזה באמת מוחק ושלא צריך להעביר את זה למחלקה סימוליישן ששם יצרנו את הסלקשן פוליסי
    plan.setSelectionPolicy(Simulation::ToSelectionPolicy(newPolicy, plan.GetwithUnderQUA(), plan.GetwithUnderScoreECO(), plan.GetwithUnderENVI()));
    string output = std::to_string(plan.getPlanId()) +'/n' + "previous Policy:" + prev +'/n' + "new Policy:" + plan.getSelectionPolicy()->getName();
    std::cout << output << std::endl;
}

ChangePlanPolicy *clone() const{
    return new ChangePlanPolicy(*this);
}
       
const string toString() const{
    return "the plan number is" + std::to_string(planId) + "and the new policy is" + newPolicy;
}

//---------------------------PrintActionsLog---------------------------

PrintActionsLog(); ///לא יודעת איך 

void act(Simulation &simulation){

}

PrintActionsLog *clone() const{
     return new PrintActionsLog(*this);
}

const string toString() const{

}
