#pragma once
#include "entities/StaffMember.h"
#include "entities/INotifiable.h"
#include "datastructs/LinkedList.h"

class AdminUser : public StaffMember, public INotifiable {
private:
    CustomString             m_username;
    CustomString             m_passwordHash;
    int                      m_accessLevel{};
    LinkedList<CustomString> m_activityLog;

public:
    AdminUser() = default;

    // INotifiable interface
    void sendNotification(const CustomString& msg, int priority) override {
        char buf[16];
        std::snprintf(buf, sizeof(buf), "[P%d] ", priority);
        CustomString entry = CustomString(buf) + msg;
        m_activityLog.push_back(entry);
    }
    LinkedList<CustomString> getDeliveryLog() const override { return m_activityLog; }
    void clearLog() override { m_activityLog.clear(); }

    // Getters / Setters
    CustomString getUsername()    const { return m_username; }
    int          getAccessLevel() const { return m_accessLevel; }
    void setUsername(const CustomString& u)     { m_username = u; }
    void setPasswordHash(const CustomString& h) { m_passwordHash = h; }
    void setAccessLevel(int lvl)                { if (lvl >= 0 && lvl <= 10) m_accessLevel = lvl; }

    CustomString toString()      const override { return m_username + CustomString(" [Admin]"); }
    CustomString getEntityType() const override { return CustomString("AdminUser"); }
    void serialize(std::ofstream& out)   const override { StaffMember::serialize(out); }
    void deserialize(std::ifstream& in)        override { StaffMember::deserialize(in); }
};
