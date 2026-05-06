#pragma once
#include "utilities/CustomString.h"
class AppController {
public:
    static AppController& getInstance();
    void initialize();
};
