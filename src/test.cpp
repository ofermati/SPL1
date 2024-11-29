#include "Plan.h"
#include <iostream>
#include <cassert> // For assertions

// Simple test framework functions
int totalTests = 0;
int passedTests = 0;

void runTest(const std::string &testName, bool condition) {
    totalTests++;
    if (condition) {
        std::cout << "[PASSED] " << testName << "\n";
        passedTests++;
    } else {
        std::cout << "[FAILED] " << testName << "\n";
    }
}

void printSummary() {
    std::cout << passedTests << " / " << totalTests << " tests passed.\n";
}

// Tests
void testDefaultConstructor() {
    runTest("Default Constructor", []() {
        Plan defaultPlan;
        return defaultPlan.getlifeQualityScore() == 0 &&
               defaultPlan.getEconomyScore() == 0 &&
               defaultPlan.getEnvironmentScore() == 0 &&
               defaultPlan.getFacilities().empty();
    }());
}

void testParameterizedConstructor() {
    runTest("Parameterized Constructor", []() {
        Settlement settlement("TestTown", SettlementType::CITY); // Adjust SettlementType if needed
        SelectionPolicy *policy = new BalancedSelection(0,0,0); // Replace with your actual policy type
        std::vector<FacilityType> facilityOptions = {FacilityType("HOSPITAL", FacilityCategory::ENVIRONMENT, 1000, 80, 75, 90),  FacilityType("SCHOOL", FacilityCategory::LIFE_QUALITY, 500, 85, 80, 70)};

        Plan paramPlan(1, settlement, policy, facilityOptions);

        bool result = paramPlan.getlifeQualityScore() == 0 &&
                      paramPlan.getEconomyScore() == 0 &&
                      paramPlan.getEnvironmentScore() == 0 &&
                      paramPlan.getFacilities().empty();
        delete policy; // Cleanup
        return result;
    }());
}

void testCopyConstructor() {
    runTest("Copy Constructor", []() {
        Settlement settlement("TestTown", SettlementType::VILLAGE);
        SelectionPolicy *policy = new EconomySelection(); // Replace with your actual policy type
        std::vector<FacilityType> facilityOptions = {FacilityType("HOSPITAL", FacilityCategory::ENVIRONMENT, 1000, 80, 75, 90)};

        Plan originalPlan(1, settlement, policy, facilityOptions);
        Plan copiedPlan(originalPlan); // Correct usage of the copy constructor

        bool result = copiedPlan.getlifeQualityScore() == originalPlan.getlifeQualityScore() &&
                      copiedPlan.getEconomyScore() == originalPlan.getEconomyScore() &&
                      copiedPlan.getEnvironmentScore() == originalPlan.getEnvironmentScore() &&
                      copiedPlan.getFacilities().size() == originalPlan.getFacilities().size() &&
                      copiedPlan.getFacilities().data() != originalPlan.getFacilities().data(); // Ensure deep copy

        delete policy; // Cleanup
        return result;
    }());
}

void testToString() {
    runTest("ToString Method", []() {
        Settlement settlement("TestTown", SettlementType::VILLAGE);
        SelectionPolicy *policy = new BalancedSelection(0,0,0); // Replace with your actual policy type
        std::vector<FacilityType> facilityOptions = {FacilityType("HOSPITAL", FacilityCategory::ENVIRONMENT, 1000, 80, 75, 90)};
        Plan testPlan(1, settlement, policy, facilityOptions);
        std::string output = testPlan.toString();

        bool result = output.find("PlanID: 1") != std::string::npos &&
                      output.find("SettlementName: TestTown") != std::string::npos;

        delete policy; // Cleanup
        return result;
    }());
}

// Main Function
int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testCopyConstructor();
    testToString();

    printSummary();
    return 0;
}
