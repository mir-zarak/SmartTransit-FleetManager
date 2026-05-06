#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

enum class TripStatus { SCHEDULED, IN_PROGRESS, COMPLETED, CANCELLED };
class Trip {
public:
    int m_tripId{};
    int m_vehicleId{};
    int m_driverId{};
    int m_routeId{};
    CustomTime m_startTime;
    CustomTime m_actualStartTime;
    CustomTime m_endTime;
    int m_passengersBoardedTotal{};
    TripStatus m_status{TripStatus::SCHEDULED};
    int m_delayMinutes{};
};
