#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

enum class JobStatus { OPEN, IN_PROGRESS, DONE, CANCELLED };
class MaintenanceJob {
    int m_jobId{};
    int m_vehicleId{};
    int m_technicianId{};
    CustomString m_description;
    CustomDate m_scheduledDate;
    CustomDate m_completedDate;
    DynamicArray<CustomString> m_parts;
    double m_cost{};
    JobStatus m_status{JobStatus::OPEN};
};
