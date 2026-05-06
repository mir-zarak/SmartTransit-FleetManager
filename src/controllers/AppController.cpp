#include "controllers/AppController.h"
#include "controllers/AuthController.h"
#include "controllers/FleetController.h"

AppController& AppController::getInstance() {
    static AppController instance;
    return instance;
}

void AppController::initialize() {
    AuthController::getInstance().initialize();
    FleetController::getInstance().initialize();
}