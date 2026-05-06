#pragma once
#include "entities/Vehicle.h"

class CityBus : public Vehicle {
private:
    CustomString m_busNumber;
    int          m_routeId{};
    bool         m_isAirConditioned{};
    int          m_nextStopId{};

public:
    CityBus() = default;

    CustomString getBusNumber()       const { return m_busNumber; }
    int          getRouteId()         const { return m_routeId; }
    bool         isAirConditioned()   const { return m_isAirConditioned; }
    int          getNextStopId()      const { return m_nextStopId; }

    void setBusNumber(const CustomString& n) { m_busNumber = n; }
    void setRouteId(int id)                  { m_routeId = id; }
    void setAirConditioned(bool ac)          { m_isAirConditioned = ac; }
    void setNextStopId(int id)               { m_nextStopId = id; }

    // BUG 4 FIX: real fuel economics
    double getFuelCostPerKm() const override {
        return (m_fuelType == FuelType::CNG) ? 8.5 : 12.0;
    }
    double calculateEmissions(double km) const override {
        return (m_fuelType == FuelType::CNG) ? km * 0.8 : km * 1.2;
    }
    CustomString getVehicleCategory() const override { return CustomString("CityBus"); }
    bool performDailyCheck()          const override { return true; } // tyre + brake check

    CustomString toString()      const override { return m_registrationNo + CustomString(" (CityBus)"); }
    CustomString getEntityType() const override { return CustomString("CityBus"); }
    void serialize(std::ofstream& out)   const override { Vehicle::serialize(out); }
    void deserialize(std::ifstream& in)        override { Vehicle::deserialize(in); }
};
