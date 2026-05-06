#include "controllers/TicketingController.h"
TicketingController& TicketingController::getInstance() { static TicketingController instance; return instance; }
void TicketingController::initialize() {}
