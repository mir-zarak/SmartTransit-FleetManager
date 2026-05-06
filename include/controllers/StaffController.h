#pragma once
#include "utilities/CustomString.h"
class StaffController {
public:
    static StaffController& getInstance();
    void initialize();
};
