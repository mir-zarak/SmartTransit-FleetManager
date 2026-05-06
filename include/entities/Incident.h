#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

enum class IncidentSeverity { LOW, MEDIUM, HIGH, CRITICAL };
class Incident {
    int m_incidentId{};
    int m_vehicleId{};
    int m_driverId{};
    CustomString m_description;
    GeoCoordinate m_location;
    CustomDate m_date;
    CustomTime m_time;
    IncidentSeverity m_severity{IncidentSeverity::LOW};
    bool m_isResolved{};
};
