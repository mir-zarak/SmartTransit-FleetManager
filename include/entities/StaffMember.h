#pragma once
#include "entities/Person.h"
#include "datastructs/LinkedList.h"

enum class StaffRole { DRIVER, CONDUCTOR, DISPATCHER, MAINTENANCE, TRAFFIC_CONTROLLER, ADMIN };

class StaffMember : public Person {
protected:
    CustomString m_employeeId, m_department;
    StaffRole m_role{StaffRole::ADMIN};
    CustomDate m_joiningDate;
    double m_baseSalary{};
    bool m_isOnDuty{false};
    CustomDate m_licenseExpiry;
    static int s_totalStaff;

public:
    StaffMember();
    int getYearsOfService() const;
    virtual double calculateMonthlySalary() const;
    bool isLicenseValid() const;
    void clockIn();
    void clockOut();
    CustomString toString() const override;
    CustomString getEntityType() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;
};
