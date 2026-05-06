#pragma once
#include "utilities/CustomString.h"
class ReportController {
public:
    static ReportController& getInstance();
    void initialize();
};
