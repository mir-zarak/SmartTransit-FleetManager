#pragma once
#include "utilities/CustomString.h"
#include "utilities/CustomDate.h"
#include "utilities/CustomTime.h"
#include "utilities/GeoCoordinate.h"
#include "datastructs/DynamicArray.h"
#include "datastructs/LinkedList.h"

enum class TicketType { SINGLE, DAY_PASS, WEEKLY, STUDENT, CORPORATE };
class Ticket {
    int m_ticketId{};
    int m_passengerId{};
    int m_tripId{};
    double m_fareAmount{};
    CustomDate m_issueDate;
    CustomTime m_issueTime;
    TicketType m_type{TicketType::SINGLE};
    bool m_isValidated{};
public:
    bool operator==(const Ticket& o) const { return m_ticketId == o.m_ticketId; }
    friend std::ostream& operator<<(std::ostream& os, const Ticket& t){ return os << t.m_ticketId; }
};
