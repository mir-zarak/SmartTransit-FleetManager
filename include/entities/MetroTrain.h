#pragma once
#include "entities/Vehicle.h"

class MetroTrain : public Vehicle {
private:
    CustomString m_lineId;
    int          m_carriageCount{1};
    double       m_maxSpeed{};
    bool         m_isUnderground{};

public:
    MetroTrain() = default;

    CustomString getLineId()        const { return m_lineId; }
    int          getCarriageCount() const { return m_carriageCount; }
    double       getMaxSpeed()      const { return m_maxSpeed; }
    bool         isUnderground()    const { return m_isUnderground; }

    void setLineId(const CustomString& id)  { m_lineId = id; }
    void setCarriageCount(int c)            { if (c > 0) m_carriageCount = c; }
    void setMaxSpeed(double s)              { if (s > 0) m_maxSpeed = s; }
    void setUnderground(bool u)             { m_isUnderground = u; }

    // BUG 4 FIX: electric — scales with carriage count, zero emissions
    double getFuelCostPerKm() const override { return 5.0 * m_carriageCount; }
    double calculateEmissions(double) const override { return 0.0; }
    CustomString getVehicleCategory() const override { return CustomString("MetroTrain"); }
    bool performDailyCheck()          const override { return true; }

    CustomString toString()      const override { return m_registrationNo + CustomString(" (MetroTrain)"); }
    CustomString getEntityType() const override { return CustomString("MetroTrain"); }
    void serialize(std::ofstream& out)   const override { Vehicle::serialize(out); }
    void deserialize(std::ifstream& in)        override { Vehicle::deserialize(in); }
};
