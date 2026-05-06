#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

class ChargingStation {
    int m_stationId{};
    GeoCoordinate m_location;
    int m_totalSlots{};
    int m_availableSlots{};
    double m_powerOutputKW{};
    DynamicArray<int> m_currentVehicles;
};
