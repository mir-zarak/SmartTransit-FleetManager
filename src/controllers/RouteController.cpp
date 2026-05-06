#include "controllers/RouteController.h"
RouteController& RouteController::getInstance() { static RouteController instance; return instance; }
void RouteController::initialize() {}
