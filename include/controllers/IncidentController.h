#pragma once
#include "utilities/CustomString.h"
class IncidentController {
public:
    static IncidentController& getInstance();
    void initialize();
};
