#pragma once
#include "entities/StaffMember.h"
#include "datastructs/DynamicArray.h"

class Driver : public StaffMember {
private:
    CustomString m_licenseClass;
    int          m_assignedVehicleId{};
    double       m_hoursThisWeek{};
    int          m_incidentCount{};

public:
    Driver() = default;
    Driver(const CustomString& licClass, int vehicleId,
           double hours, int incidents)
        : m_licenseClass(licClass), m_assignedVehicleId(vehicleId),
          m_hoursThisWeek(hours), m_incidentCount(incidents) {}

    CustomString getLicenseClass()      const { return m_licenseClass; }
    int          getAssignedVehicleId() const { return m_assignedVehicleId; }
    double       getHoursThisWeek()     const { return m_hoursThisWeek; }
    int          getIncidentCount()     const { return m_incidentCount; }

    void setAssignedVehicleId(int id)            { m_assignedVehicleId = id; }
    void setLicenseClass(const CustomString& lc) { m_licenseClass = lc; }
    void addHours(double h)                      { m_hoursThisWeek += h; }
    void logIncident()                           { ++m_incidentCount; }

    CustomString toString()      const override { return getFullName() + CustomString(" [Driver]"); }
    CustomString getEntityType() const override { return CustomString("Driver"); }
    void serialize(std::ofstream& out)   const override { StaffMember::serialize(out); }
    void deserialize(std::ifstream& in)        override { StaffMember::deserialize(in); }
};
