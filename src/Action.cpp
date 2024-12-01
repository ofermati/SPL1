#include "Action.h"
#include <string>
#include <vector>
#include "Simulation.cpp"
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

//---------------------------AddPlan---------------------------//משהו שצריך לחשוב עליו: אם זורקים הערה אי אפשר לשנות את הסטטוס לארור
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
settlementName(settlementName), selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    Settlement *sett = Simulation::getSettlement(settlementName);//אם לק קיים יישוב כזה זה יזרוק הערה בגט סטלמנט
    SelectionPolicy *selectionPolicy= Simulation::ToSelectionPolicy(selectionPolicy);//אם לא קיימת סלקשן פולייס כזאת יזרוק הערה בפונקציה של עופר
    simulation.addPlan(sett, selectionPolicy);
    complete();  //הייתי צריכה לכלול את סימוליישנ בשביל שזה יעבוד אז מקווה שזה לא יעשה בעיות עם פרגמה וואנ ס וכאלה
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
    Settlement *addMe = new Settlement(settlementName, settlementType);
    simulation.addSettlement(addMe);
}
AddSettlement *clone() const{

}
const string toString() const{
    return "The settlement name is" + settlementName + " and the type is" + Settlement::STtostring(settlementType);
}