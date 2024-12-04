#include "SelectionPolicy.h"
#include <vector>
#include <algorithm> // std::max
#include <cmath>     // std::abs
#include <stdexcept>
#include <iostream>


using std::vector;

/*************************************** NaiveSelection *****************************************/
// Constrector:
NaiveSelection::NaiveSelection() : lastSelectedIndex(0){}

// Methods:
const FacilityType &NaiveSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    lastSelectedIndex = lastSelectedIndex % facilitiesOptions.size();
    const FacilityType &output = facilitiesOptions[lastSelectedIndex];
    lastSelectedIndex++;
    return output;
}

const string NaiveSelection::toString() const
{
    return "Naive Selection (Last Selected Index: " + std::to_string(lastSelectedIndex) + ")";
}

NaiveSelection *NaiveSelection::clone() const
{
    NaiveSelection *other = new NaiveSelection(*this);
    // in this case, the * means look at the values at my address.
    return other;
}

const string NaiveSelection::getName() const{
    return "nve";
}

/*************************************** BalancedSelection *****************************************/

BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
    : LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

BalancedSelection::BalancedSelection():BalancedSelection(0,0,0){} //בנאי דיפולטיבי

const FacilityType &BalancedSelection::selectFacility(const vector<FacilityType> &facilitiesOptions){
    if (facilitiesOptions.empty())
    {
        throw std::invalid_argument("facilitiesOptions cannot be empty");
    }
    int minIndex = 0;
    int minBalance = Balance(facilitiesOptions[0], LifeQualityScore, EconomyScore, EnvironmentScore);

    for (size_t i = 1; i < facilitiesOptions.size(); i++){
        int currentBalance = Balance(facilitiesOptions[i], LifeQualityScore, EconomyScore, EnvironmentScore);
        if (currentBalance < minBalance){
            minIndex = i;
            minBalance = currentBalance;
        }
    }
    
    LifeQualityScore = LifeQualityScore + facilitiesOptions[minIndex].getLifeQualityScore();
    EconomyScore = EconomyScore + facilitiesOptions[minIndex].getEconomyScore();
    EnvironmentScore = EnvironmentScore + facilitiesOptions[minIndex].getEnvironmentScore();
    return facilitiesOptions[minIndex];
}

int BalancedSelection::Balance(const FacilityType &type, int LifeQualityScore, int EconomyScore, int EnvironmentScore){
    int LifeQuality = type.getLifeQualityScore() + LifeQualityScore;
    int Economy = type.getEconomyScore() + EconomyScore;
    int Environment = type.getEnvironmentScore() + EnvironmentScore;
    int diff1 = std::abs(Environment - Economy);
    int diff2 = std::abs(Economy - LifeQuality);
    int diff3 = std::abs(LifeQuality - Environment);
    int maxDiff = std::max({diff1, diff2, diff3});
    return maxDiff;
}

const string BalancedSelection::toString() const{
    return ("this is Balanced Selection. the life quality score is" + std::to_string(LifeQualityScore) + "the economy score is" + std::to_string(EconomyScore) + "the enviroment score is" + std::to_string(EnvironmentScore));
}

BalancedSelection *BalancedSelection::clone() const{
    BalancedSelection *other = new BalancedSelection(*this);
    // in this case, the * means look at the values at my address.
    return other;
}

const string BalancedSelection::getName() const{
    return "bal";
}

/*************************************** EconomySelection *****************************************/

EconomySelection::EconomySelection() : lastSelectedIndex(-1) {}

const FacilityType &EconomySelection::selectFacility(const vector<FacilityType> &facilitiesOptions){
    int firsti= (lastSelectedIndex + 1) % facilitiesOptions.size();
    for (size_t i = firsti ; i<=facilitiesOptions.size() ; i = (i + 1) % facilitiesOptions.size()){
        if (facilitiesOptions[i].getCategory() == FacilityCategory::ECONOMY){
            lastSelectedIndex=i;
            return facilitiesOptions[i];
        }
    }
    throw std::runtime_error("No facility with ECONOMY category found.");
}

const string EconomySelection::toString() const
{
    return "Economy selection (Last Selected Index: " + std::to_string(lastSelectedIndex) + ")";
}

EconomySelection *EconomySelection::clone() const
{
    EconomySelection *other = new EconomySelection(*this);
    // in this case, the * means look at the values at my address.
    return other;
}

const string EconomySelection::getName() const{
    return "eco";
}
/*************************************** SustainabilitySelection *****************************************/

SustainabilitySelection::SustainabilitySelection(): lastSelectedIndex(-1) {}

const FacilityType &SustainabilitySelection::selectFacility(const vector<FacilityType> &facilitiesOptions) {
    int firsti= (lastSelectedIndex + 1) % facilitiesOptions.size();
    for (size_t i=firsti ; i<=facilitiesOptions.size() ; i = (i + 1) % facilitiesOptions.size()){
        if (facilitiesOptions[i].getCategory() == FacilityCategory::ENVIRONMENT){
            lastSelectedIndex=i;
            return facilitiesOptions[i];
        }
    }
    throw std::runtime_error("No facility with ENVIRONMENT category found.");
}

const string SustainabilitySelection::toString() const {
    return "ENVIRONMENT selection (Last Selected Index: " + std::to_string(lastSelectedIndex) + ")";
}

SustainabilitySelection *SustainabilitySelection::clone() const {
     SustainabilitySelection *other = new SustainabilitySelection(*this);
    // in this case, the * means look at the values at my address.
    return other;
}

const string SustainabilitySelection::getName() const{
    return "env";
}

