#pragma once
#include "entities/Entity.h"

class Person : public Entity {
protected:
    CustomString m_firstName, m_lastName, m_cnic, m_contactNumber, m_email, m_address;
    CustomDate m_dob;

public:
    Person();
    CustomString getFullName() const;
    int getAge() const;
    bool validateContact() const;
    bool operator<(const Person& o) const;
    CustomString toString() const override;
    CustomString getEntityType() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;
};
