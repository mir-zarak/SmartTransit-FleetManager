#pragma once
#include "entities/Driver.h"
#include "datastructs/DynamicArray.h"

class SeniorDriver : public Driver {
private:
    int                       m_menteeCount{};
    DynamicArray<CustomString> m_awardsList;

public:
    SeniorDriver() = default;

    int          getMenteeCount() const { return m_menteeCount; }
    void         addMentee()            { ++m_menteeCount; }
    void         addAward(const CustomString& award) { m_awardsList.append(award); }
    int          getAwardCount() const  { return m_awardsList.size(); }

    // BUG 2 FIX: Seniority bonus — 10% extra per 5 years of service
    double calculateMonthlySalary() const override {
        double base  = StaffMember::calculateMonthlySalary();
        int    years = getYearsOfService();
        double bonus = base * 0.10 * (years / 5 + 1);
        return base + bonus;
    }

    CustomString toString()      const override { return getFullName() + CustomString(" [SeniorDriver]"); }
    CustomString getEntityType() const override { return CustomString("SeniorDriver"); }
    void serialize(std::ofstream& out)   const override { StaffMember::serialize(out); }
    void deserialize(std::ifstream& in)        override { StaffMember::deserialize(in); }
};
