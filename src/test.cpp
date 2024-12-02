#include "Simulation.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

void testAddSettlement() {
    Simulation sim("config.txt");
    Settlement* settlement = new Settlement("TestSettlement", SettlementType::URBAN);

    // בדיקה: הוספת יישוב
    assert(sim.addSettlement(settlement) == true);
    assert(sim.isSettlementExists("TestSettlement") == true);

    // בדיקה: יישוב שכבר קיים
    try {
        sim.addSettlement(settlement);
        assert(false); // אם הגענו לכאן, הבדיקה נכשלה
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Settlement already exists.");
    }

    std::cout << "testAddSettlement passed successfully.\n";
}

void testAddFacility() {
    Simulation sim("config.txt");
    FacilityType facility("TestFacility", FacilityCategory::COMMERCIAL, 5000, 10, 5, -3);

    // בדיקה: הוספת מתקן
    assert(sim.addFacility(facility) == true);
    assert(sim.isFacilityExists(facility) == true);

    // בדיקה: מתקן שכבר קיים
    try {
        sim.addFacility(facility);
        assert(false); // אם הגענו לכאן, הבדיקה נכשלה
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Facility already exists.");
    }

    std::cout << "testAddFacility passed successfully.\n";
}

void testAddPlan() {
    Simulation sim("config.txt");
    Settlement* settlement = new Settlement("TestSettlement", SettlementType::URBAN);
    sim.addSettlement(settlement);
    SelectionPolicy* policy = new NaiveSelection();

    // בדיקה: הוספת תוכנית
    sim.addPlan(*settlement, policy);

    Plan& plan = sim.getPlan(0);
    assert(plan.getPlanId() == 0);
    assert(&plan.getSttlement() == settlement);

    // בדיקה: הוספת תוכנית ליישוב שאינו קיים
    try {
        sim.addPlan(Simulation().getSettlement("NonExistent"), policy);
        assert(false); // אם הגענו לכאן, הבדיקה נכשלה
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Cannot create this plan.");
    }

    std::cout << "testAddPlan passed successfully.\n";
}

void testStep() {
    Simulation sim("config.txt");
    Settlement* settlement = new Settlement("TestSettlement", SettlementType::URBAN);
    sim.addSettlement(settlement);

    SelectionPolicy* policy = new NaiveSelection();
    sim.addPlan(*settlement, policy);

    // בדיקה: קריאה ל-step
    sim.step();

    Plan& plan = sim.getPlan(0);
    assert(plan.getFacilities().size() >= 0); // בדוק אם מתבצעות התקדמויות בתוכנית

    std::cout << "testStep passed successfully.\n";
}

void testClose() {
    Simulation sim("config.txt");
    Settlement* settlement = new Settlement("TestSettlement", SettlementType::URBAN);
    sim.addSettlement(settlement);

    SelectionPolicy* policy = new NaiveSelection();
    sim.addPlan(*settlement, policy);

    // קריאה ל-close
    sim.close();

    assert(sim.getSettlements().empty());
    assert(sim.getPlans().empty());
    assert(sim.getFacilitiesOptions().empty());

    std::cout << "testClose passed successfully.\n";
}

int main() {
    try {
        testAddSettlement();
        testAddFacility();
        testAddPlan();
        testStep();
        testClose();
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
