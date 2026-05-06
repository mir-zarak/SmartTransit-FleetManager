#pragma once
#include "entities/StaffMember.h"

class Conductor : public StaffMember {
private:
    int    m_assignedBusId{};
    int    m_ticketsSoldToday{};
    double m_cashCollectedToday{};

public:
    Conductor() = default;

    int    getAssignedBusId()       const { return m_assignedBusId; }
    int    getTicketsSoldToday()    const { return m_ticketsSoldToday; }
    double getCashCollectedToday()  const { return m_cashCollectedToday; }

    void setAssignedBusId(int id)         { m_assignedBusId = id; }
    void addTicketSold(double amount)     { ++m_ticketsSoldToday; m_cashCollectedToday += amount; }

    CustomString toString()      const override { return getFullName() + CustomString(" [Conductor]"); }
    CustomString getEntityType() const override { return CustomString("Conductor"); }
    void serialize(std::ofstream& out)   const override { StaffMember::serialize(out); }
    void deserialize(std::ifstream& in)        override { StaffMember::deserialize(in); }
};
