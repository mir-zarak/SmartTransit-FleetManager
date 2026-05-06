#pragma once
#include "utilities/CustomString.h"
class PaymentController {
public:
    static PaymentController& getInstance();
    void initialize();
};
