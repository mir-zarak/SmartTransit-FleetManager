#pragma once
#include "entities/Vehicle.h"

class ElectricScooter : public Vehicle {
private:
    int m_batteryLevelPercent{100};
    int m_dockingStationId{};

public:
    ElectricScooter() = default;

    int getBatteryLevelPercent() const { return m_batteryLevelPercent; }
    int getDockingStationId()    const { return m_dockingStationId; }

    void setBatteryLevel(int lvl)    { if (lvl >= 0 && lvl <= 100) m_batteryLevelPercent = lvl; }
    void setDockingStationId(int id) { m_dockingStationId = id; }

    // BUG 4 FIX: minimal cost, zero emissions
    double getFuelCostPerKm()        const override { return 1.5; }
    double calculateEmissions(double) const override { return 0.0; }
    CustomString getVehicleCategory() const override { return CustomString("ElectricScooter"); }
    bool performDailyCheck()          const override { return m_batteryLevelPercent > 20; }

    CustomString toString()      const override { return m_registrationNo + CustomString(" (ElectricScooter)"); }
    CustomString getEntityType() const override { return CustomString("ElectricScooter"); }
    void serialize(std::ofstream& out)   const override { Vehicle::serialize(out); }
    void deserialize(std::ifstream& in)        override { Vehicle::deserialize(in); }
};
