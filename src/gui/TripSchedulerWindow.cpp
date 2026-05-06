#include "gui/TripSchedulerWindow.h"
#include "gui/CommonQt.h"
#include <stdexcept>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QCalendarWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

TripSchedulerWindow::TripSchedulerWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Trip Scheduler");
    setMinimumSize(700, 600);

    auto* layout = new QVBoxLayout(this);
    auto* title  = new QLabel("📅 Trip Scheduler");
    QFont f = title->font(); f.setPointSize(13); f.setBold(true);
    title->setFont(f); title->setAlignment(Qt::AlignCenter);

    auto* calendar = new QCalendarWidget();
    calendar->setMinimumDate(QDate::currentDate());
    calendar->setMaximumHeight(220);

    auto* vehicleInput = new QLineEdit(); vehicleInput->setPlaceholderText("Vehicle ID (e.g., BUS-001)");
    auto* driverInput  = new QLineEdit(); driverInput->setPlaceholderText("Driver ID (e.g., DRV-042)");
    auto* routeBox     = new QComboBox();
    routeBox->addItems({"Route A — Terminal to City Centre",
                        "Route B — North Suburb to Station",
                        "Route C — East Zone Loop",
                        "Line 1 — Metro Blue Line",
                        "Line 2 — Metro Red Line"});
    auto* timeInput = new QLineEdit(); timeInput->setPlaceholderText("Departure Time (HH:MM, 24h)");

    auto* form = new QFormLayout();
    form->addRow("Vehicle:",   vehicleInput);
    form->addRow("Driver:",    driverInput);
    form->addRow("Route:",     routeBox);
    form->addRow("Dep. Time:", timeInput);

    auto* scheduleBtn = new QPushButton("✅ Schedule Trip");
    scheduleBtn->setMinimumHeight(40);
    auto* closeBtn    = new QPushButton("Close");

    connect(scheduleBtn, &QPushButton::clicked, this, [=]() {
        try {
            if (vehicleInput->text().isEmpty())
                throw std::invalid_argument("Vehicle ID is required.");
            if (driverInput->text().isEmpty())
                throw std::invalid_argument("Driver ID is required.");
            if (timeInput->text().isEmpty())
                throw std::invalid_argument("Departure time is required.");
            // Simple HH:MM format check
            QString t = timeInput->text().trimmed();
            if (t.length() != 5 || t[2] != ':')
                throw std::invalid_argument("Time must be in HH:MM format.");

            QMessageBox::information(this, "Trip Scheduled",
                QString("✅ Trip scheduled!\n\nDate:    %1\nVehicle: %2\nDriver:  %3\nRoute:   %4\nTime:    %5")
                .arg(calendar->selectedDate().toString("dd MMM yyyy"))
                .arg(vehicleInput->text())
                .arg(driverInput->text())
                .arg(routeBox->currentText())
                .arg(timeInput->text()));
        } catch (const std::exception& ex) {
            QMessageBox::warning(this, "Scheduling Error", ex.what());
        }
    });

    connect(closeBtn, &QPushButton::clicked, this, &TripSchedulerWindow::close);

    layout->addWidget(title);
    layout->addWidget(calendar);
    layout->addLayout(form);
    layout->addWidget(scheduleBtn);
    layout->addWidget(closeBtn);
}
