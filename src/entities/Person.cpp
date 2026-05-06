#include "entities/Person.h"
Person::Person() = default;
CustomString Person::getFullName() const { return m_firstName + CustomString(" ") + m_lastName; }
int Person::getAge() const { return CustomDate::today() - m_dob; }
bool Person::validateContact() const { return !m_contactNumber.isEmpty() && !m_email.isEmpty(); }
bool Person::operator<(const Person& o) const { return m_lastName < o.m_lastName; }
CustomString Person::toString() const { return getFullName(); }
CustomString Person::getEntityType() const { return CustomString("Person"); }
void Person::serialize(std::ofstream&) const {}
void Person::deserialize(std::ifstream&) {}
