#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

class Stop {
    int m_stopId{};
    CustomString m_stopName;
    GeoCoordinate m_position;
    DynamicArray<int> m_lineIds;
    bool m_coveredShelter{};
public:
    bool operator==(const Stop& o) const { return m_stopId == o.m_stopId; }
    bool operator<(const Stop& o) const { return m_stopName < o.m_stopName; }
    friend std::ostream& operator<<(std::ostream& os, const Stop& s){ return os << s.m_stopName; }
};
