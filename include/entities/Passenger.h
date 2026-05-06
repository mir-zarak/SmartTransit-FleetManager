#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

class Passenger {
    int m_passengerId{};
    CustomString m_name;
    CustomString m_contactNumber;
    int m_loyaltyPoints{};
    LinkedList<int> m_travelHistory;
public:
    void addLoyaltyPoints(int pts) { m_loyaltyPoints += pts; }
    bool redeemPoints(int pts) { if (pts > m_loyaltyPoints) return false; m_loyaltyPoints -= pts; return true; }
};
