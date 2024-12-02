
#include "Plan.h"
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// בדיקות לתרחישים בסיסיים ומתקדמים

// בדיקת פונקציית step עם מתקנים זמינים
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

    cout << "testStep passed.";
}

// בדיקה לתרחיש ללא מתקנים
void testNoFacilities() {
    Settlement settlement("EmptySettlement", SettlementType::VILLAGE);
    NaiveSelection selectionPolicy;
    vector<FacilityType> facilityOptions = {}; // ללא מתקנים
    Plan plan(2, settlement, &selectionPolicy, facilityOptions);

    try {
        plan.step();
        assert(false && "Step should throw an exception when no facilities are available");
    } catch (const std::exception &e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }

    cout << "testNoFacilities passed.";
}

// בדיקה לאינטגרציה עם יישובים
void testSettlementIntegration() {
    Settlement settlement("TestVillage", SettlementType::VILLAGE);
    NaiveSelection selectionPolicy;
    vector<FacilityType> facilityOptions = {
        FacilityType("School", FacilityCategory::ECONOMY, 12, 6, 8, 2)
    };
    Plan plan(3, settlement, &selectionPolicy, facilityOptions);

    // בדיקת נתוני הישוב
    assert(plan.toString().find("TestVillage") != string::npos && "Settlement name should match");
    assert(plan.toString().find("Village") != string::npos && "Settlement type should match");

    cout << "testSettlementIntegration passed.";
}

// בדיקת SelectionPolicy שונות
void testSelectionPolicies() {
    vector<FacilityType> facilities = {
        FacilityType("EcoPark", FacilityCategory::ENVIRONMENT, 20, 10, 5, 15),
        FacilityType("Mall", FacilityCategory::ECONOMY, 30, 5, 20, 5),
        FacilityType("Factory", FacilityCategory::ECONOMY, 40, 5, 25, 0)
    };

    BalancedSelection balanced(50, 50, 50);
    const FacilityType &selectedBalanced = balanced.selectFacility(facilities);
    assert(selectedBalanced.getName() == "EcoPark" && "BalancedSelection should select the best balanced facility");

    EconomySelection economy;
    const FacilityType &selectedEconomy = economy.selectFacility(facilities);
    assert(selectedEconomy.getName() == "Mall" && "EconomySelection should select the facility with ECONOMY category");

    cout << "testSelectionPolicies passed.";
}

// בדיקת פונקציית scoreUpdate
void testScoreUpdate() {
    Settlement settlement("ScoreSettlement", SettlementType::CITY);
    NaiveSelection selectionPolicy;
    vector<FacilityType> facilityOptions = {
        FacilityType("Garden", FacilityCategory::ENVIRONMENT, 10, 5, 0, 7),
        FacilityType("Market", FacilityCategory::ECONOMY, 15, 8, 10, 3)
    };
    Plan plan(4, settlement, &selectionPolicy, facilityOptions);

    plan.step();
    Facility *facility = plan.getFacilities().front();
    assert(facility != nullptr && "Facility should exist after step");
}

// פונקציה ראשית להרצת כל הבדיקות
int main() {
    testStep();
    testNoFacilities();
    testSettlementIntegration();
    testSelectionPolicies();
    testScoreUpdate();

    cout << "All tests passed successfully.";
    return 0;
}
