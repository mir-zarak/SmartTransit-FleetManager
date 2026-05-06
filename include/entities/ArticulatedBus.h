#pragma once
#include "entities/CityBus.h"

class ArticulatedBus : public CityBus {
private:
    int    m_secondSegmentCapacity{};
    double m_jointAngle{};

public:
    ArticulatedBus() = default;

    int    getSecondSegmentCapacity() const { return m_secondSegmentCapacity; }
    double getJointAngle()            const { return m_jointAngle; }

    void setSecondSegmentCapacity(int c) { if (c >= 0) m_secondSegmentCapacity = c; }
    void setJointAngle(double a)         { m_jointAngle = a; }

    // BUG 4 FIX: higher drag factor than CityBus
    double getFuelCostPerKm() const override { return CityBus::getFuelCostPerKm() * 1.3; }
    double calculateEmissions(double km) const override { return CityBus::calculateEmissions(km) * 1.3; }
    CustomString getVehicleCategory() const override { return CustomString("ArticulatedBus"); }
    bool performDailyCheck()          const override { return CityBus::performDailyCheck(); }

    CustomString toString()      const override { return m_registrationNo + CustomString(" (ArticulatedBus)"); }
    CustomString getEntityType() const override { return CustomString("ArticulatedBus"); }
    void serialize(std::ofstream& out)   const override { CityBus::serialize(out); }
    void deserialize(std::ifstream& in)        override { CityBus::deserialize(in); }
};
