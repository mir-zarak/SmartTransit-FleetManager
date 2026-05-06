#pragma once
#include "entities/FreightTruck.h"
#include "exceptions/TransitExceptions.h"

class RefrigeratedTruck : public FreightTruck {
private:
    double m_targetTempCelsius{-18.0};
    double m_currentTempCelsius{-18.0};
    static constexpr double TEMP_TOLERANCE = 3.0;

public:
    RefrigeratedTruck() = default;

    double getTargetTemp()  const { return m_targetTempCelsius; }
    double getCurrentTemp() const { return m_currentTempCelsius; }

    void setTargetTemp(double t)  { m_targetTempCelsius = t; }
    void setCurrentTemp(double t) { m_currentTempCelsius = t; checkTempAlert(); }

    // BUG 3 FIX: throws CargoCriticalException if out of range
    void checkTempAlert() const {
        double diff = m_currentTempCelsius - m_targetTempCelsius;
        if (diff > TEMP_TOLERANCE || diff < -TEMP_TOLERANCE) {
            char buf[64];
            std::snprintf(buf, sizeof(buf), "Temp out of range! Target: %.1f Current: %.1f",
                          m_targetTempCelsius, m_currentTempCelsius);
            throw CargoCriticalException(
                CustomString(buf),
                CustomString("RefrigeratedTruck"),
                3001
            );
        }
    }

    // BUG 4 FIX: 1.15x FreightTruck rate (refrigeration overhead)
    double getFuelCostPerKm() const override { return FreightTruck::getFuelCostPerKm() * 1.15; }
    double calculateEmissions(double km) const override { return FreightTruck::calculateEmissions(km) * 1.1; }
    CustomString getVehicleCategory() const override { return CustomString("RefrigeratedTruck"); }
    bool performDailyCheck() const override {
        checkTempAlert(); // BUG 3: call in daily check
        return FreightTruck::performDailyCheck();
    }

    CustomString toString()      const override { return m_registrationNo + CustomString(" (RefrigeratedTruck)"); }
    CustomString getEntityType() const override { return CustomString("RefrigeratedTruck"); }
    void serialize(std::ofstream& out)   const override { FreightTruck::serialize(out); }
    void deserialize(std::ifstream& in)        override { FreightTruck::deserialize(in); }
};
