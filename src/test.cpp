#include "Plan.h"
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// פונקציה פשוטה לבדיקת פונקציית step
void testStep() {
    Settlement settlement("TestSettlement", SettlementType::CITY);
    NaiveSelection selectionPolicy;
    vector<FacilityType> facilityOptions = {
        FacilityType("Park", FacilityCategory::ENVIRONMENT, 10, 5, 0, 7),
        FacilityType("Hospital", FacilityCategory::ECONOMY, 15, 8, 10, 3)
    };
    Plan plan(1, settlement, &selectionPolicy, facilityOptions);

    // בדיקה ראשונית
    assert(plan.getFacilities().empty() && "Facilities should be empty at initialization");

    // ביצוע שלב ראשון
    plan.step();

    // בדיקה שהסטטוס נשאר "AVAILABLE" ושיש מתקנים בתהליך בנייה
    assert(plan.toString().find("AVAILABLE") != string::npos && "Plan should be AVAILABLE after step");
    assert(plan.toString().find("UNDER_CONSTRUCTION") != string::npos && "Facilities should be under construction");

    // ביצוע שלב נוסף ובדיקה שמתקנים מתקדמים
    plan.step();
    assert(!plan.getFacilities().empty() && "Facilities should not be empty after construction steps");

    cout << "testStep passed.\n";
}

// פונקציה לבדיקת יצירת תוכנית עם ישוב
void testSettlementIntegration() {
    Settlement settlement("TestVillage", SettlementType::VILLAGE);
    NaiveSelection selectionPolicy;
    vector<FacilityType> facilityOptions = {
        FacilityType("School", FacilityCategory::ECONOMY, 12, 6, 8, 2)
    };
    Plan plan(2, settlement, &selectionPolicy, facilityOptions);

    // בדיקת נתוני הישוב
    assert(plan.toString().find("TestVillage") != string::npos && "Settlement name should match");
    assert(plan.toString().find("Village") != string::npos && "Settlement type should match");

    cout << "testSettlementIntegration passed.\n";
}

// פונקציה לבדיקת הדפסת מצב
void testPrintStatus() {
    Settlement settlement("TestSettlement", SettlementType::METROPOLIS);
    NaiveSelection selectionPolicy;
    vector<FacilityType> facilityOptions = {
        FacilityType("Library", FacilityCategory::ENVIRONMENT, 8, 4, 0, 6)
    };
    Plan plan(3, settlement, &selectionPolicy, facilityOptions);

    cout << "Expected: Available\nActual: ";
    plan.printStatus();
    cout << "\nPrint status test passed.\n";
}

int main() {
    // קריאה לפונקציות הבדיקה
    testStep();
    testSettlementIntegration();
    testPrintStatus();

    cout << "All tests passed successfully.\n";
    return 0;
}
