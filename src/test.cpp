#include <iostream>
#include "Facility.h"
#include "Settlement.h"

using namespace std;

void testFacility() {
    cout << "Testing Facility Class..." << endl;

    // Create a mock Settlement
    Settlement settlement("TestSettlement", SettlementType::CITY);

    // Test Facility Constructor with parameters
    Facility facility1("Library", "TestSettlement", FacilityCategory::LIFE_QUALITY, 10, 20, 15, 5);
    cout << "Facility Name: " << facility1.getName() << endl;
    cout << "Settlement Name: " << facility1.getSettlementName() << endl;
    cout << "Category: LIFE_QUALITY" << endl;
    cout << "Cost: " << facility1.getCost() << endl;
    cout << "Life Quality Score: " << facility1.getLifeQualityScore() << endl;
    cout << "Economy Score: " << facility1.getEconomyScore() << endl;
    cout << "Environment Score: " << facility1.getEnvironmentScore() << endl;
    cout << "Initial Status: " 
         << (facility1.getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS ? "UNDER_CONSTRUCTIONS" : "OPERATIONAL") 
         << endl;

    // Test Facility setStatus() and getStatus()
    facility1.setStatus(FacilityStatus::OPERATIONAL);
    cout << "Updated Status: " 
         << (facility1.getStatus() == FacilityStatus::OPERATIONAL ? "OPERATIONAL" : "UNDER_CONSTRUCTIONS") 
         << endl;

    // Test step() method (if implemented)
    cout << "Testing step() method..." << endl;
    FacilityStatus result = facility1.step();
    cout << "Step result: " 
         << (result == FacilityStatus::OPERATIONAL ? "OPERATIONAL" : "UNDER_CONSTRUCTIONS") 
         << endl;

    // Test toString() method
    cout << "Facility Info: " << facility1.toString() << endl;

    cout << "Facility Class Test Completed." << endl;
}

int main() {
    try {
        testFacility();
    } catch (const exception &e) {
        cerr << "Test failed: " << e.what() << endl;
    }
    return 0;
}
