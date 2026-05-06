#include "entities/Vehicle.h"
Vehicle::Vehicle() = default;
void Vehicle::boardPassenger() { ++m_currentPassengers; }
void Vehicle::alightPassenger() { if (m_currentPassengers > 0) --m_currentPassengers; }
double Vehicle::getOccupancyPercent() const { return m_passengerCapacity ? (100.0 * m_currentPassengers / m_passengerCapacity) : 0.0; }
bool Vehicle::isOverCapacity() const { return m_currentPassengers > m_passengerCapacity; }
void Vehicle::updatePosition(const GeoCoordinate& pos) { m_currentPosition = pos; }
bool Vehicle::operator==(const Vehicle& o) const { return m_registrationNo == o.m_registrationNo; }
bool Vehicle::operator<(const Vehicle& o) const { return m_registrationNo < o.m_registrationNo; }
double Vehicle::operator-(const Vehicle& o) const { return m_currentPosition - o.m_currentPosition; }
CustomString Vehicle::toString() const {
    return m_registrationNo + CustomString(" (") + getVehicleCategory() + CustomString(")");
}
CustomString Vehicle::getEntityType() const { return CustomString("Vehicle"); }
void Vehicle::serialize(std::ofstream&) const {}
void Vehicle::deserialize(std::ifstream&) {}
