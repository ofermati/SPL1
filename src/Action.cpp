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




/*
class BackupSimulation : public BaseAction {
    public:
        BackupSimulation();
        void act(Simulation &simulation) override;
        BackupSimulation *clone() const override;
        const string toString() const override;
    private:
};
*/

BaseAction::BackupSimulation(){

}

/*
class ChangePlanPolicy : public BaseAction {
    public:
        X ChangePlanPolicy(const int planId, const string &newPolicy);
        void act(Simulation &simulation) override;
        ChangePlanPolicy *clone() const override;
        const string toString() const override;
    private:
        const int planId;
        const string newPolicy;
};

*/

BaseAction::ChangePlanPolicy(const int planId, const string &newPolicy):planId(planId), newPolicy(newPolicy){}

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
    std::cout << output << std::endl
}
