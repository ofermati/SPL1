#include "Plan.h"
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include <iostream>
#include <vector>
<<<<<<< HEAD
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
=======
#include "SelectionPolicy.h"  // Assuming SelectionPolicy and its subclasses are defined here
#include "Facility.h"         // Assuming FacilityType is defined here

using namespace std;

int main() {
    // Facilities for testing
    vector<FacilityType> facilities = {
        {"Economy Facility 1", FacilityCategory::ECONOMY, 100, 10, 20, 30},
        {"Environment Facility 1", FacilityCategory::ENVIRONMENT, 150, 15, 10, 25},
        {"Economy Facility 2", FacilityCategory::ECONOMY, 200, 20, 15, 10},
        {"Environment Facility 2", FacilityCategory::ENVIRONMENT, 250, 5, 10, 40}
    };

    // Test NaiveSelection
    NaiveSelection naiveSelector;
    cout << "Testing NaiveSelection:" << endl;
    const FacilityType &selectedNaive = naiveSelector.selectFacility(facilities);
    cout << "Selected: " << selectedNaive.getName() << " with life quality: " << selectedNaive.getLifeQualityScore() << endl;
    cout << naiveSelector.toString() << endl;

    // Test BalancedSelection
    BalancedSelection balancedSelector(50, 50, 50);  // Adjust constructor as needed
    cout << "\nTesting BalancedSelection:" << endl;
    const FacilityType &selectedBalanced = balancedSelector.selectFacility(facilities);
    cout << "Selected: " << selectedBalanced.getName() << " with life quality: " << selectedBalanced.getLifeQualityScore() << endl;
    cout << balancedSelector.toString() << endl;

    // Test EconomySelection
    EconomySelection economySelector;
    cout << "\nTesting EconomySelection:" << endl;
    try {
        const FacilityType &selectedEconomy = economySelector.selectFacility(facilities);
        cout << "Selected: " << selectedEconomy.getName() << " with economy score: " << selectedEconomy.getEconomyScore() << endl;
    } catch (const std::runtime_error &e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    cout << economySelector.toString() << endl;

    // Test SustainabilitySelection
    SustainabilitySelection sustainabilitySelector;
    cout << "\nTesting SustainabilitySelection:" << endl;
    try {
        const FacilityType &selectedSustainability = sustainabilitySelector.selectFacility(facilities);
        cout << "Selected: " << selectedSustainability.getName() << " with environment score: " << selectedSustainability.getEnvironmentScore() << endl;
    } catch (const std::runtime_error &e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    cout << sustainabilitySelector.toString() << endl;
>>>>>>> 36fb37c52200ea9f2925dc74af9cbd470f521868

    cout << "All tests passed successfully.\n";
    return 0;
}
