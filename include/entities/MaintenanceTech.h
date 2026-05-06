#pragma once
#include "entities/StaffMember.h"

class MaintenanceTech : public StaffMember {
private:
    CustomString m_specialisation;
    int          m_jobsCompletedThisMonth{};

public:
    MaintenanceTech() = default;

    CustomString getSpecialisation()        const { return m_specialisation; }
    int          getJobsCompletedThisMonth() const { return m_jobsCompletedThisMonth; }

    void setSpecialisation(const CustomString& s) { m_specialisation = s; }
    void completeJob()                             { ++m_jobsCompletedThisMonth; }

    CustomString toString()      const override { return getFullName() + CustomString(" [MaintenanceTech]"); }
    CustomString getEntityType() const override { return CustomString("MaintenanceTech"); }
    void serialize(std::ofstream& out)   const override { StaffMember::serialize(out); }
    void deserialize(std::ifstream& in)        override { StaffMember::deserialize(in); }
};
