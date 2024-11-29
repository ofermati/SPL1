#include <iostream>
#include <vector>
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

    return 0;
}
