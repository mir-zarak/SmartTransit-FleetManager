#include "controllers/PaymentController.h"
PaymentController& PaymentController::getInstance() { static PaymentController instance; return instance; }
void PaymentController::initialize() {}
