#include <iostream>
#include <vector>
#include "SelectionPolicy.h"
#include "Facility.h"

using namespace std;

// Utility function to print the facilities vector
void printFacilities(const vector<FacilityType> &facilities) {
    cout << "Facilities:\n";
    for (const auto &facility : facilities) {
        cout << "  " << facility.getName()
             << " | Category: " << static_cast<int>(facility.getCategory())
             << " | Life Quality: " << facility.getLifeQualityScore()
             << " | Economy: " << facility.getEconomyScore()
             << " | Environment: " << facility.getEnvironmentScore() << "\n";
    }
}

// Test function for SelectionPolicy
void testSelectionPolicy(SelectionPolicy *policy, vector<FacilityType> &facilities) {
    cout << "Testing " << policy->toString() << ":\n";
    cout << "Initial Facilities:\n";
    printFacilities(facilities);
    cout << "\n";

    // Perform 5 steps of selection
    for (int i = 0; i < 5; ++i) {
        cout << "Step " << (i + 1) << ":\n";
        try {
            const FacilityType &selected = policy->selectFacility(facilities);
            cout << "  Selected Facility: " << selected.getName() << "\n";
        } catch (const std::exception &e) {
            cout << "  Error: " << e.what() << "\n";
        }
        cout << "\n";
    }

    delete policy; // Clean up the dynamically allocated policy
}

// Main function to run the test
int main() {
    vector<FacilityType> facilities = {
        FacilityType("Facility1", FacilityCategory::LIFE_QUALITY, 100, 50, 30, 20),
        FacilityType("Facility2", FacilityCategory::ECONOMY, 150, 40, 60, 10),
        FacilityType("Facility3", FacilityCategory::ENVIRONMENT, 200, 30, 20, 50),
        FacilityType("Facility4", FacilityCategory::LIFE_QUALITY, 120, 70, 20, 30),
        FacilityType("Facility5", FacilityCategory::ECONOMY, 130, 30, 50, 40),
    };

    cout << "Testing NaiveSelection:\n";
    testSelectionPolicy(new NaiveSelection(), facilities);
    cout << "\n";

    cout << "Testing BalancedSelection:\n";
    testSelectionPolicy(new BalancedSelection(0, 0, 0), facilities);
    cout << "\n";

    cout << "Testing EconomySelection:\n";
    testSelectionPolicy(new EconomySelection(), facilities);
    cout << "\n";

    cout << "Testing SustainabilitySelection:\n";
    testSelectionPolicy(new SustainabilitySelection(), facilities);
    cout << "\n";

    return 0;
}
