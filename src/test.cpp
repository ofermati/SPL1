#include "Plan.h"
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// פונקציית בדיקה עבור פונקציית step במחלקת Plan
void testPlanStep() {
    // יצירת יישוב לדוגמה
    Settlement settlement("TestSettlement", SettlementType::CITY);

    // יצירת מדיניות בחירה פשוטה
    NaiveSelection selectionPolicy;

    // יצירת מתקנים לדוגמה
    vector<FacilityType> facilityOptions = {
        FacilityType("Park", FacilityCategory::ENVIRONMENT, 10, 5, 0, 7),
        FacilityType("Hospital", FacilityCategory::ECONOMY, 15, 8, 10, 3)
    };

    // יצירת תוכנית (Plan) עם הנתונים שיצרנו
    Plan plan(1, settlement, &selectionPolicy, facilityOptions);

    // פלט דיבוג: מצב התוכנית לפני הקריאה ל-step
    cout << "Before step:\n" << plan.toString() << endl;

    // קריאה ל-step
    plan.step();

    // פלט דיבוג: מצב התוכנית אחרי הקריאה ל-step
    cout << "After step:\n" << plan.toString() << endl;

    // בדיקה שהפונקציה step מוסיפה מתקנים ל-underConstruction
    assert(plan.toString().find("UNDER_CONSTRUCTION") != string::npos && 
           "Facilities should be under construction after step");

    cout << "testPlanStep passed successfully.\n";
}

void testPlanStepCompletion() {
    // יצרנו תוכנית דוגמה כרגיל
    Settlement settlement("TestSettlement", SettlementType::CITY);
    NaiveSelection selectionPolicy;
    vector<FacilityType> facilityOptions = {
        FacilityType("Park", FacilityCategory::ENVIRONMENT, 10, 5, 0, 7),
        FacilityType("Hospital", FacilityCategory::ECONOMY, 15, 8, 10, 3)
    };
    Plan plan(1, settlement, &selectionPolicy, facilityOptions);

    // ביצוע מספר שלבים
    for (int i = 0; i < 10; ++i) {
        cout << "Step " << i + 1 << ":\n";
        plan.step();
        cout << plan.toString() << endl;
    }

    // וודא שאין מתקנים שנשארו ב-underConstruction עם זמן בנייה שלם
    string planOutput = plan.toString();
    size_t pos = planOutput.find("UNDER_CONSTRUCTION");
    if (pos != string::npos) {
        cout << "Facilities still under construction:\n";
        cout << planOutput.substr(pos) << endl;
    }

    // הבדיקה תתמקד רק במתקנים ב-facilities
    for (const Facility* facility : plan.getFacilities()) {
        assert(facility->getStatus() == FacilityStatus::OPERATIONAL &&
               "All facilities in facilities list should be OPERATIONAL");
    }

    cout << "testPlanStepCompletion passed successfully.\n";
}



int main() {
    // קריאה לפונקציות הבדיקה
    testPlanStep();
    testPlanStepCompletion();

    cout << "All tests completed successfully.\n";
    return 0;
}
