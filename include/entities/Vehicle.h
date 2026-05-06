#pragma once
#include "entities/TransitAsset.h"

enum class FuelType { DIESEL, CNG, ELECTRIC, HYBRID };

class Vehicle : public TransitAsset {
protected:
    CustomString m_registrationNo, m_make, m_model, m_colour;
    FuelType m_fuelType{FuelType::DIESEL};
    int m_passengerCapacity{};
    int m_currentPassengers{};
    double m_odometer{};
    GeoCoordinate m_currentPosition;
    int m_assignedDriverId{};
    int m_currentRouteId{};

public:
    Vehicle();
    virtual ~Vehicle() = default;
    int getPassengerCapacity() const { return m_passengerCapacity; }
    void setPassengerCapacity(int cap) { m_passengerCapacity = cap; }
    virtual double getFuelCostPerKm() const = 0;
    virtual CustomString getVehicleCategory() const = 0;
    virtual bool performDailyCheck() const = 0;
    virtual double calculateEmissions(double km) const = 0;
    void boardPassenger();
    void alightPassenger();
    double getOccupancyPercent() const;
    bool isOverCapacity() const;
    void updatePosition(const GeoCoordinate& pos);
    bool operator==(const Vehicle& o) const;
    bool operator<(const Vehicle& o) const;
    double operator-(const Vehicle& o) const;
    CustomString toString() const override;
    CustomString getEntityType() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;
};
