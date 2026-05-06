#include "controllers/AppController.h"

#ifdef SMARTTRANSIT_WITH_GUI
#include <QApplication>
#include "gui/LoginWindow.h"
#endif

int main(int argc, char *argv[]) {

    // Initialize ALL controllers via AppController
    AppController::getInstance().initialize();

#ifdef SMARTTRANSIT_WITH_GUI
    QApplication app(argc, argv);

    LoginWindow w;
    w.show();

    return app.exec();
#else
    (void)argc;
    (void)argv;
    return 0;
#endif
}