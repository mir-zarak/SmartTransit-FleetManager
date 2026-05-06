#include "gui/MainDashboard.h"
#include "gui/CommonQt.h"
#include "gui/FleetManagementWindow.h"
#include "gui/RouteBuilderWindow.h"
#include "gui/TicketingWindow.h"
#include "gui/ReportDashboardWindow.h"
#include "gui/StaffManagementWindow.h"
#include "gui/MaintenanceWindow.h"
#include "gui/DispatchConsoleWindow.h"
#include "gui/LiveMapWindow.h"
#include "gui/TripSchedulerWindow.h"
#include "gui/LoginWindow.h"
#include "controllers/AuthController.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

MainDashboard::MainDashboard(QWidget* parent) : QWidget(parent) {
    setWindowTitle("SmartTransit EMS — Dashboard");
    setMinimumSize(500, 600);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    auto& auth = AuthController::getInstance();
    UserRole role = auth.getCurrentRole();

    QString userInfo = QString("Logged in as: %1").arg(auth.getCurrentUser().c_str());
    auto* title   = new QLabel("SmartTransit EMS Dashboard");
    auto* userLbl = new QLabel(userInfo);
    QFont titleFont = title->font();
    titleFont.setPointSize(16); titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    userLbl->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);
    mainLayout->addWidget(userLbl);
    mainLayout->addSpacing(10);

    // Helper lambda: create button that opens a window safely
    auto makeBtn = [&](const QString& label, auto factory) {
        auto* btn = new QPushButton(label);
        btn->setMinimumHeight(40);
        connect(btn, &QPushButton::clicked, this, [=]() {
            try {
                auto* w = factory();
                w->setAttribute(Qt::WA_DeleteOnClose);
                w->setMinimumSize(700, 500);
                w->show();
            } catch (const std::exception& ex) {
                QMessageBox::critical(this, "Error", ex.what());
            }
        });
        return btn;
    };

    bool isAdmin      = (role == UserRole::ADMIN);
    bool isDispatcher = (role == UserRole::DISPATCHER);
    bool isDriver     = (role == UserRole::DRIVER);
    bool isConductor  = (role == UserRole::CONDUCTOR);
    bool isMaintenance= (role == UserRole::MAINTENANCE);

    // ALL roles: Fleet Management
    mainLayout->addWidget(makeBtn("🚌 Fleet Management",
        []() -> QWidget* { return new FleetManagementWindow(); }));

    // ADMIN + DISPATCHER: Live Map, Dispatch Console
    if (isAdmin || isDispatcher) {
        mainLayout->addWidget(makeBtn("🗺  Live Map",
            []() -> QWidget* { return new LiveMapWindow(); }));
        mainLayout->addWidget(makeBtn("📡 Dispatch Console",
            []() -> QWidget* { return new DispatchConsoleWindow(); }));
    }

    // ADMIN + DRIVER + CONDUCTOR: Trip Scheduler, Route Builder
    if (isAdmin || isDriver || isConductor) {
        mainLayout->addWidget(makeBtn("📅 Trip Scheduler",
            []() -> QWidget* { return new TripSchedulerWindow(); }));
        mainLayout->addWidget(makeBtn("🗺  Route Builder",
            []() -> QWidget* { return new RouteBuilderWindow(); }));
    }

    // ADMIN + CONDUCTOR: Ticketing
    if (isAdmin || isConductor) {
        mainLayout->addWidget(makeBtn("🎫 Ticketing",
            []() -> QWidget* { return new TicketingWindow(); }));
    }

    // ADMIN + MAINTENANCE: Maintenance
    if (isAdmin || isMaintenance) {
        mainLayout->addWidget(makeBtn("🔧 Maintenance",
            []() -> QWidget* { return new MaintenanceWindow(); }));
    }

    // ADMIN only: Staff Management, Reports
    if (isAdmin) {
        mainLayout->addWidget(makeBtn("👥 Staff Management",
            []() -> QWidget* { return new StaffManagementWindow(); }));
        mainLayout->addWidget(makeBtn("📊 Reports",
            []() -> QWidget* { return new ReportDashboardWindow(); }));
    }

    mainLayout->addStretch();

    // Logout button
    auto* logoutBtn = new QPushButton("🔓 Logout");
    logoutBtn->setMinimumHeight(40);
    logoutBtn->setStyleSheet(
        "background-color: #c0392b; color: white; font-weight: bold;");
    connect(logoutBtn, &QPushButton::clicked, this, [this]() {
        AuthController::getInstance().logout();
        auto* login = new LoginWindow();
        login->setAttribute(Qt::WA_DeleteOnClose);
        login->show();
        this->close();
    });
    mainLayout->addWidget(logoutBtn);
}
