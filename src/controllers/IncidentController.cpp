#include "controllers/IncidentController.h"
IncidentController& IncidentController::getInstance() { static IncidentController instance; return instance; }
void IncidentController::initialize() {}
