#pragma once
#include "entities/Vehicle.h"

class RideHailCar : public Vehicle {
private:
    double m_driverRating{5.0};
    int    m_tripCount{};
    double m_surgeMultiplier{1.0};

public:
    RideHailCar() = default;

    double getDriverRating()     const { return m_driverRating; }
    int    getTripCount()        const { return m_tripCount; }
    double getSurgeMultiplier()  const { return m_surgeMultiplier; }

    void setDriverRating(double r)    { if (r >= 0.0 && r <= 5.0) m_driverRating = r; }
    void setSurgeMultiplier(double m) { if (m >= 1.0) m_surgeMultiplier = m; }
    void incrementTrips()             { ++m_tripCount; }

    // BUG 4 FIX: surge pricing
    double getFuelCostPerKm()        const override { return 15.0 * m_surgeMultiplier; }
    double calculateEmissions(double km) const override { return km * 0.21; }
    CustomString getVehicleCategory() const override { return CustomString("RideHailCar"); }
    bool performDailyCheck()          const override { return true; } // insurance + MOT

    CustomString toString()      const override { return m_registrationNo + CustomString(" (RideHailCar)"); }
    CustomString getEntityType() const override { return CustomString("RideHailCar"); }
    void serialize(std::ofstream& out)   const override { Vehicle::serialize(out); }
    void deserialize(std::ifstream& in)        override { Vehicle::deserialize(in); }
};
