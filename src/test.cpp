#include <iostream>
#include <vector>
#include "SelectionPolicy.h"
#include "Facility.h"
using std::vector;

using namespace std;

// Mock FacilityType class for testing purposes
class MockFacilityType : public FacilityType {
public:
    MockFacilityType(const string &name, FacilityCategory category, int price, int lifeQualityScore, int economyScore, int environmentScore)
        : FacilityType(name, category, price, lifeQualityScore, economyScore, environmentScore) {}
};

// Function to test NaiveSelection
void testNaiveSelection() {
    NaiveSelection policy;
    vector<FacilityType> facilities = {
        MockFacilityType("Facility1", FacilityCategory::LIFE_QUALITY, 100, 10, 20, 30),
        MockFacilityType("Facility2", FacilityCategory::ECONOMY, 150, 15, 25, 35),
        MockFacilityType("Facility3", FacilityCategory::ENVIRONMENT, 200, 20, 30, 40),
    };

    const FacilityType &selected = policy.selectFacility(facilities);
    cout << "NaiveSelection selected: " << selected.getName() << endl;
}

// Function to test BalancedSelection
void testBalancedSelection() {
    BalancedSelection policy(10, 20, 30);
    vector<FacilityType> facilities = {
        MockFacilityType("Facility1", FacilityCategory::LIFE_QUALITY, 100, 10, 20, 30),
        MockFacilityType("Facility2", FacilityCategory::ECONOMY, 150, 15, 25, 35),
        MockFacilityType("Facility3", FacilityCategory::ENVIRONMENT, 200, 20, 30, 40),
    };

    const FacilityType &selected = policy.selectFacility(facilities);
    cout << "BalancedSelection selected: " << selected.getName() << endl;
}

// Function to test EconomySelection
void testEconomySelection() {
    EconomySelection policy;
    vector<FacilityType> facilities = {
        MockFacilityType("Facility1", FacilityCategory::LIFE_QUALITY, 100, 10, 20, 30),
        MockFacilityType("Facility2", FacilityCategory::ECONOMY, 150, 15, 25, 35),
        MockFacilityType("Facility3", FacilityCategory::ENVIRONMENT, 200, 20, 30, 40),
    };

    const FacilityType &selected = policy.selectFacility(facilities);
    cout << "EconomySelection selected: " << selected.getName() << endl;
}

// Function to test SustainabilitySelection
void testSustainabilitySelection() {
    SustainabilitySelection policy;
    vector<FacilityType> facilities = {
        MockFacilityType("Facility1", FacilityCategory::LIFE_QUALITY, 100, 10, 20, 30),
        MockFacilityType("Facility2", FacilityCategory::ECONOMY, 150, 15, 25, 35),
        MockFacilityType("Facility3", FacilityCategory::ENVIRONMENT, 200, 20, 30, 40),
    };

    const FacilityType &selected = policy.selectFacility(facilities);
    cout << "SustainabilitySelection selected: " << selected.getName() << endl;
}

// Main function to run all tests
int main() {
    cout << "Testing NaiveSelection:" << endl;
    testNaiveSelection();
    cout << endl;

    cout << "Testing BalancedSelection:" << endl;
    testBalancedSelection();
    cout << endl;

    cout << "Testing EconomySelection:" << endl;
    testEconomySelection();
    cout << endl;

    cout << "Testing SustainabilitySelection:" << endl;
    testSustainabilitySelection();
    cout << endl;

    return 0;
}
