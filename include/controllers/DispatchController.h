#pragma once
#include "utilities/CustomString.h"
class DispatchController {
public:
    static DispatchController& getInstance();
    void initialize();
};
