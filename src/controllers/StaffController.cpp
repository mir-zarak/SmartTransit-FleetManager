#include "controllers/StaffController.h"
StaffController& StaffController::getInstance() { static StaffController instance; return instance; }
void StaffController::initialize() {}
