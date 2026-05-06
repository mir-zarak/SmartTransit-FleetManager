#pragma once
#include "utilities/CustomString.h"
class TicketingController {
public:
    static TicketingController& getInstance();
    void initialize();
};
