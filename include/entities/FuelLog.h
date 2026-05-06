#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

class FuelLog {
    int m_logId{};
    int m_vehicleId{};
    double m_litresFilled{};
    double m_costPerLitre{};
    double m_totalCost{};
    double m_odometer{};
    CustomDate m_fillDate;
public:
    double operator*() const { return m_litresFilled * m_costPerLitre; }
    friend std::ostream& operator<<(std::ostream& os, const FuelLog& f){ return os << f.m_totalCost; }
};
