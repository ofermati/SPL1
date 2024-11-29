#include <iostream>
#include <vector>
#include "Facility.h"

int main() {
    // Test the Facility class

    // Create a FacilityType object
    FacilityType facilityType("Economy Facility 1", FacilityCategory::ECONOMY, 100, 10, 20, 30);

    // Create a Facility object using the FacilityType
    Facility facility(facilityType, "Settlement 1");

<<<<<<< HEAD
const string &FacilityType::getName() const{
    return name;
}

int FacilityType::getCost() const{
    return price;
}

int FacilityType::getLifeQualityScore() const{
    return lifeQuality_score;
}

int FacilityType::getEnvironmentScore() const{
    return environment_score;
}

int FacilityType::getEconomyScore() const{
    return economy_score;
}

FacilityCategory FacilityType::getCategory() const{
    return category;
}

//facility:

Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
    : FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score),
    settlementName(settlementName),
    status(FacilityStatus::UNDER_CONSTRUCTIONS),
    timeLeft(price){}

Facility::Facility(const FacilityType &type, const string &settlementName)
    :Facility(type.FacilityType::getName(), settlementName, type.FacilityType::getCategory(), type.FacilityType::getCost(), type.FacilityType::getLifeQualityScore(), type.FacilityType::getEconomyScore(), type.FacilityType::getEnvironmentScore()){}

Facility::Facility()
    : Facility(FacilityType(), ""){}

const string &Facility::getSettlementName() const{
    return settlementName;
}

const int Facility::getTimeLeft() const{
    return timeLeft;
}

FacilityStatus Facility::step(){
    if(timeLeft>0){
        timeLeft=timeLeft-1;
        if(timeLeft==0) {
        setStatus(FacilityStatus::OPERATIONAL);
        }
=======
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
>>>>>>> 36fb37c52200ea9f2925dc74af9cbd470f521868
    }

    std::cout << "Facility Status after construction: " << static_cast<int>(facility.getStatus()) << std::endl;

    // Test the Facility toString method
    std::cout << "Facility toString: " << facility.toString() << std::endl;

    return 0;
}