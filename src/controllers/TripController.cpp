#include "controllers/TripController.h"
TripController& TripController::getInstance() { static TripController instance; return instance; }
void TripController::initialize() {}
