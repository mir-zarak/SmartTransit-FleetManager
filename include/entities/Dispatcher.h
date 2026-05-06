#pragma once
#include "entities/StaffMember.h"

class Dispatcher : public StaffMember {
private:
    int          m_activeDeployments{};
    CustomString m_zoneId;

public:
    Dispatcher() = default;

    int          getActiveDeployments() const { return m_activeDeployments; }
    CustomString getZoneId()            const { return m_zoneId; }

    void setZoneId(const CustomString& z) { m_zoneId = z; }
    void incrementDeployments()           { ++m_activeDeployments; }
    void decrementDeployments()           { if (m_activeDeployments > 0) --m_activeDeployments; }

    CustomString toString()      const override { return getFullName() + CustomString(" [Dispatcher]"); }
    CustomString getEntityType() const override { return CustomString("Dispatcher"); }
    void serialize(std::ofstream& out)   const override { StaffMember::serialize(out); }
    void deserialize(std::ifstream& in)        override { StaffMember::deserialize(in); }
};
