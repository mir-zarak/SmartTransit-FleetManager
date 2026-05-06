#pragma once
#include "entities/Vehicle.h"

class FreightTruck : public Vehicle {
protected:
    double       m_cargoWeightKg{};
    double       m_maxPayloadKg{10000.0};
    CustomString m_cargoType;
    bool         m_requiresRefrigeration{};

public:
    FreightTruck() = default;

    double       getCargoWeightKg()       const { return m_cargoWeightKg; }
    double       getMaxPayloadKg()        const { return m_maxPayloadKg; }
    CustomString getCargoType()           const { return m_cargoType; }
    bool         requiresRefrigeration()  const { return m_requiresRefrigeration; }

    void setCargoWeightKg(double w)             { if (w >= 0) m_cargoWeightKg = w; }
    void setMaxPayloadKg(double m)              { if (m > 0) m_maxPayloadKg = m; }
    void setCargoType(const CustomString& t)    { m_cargoType = t; }
    void setRequiresRefrigeration(bool r)       { m_requiresRefrigeration = r; }

    // BUG 4 FIX: scales with cargo weight ratio
    double getFuelCostPerKm() const override {
        double ratio = (m_maxPayloadKg > 0) ? (m_cargoWeightKg / m_maxPayloadKg) : 0.0;
        return 20.0 + ratio * 10.0;
    }
    double calculateEmissions(double km) const override {
        return km * (2.5 + m_cargoWeightKg / 10000.0);
    }
    CustomString getVehicleCategory() const override { return CustomString("FreightTruck"); }
    bool performDailyCheck()          const override { return true; }

    CustomString toString()      const override { return m_registrationNo + CustomString(" (FreightTruck)"); }
    CustomString getEntityType() const override { return CustomString("FreightTruck"); }
    void serialize(std::ofstream& out)   const override { Vehicle::serialize(out); }
    void deserialize(std::ifstream& in)        override { Vehicle::deserialize(in); }
};
