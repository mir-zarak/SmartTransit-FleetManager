#pragma once
#include "entities/MetroTrain.h"

class HighSpeedTrain : public MetroTrain {
private:
    double       m_maxOperatingSpeedKmh{};
    double       m_tiltAngle{};
    CustomString m_signalClass;

public:
    HighSpeedTrain() = default;

    double       getMaxOperatingSpeed() const { return m_maxOperatingSpeedKmh; }
    double       getTiltAngle()         const { return m_tiltAngle; }
    CustomString getSignalClass()       const { return m_signalClass; }

    void setMaxOperatingSpeed(double s)         { if (s > 0) m_maxOperatingSpeedKmh = s; }
    void setTiltAngle(double a)                 { m_tiltAngle = a; }
    void setSignalClass(const CustomString& sc) { m_signalClass = sc; }

    // BUG 4 FIX: 1.5x MetroTrain rate
    double getFuelCostPerKm()        const override { return MetroTrain::getFuelCostPerKm() * 1.5; }
    double calculateEmissions(double) const override { return 0.0; } // electric
    CustomString getVehicleCategory() const override { return CustomString("HighSpeedTrain"); }
    bool performDailyCheck()          const override { return true; } // rail-integrity check

    CustomString toString()      const override { return m_registrationNo + CustomString(" (HighSpeedTrain)"); }
    CustomString getEntityType() const override { return CustomString("HighSpeedTrain"); }
    void serialize(std::ofstream& out)   const override { MetroTrain::serialize(out); }
    void deserialize(std::ifstream& in)        override { MetroTrain::deserialize(in); }
};
