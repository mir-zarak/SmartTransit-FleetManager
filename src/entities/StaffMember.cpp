#include "entities/StaffMember.h"
int StaffMember::s_totalStaff = 0;
StaffMember::StaffMember() { ++s_totalStaff; }
int StaffMember::getYearsOfService() const { return CustomDate::today() - m_joiningDate; }
double StaffMember::calculateMonthlySalary() const { return m_baseSalary; }
bool StaffMember::isLicenseValid() const { return !(CustomDate::today() > m_licenseExpiry); }
void StaffMember::clockIn() { m_isOnDuty = true; }
void StaffMember::clockOut() { m_isOnDuty = false; }
CustomString StaffMember::toString() const { return CustomString("StaffMember"); }
CustomString StaffMember::getEntityType() const { return CustomString("StaffMember"); }
void StaffMember::serialize(std::ofstream&) const {}
void StaffMember::deserialize(std::ifstream&) {}
