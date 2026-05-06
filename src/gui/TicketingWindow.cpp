#include "gui/TicketingWindow.h"
#include "gui/CommonQt.h"
#include "entities/IFareCalculator.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <cstdio>

TicketingWindow::TicketingWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Ticketing");
    setMinimumSize(500, 450);

    auto* layout = new QVBoxLayout(this);
    auto* title  = new QLabel("Issue Ticket");
    QFont f = title->font(); f.setPointSize(14); f.setBold(true);
    title->setFont(f); title->setAlignment(Qt::AlignCenter);

    auto* form           = new QFormLayout();
    auto* tripIdInput    = new QLineEdit(); tripIdInput->setPlaceholderText("Trip ID");
    auto* passengerInput = new QLineEdit(); passengerInput->setPlaceholderText("Passenger Name");
    auto* fareTypeBox    = new QComboBox();
    fareTypeBox->addItems({"Bus (Flat)", "Metro (Zone)", "RideHail (Surge)",
                           "Freight (Weight)", "Scooter (Micro)"});
    auto* paymentBox = new QComboBox();
    paymentBox->addItems({"Cash", "Transit Card", "QR Code", "Corporate", "Loyalty Points"});
    auto* distanceSpin = new QDoubleSpinBox();
    distanceSpin->setRange(0.1, 999.9); distanceSpin->setValue(5.0);
    distanceSpin->setSuffix(" km");
    auto* peakCheck = new QCheckBox("Peak Hour?");
    auto* fareLabel = new QLabel("Fare: —");
    fareLabel->setStyleSheet("font-weight: bold; color: #27ae60;");

    form->addRow("Trip ID:",       tripIdInput);
    form->addRow("Passenger:",     passengerInput);
    form->addRow("Fare Type:",     fareTypeBox);
    form->addRow("Payment Method:",paymentBox);
    form->addRow("Distance:",      distanceSpin);
    form->addRow("",               peakCheck);
    form->addRow("Calculated:",    fareLabel);

    auto* calcBtn  = new QPushButton("💰 Calculate Fare");
    auto* issueBtn = new QPushButton("🎫 Issue Ticket");
    auto* closeBtn = new QPushButton("Close");

    // Polymorphic fare calculation via IFareCalculator
    connect(calcBtn, &QPushButton::clicked, this, [=]() {
        try {
            IFareCalculator* calc = nullptr;
            switch (fareTypeBox->currentIndex()) {
                case 0: calc = new FlatFareBus();    break;
                case 1: calc = new ZoneBasedMetro(); break;
                case 2: calc = new SurgeRideHail();  break;
                case 3: calc = new WeightFreight();  break;
                case 4: calc = new MicroMobility();  break;
            }
            if (calc) {
                double fare = calc->calculateFare(
                    distanceSpin->value(), 1, peakCheck->isChecked());
                char buf[32]; std::snprintf(buf, sizeof(buf), "PKR %.2f", fare);
                fareLabel->setText(QString("Fare: %1").arg(buf));
                delete calc; calc = nullptr;
            }
        } catch (const std::exception& ex) {
            QMessageBox::warning(this, "Calculation Error", ex.what());
        }
    });

    connect(issueBtn, &QPushButton::clicked, this, [=]() {
        try {
            if (tripIdInput->text().isEmpty() || passengerInput->text().isEmpty())
                throw std::invalid_argument("Trip ID and Passenger Name are required.");
            QMessageBox::information(this, "Ticket Issued",
                QString("✅ Ticket issued!\nPassenger: %1\nTrip: %2\n%3")
                .arg(passengerInput->text())
                .arg(tripIdInput->text())
                .arg(fareLabel->text()));
            tripIdInput->clear(); passengerInput->clear();
            fareLabel->setText("Fare: —");
        } catch (const std::exception& ex) {
            QMessageBox::warning(this, "Error", ex.what());
        }
    });

    connect(closeBtn, &QPushButton::clicked, this, &TicketingWindow::close);

    layout->addWidget(title);
    layout->addLayout(form);
    layout->addWidget(calcBtn);
    layout->addWidget(issueBtn);
    layout->addWidget(closeBtn);
}
