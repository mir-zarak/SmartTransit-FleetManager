#pragma once
#include "utilities/CustomString.h"
class MaintenanceController {
public:
    static MaintenanceController& getInstance();
    void initialize();
};
