#include "controllers/MaintenanceController.h"
MaintenanceController& MaintenanceController::getInstance() { static MaintenanceController instance; return instance; }
void MaintenanceController::initialize() {}
