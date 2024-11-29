#include <iostream>
#include "Facility.h"
#include "Settlement.h"

void testFacility() {
    // Create a Settlement
    Settlement settlement("TestSettlement", SettlementType::CITY);

    // Create a FacilityType
    FacilityType facilityType("Library", FacilityCategory::LIFE_QUALITY, 150, 10, 5, 7);

    // Test Facility Constructor
    Facility facility(facilityType, settlement.getName());

    // Check initial status
    std::cout << "Facility Name: " << facility.getName() << std::endl;
    std::cout << "Facility Settlement: " << facility.getSettlementName() << std::endl;
    std::cout << "Initial Status: " << (facility.getStatus() == FacilityStatus::UNDER_CONSTRUCTIONS ? "Under Construction" : "Operational") << std::endl;

    // Change status and test
    facility.setStatus(FacilityStatus::OPERATIONAL);
    std::cout << "Updated Status: " << (facility.getStatus() == FacilityStatus::OPERATIONAL ? "Operational" : "Error") << std::endl;

    // Test the Facility's scores
    std::cout << "Life Quality Score: " << facilityType.getLifeQualityScore() << std::endl;
    std::cout << "Economy Score: " << facilityType.getEconomyScore() << std::endl;
    std::cout << "Environment Score: " << facilityType.getEnvironmentScore() << std::endl;

    // Test toString
    std::cout << "Facility Info: " << facility.toString() << std::endl;
}

int main() {
    try {
        testFacility();
    } catch (const std::exception &e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
    }

    return 0;
}
