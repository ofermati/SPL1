#include <iostream>
#include "Plan.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Facility.h"

// Function to test Plan functionality
void testPlan() {
    // Create a Settlement
    Settlement settlement("Test Settlement", SettlementType::CITY);

    // Create Facility Types
    FacilityType facilityType1("Facility1", FacilityCategory::LIFE_QUALITY, 100, 10, 20, 30);
    FacilityType facilityType2("Facility2", FacilityCategory::ECONOMY, 200, 15, 25, 35);
    FacilityType facilityType3("Facility3", FacilityCategory::ENVIRONMENT, 150, 20, 30, 40);

    std::vector<FacilityType> facilityOptions = {facilityType1, facilityType2, facilityType3};

    // Create a Selection Policy
    NaiveSelection naiveSelection;

    // Create a Plan
    Plan plan(1, settlement, &naiveSelection, facilityOptions);

    // Print initial state
    std::cout << "Initial Plan State:\n" << plan.toString() << "\n";

    // Add facilities
    Facility facility1(facilityType1, settlement.getName());
    Facility facility2(facilityType2, settlement.getName());
    facility1.setStatus(FacilityStatus::UNDER_CONSTRUCTIONS);
    facility2.setStatus(FacilityStatus::OPERATIONAL);

    plan.addFacility(&facility1);
    plan.addFacility(&facility2);

    // Print state after adding facilities
    std::cout << "\nPlan State After Adding Facilities:\n" << plan.toString() << "\n";

    // Step through the Plan
    plan.step();

    // Print state after stepping
    std::cout << "\nPlan State After Step:\n" << plan.toString() << "\n";

    // Test setSelectionPolicy
    BalancedSelection balancedSelection(10, 15, 20);
    plan.setSelectionPolicy(&balancedSelection);

    // Print state after changing selection policy
    std::cout << "\nPlan State After Changing Selection Policy:\n" << plan.toString() << "\n";
}

int main() {
    testPlan();
    return 0;
}
