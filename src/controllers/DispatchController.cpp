#include "controllers/DispatchController.h"
DispatchController& DispatchController::getInstance() { static DispatchController instance; return instance; }
void DispatchController::initialize() {}
