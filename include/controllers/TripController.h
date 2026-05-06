#pragma once
#include "utilities/CustomString.h"
class TripController {
public:
    static TripController& getInstance();
    void initialize();
};
