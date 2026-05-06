#pragma once
#include "utilities/CustomString.h"
class RouteController {
public:
    static RouteController& getInstance();
    void initialize();
};
