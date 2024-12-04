#include "Facility.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

//facilityType:

FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
    : name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score){}

FacilityType::FacilityType()
    :     FacilityType("", FacilityCategory::ECONOMY, 0, 0, 0, 0){}


FacilityType& FacilityType::operator=(const FacilityType& other){
    return *this;
}


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
    }
    return status;
}

void Facility::setStatus(FacilityStatus status){
    this->status=status;
}

const FacilityStatus& Facility::getStatus() const{
    return status;
}

const string Facility::toString() const{
    return "this is" + name + "in" + settlementName + "with" +  std::to_string(timeLeft) + "time left.";
}

string FacilityType::categoryToString (FacilityCategory type) const {
     switch (type) {
        case FacilityCategory::ECONOMY : return "Economy";
        case FacilityCategory::ENVIRONMENT : return "Enviroment";
        case FacilityCategory::LIFE_QUALITY : return "Life quality";
    }
    return "Unknown";
}