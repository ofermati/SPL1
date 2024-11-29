#include <iostream>
#include <vector>
#include "Facility.h"

int main() {
    // Test the Facility class

    // Create a FacilityType object
    FacilityType facilityType("Economy Facility 1", FacilityCategory::ECONOMY, 100, 10, 20, 30);

    // Create a Facility object using the FacilityType
    Facility facility(facilityType, "Settlement 1");

    // Test the Facility class methods
    std::cout << "Facility Name: " << facility.getName() << std::endl;
    std::cout << "Settlement Name: " << facility.getSettlementName() << std::endl;
    std::cout << "Facility Category: " << static_cast<int>(facility.getCategory()) << std::endl;
    std::cout << "Facility Cost: " << facility.getCost() << std::endl;
    std::cout << "Facility Life Quality Score: " << facility.getLifeQualityScore() << std::endl;
    std::cout << "Facility Economy Score: " << facility.getEconomyScore() << std::endl;
    std::cout << "Facility Environment Score: " << facility.getEnvironmentScore() << std::endl;
    std::cout << "Facility Time Left: " << facility.getTimeLeft() << std::endl;
    std::cout << "Facility Status: " << static_cast<int>(facility.getStatus()) << std::endl;

    // Step the Facility
    while (facility.getTimeLeft() > 0) {
        facility.step();
    }

    std::cout << "Facility Status after construction: " << static_cast<int>(facility.getStatus()) << std::endl;

    // Test the Facility toString method
    std::cout << "Facility toString: " << facility.toString() << std::endl;

    return 0;
}