#pragma once
#include <vector>
#include "Facility.h"
using std::vector;

class SelectionPolicy {
    public:
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) = 0;
        virtual const string toString() const = 0;
        virtual SelectionPolicy* clone() const = 0;
        virtual ~SelectionPolicy() = default;
        virtual const string getName() const = 0;
};

class NaiveSelection: public SelectionPolicy {
    public:
        NaiveSelection();
        // NaiveSelection& operator=(const NaiveSelection& other)= default;
        // NaiveSelection(const NaiveSelection &other) = default;
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        NaiveSelection *clone() const override;
        // ~NaiveSelection() override = default;
        const string getName() const override;
    private:
        int lastSelectedIndex;
};

class BalancedSelection: public SelectionPolicy {
    public:
        BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        BalancedSelection();
        // BalancedSelection& operator=(const BalancedSelection& other)= default;
        // BalancedSelection(const BalancedSelection &other) = default;
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        BalancedSelection *clone() const override;
        int Balance(const FacilityType &type, int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        ~BalancedSelection() override = default;
        const string getName() const override;
    private:
        int LifeQualityScore;
        int EconomyScore;
        int EnvironmentScore;
};

class EconomySelection: public SelectionPolicy {
    public:
        EconomySelection();
        // EconomySelection& operator=(const EconomySelection& other)= default;
        // EconomySelection(const EconomySelection &other) = default;
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        EconomySelection *clone() const override;
        ~EconomySelection() override = default;
        const string getName() const override;
    private:
        int lastSelectedIndex;

};

class SustainabilitySelection: public SelectionPolicy {
    public:
        SustainabilitySelection();
        // SustainabilitySelection& operator=(const SustainabilitySelection& other)= default;
        // SustainabilitySelection(const SustainabilitySelection &other) = default;
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        SustainabilitySelection *clone() const override;
        ~SustainabilitySelection() override = default;
        const string getName() const override;
    private:
        int lastSelectedIndex;
};