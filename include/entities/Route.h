#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

#include "entities/Stop.h"
class Route {
    int m_routeId{};
    CustomString m_routeName;
    LinkedList<Stop*> m_stops;
    double m_totalDistanceKm{};
    int m_scheduledFrequencyMinutes{};
    bool m_isActive{true};
public:
    int getTotalStops() const { return m_stops.size(); }
    void addStop(Stop* s) { m_stops.push_back(s); }
    void removeStop(int idx) { m_stops.removeAt(idx); }
};
