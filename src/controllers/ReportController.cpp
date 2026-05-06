#include "controllers/ReportController.h"
ReportController& ReportController::getInstance() { static ReportController instance; return instance; }
void ReportController::initialize() {}
