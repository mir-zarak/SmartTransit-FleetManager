#include "gui/VehicleProfileDialog.h"
#include "gui/CommonQt.h"
#include "controllers/FleetController.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>

VehicleProfileDialog::VehicleProfileDialog(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Vehicle Profile");
    setMinimumSize(700, 500);

    auto* layout = new QVBoxLayout(this);
    auto* title  = new QLabel("🚌 Vehicle Profile");
    QFont f = title->font(); f.setPointSize(13); f.setBold(true);
    title->setFont(f); title->setAlignment(Qt::AlignCenter);

    auto* tabs = new QTabWidget();

    // ── Tab 1: Details ─────────────────────────────────────────────
    auto* detailsTab    = new QWidget();
    auto* detailsLayout = new QFormLayout(detailsTab);
    detailsLayout->addRow("Registration No:", new QLabel("BUS-001"));
    detailsLayout->addRow("Category:",        new QLabel("CityBus"));
    detailsLayout->addRow("Make / Model:",    new QLabel("Hino / Rainbow"));
    detailsLayout->addRow("Fuel Type:",       new QLabel("CNG"));
    detailsLayout->addRow("Capacity:",        new QLabel("45 passengers"));
    detailsLayout->addRow("Odometer:",        new QLabel("52,340 km"));
    detailsLayout->addRow("Status:",          new QLabel("✅ Active"));
    detailsLayout->addRow("Assigned Driver:", new QLabel("Ahmed Khan (DRV-001)"));
    tabs->addTab(detailsTab, "Details");

    // ── Tab 2: Trip History ────────────────────────────────────────
    auto* tripTab    = new QWidget();
    auto* tripLayout = new QVBoxLayout(tripTab);
    auto* tripTable  = new QTableWidget(0, 4);
    tripTable->setHorizontalHeaderLabels({"Trip ID", "Route", "Date", "Passengers"});
    tripTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tripTable->horizontalHeader()->setSortIndicatorShown(true);
    tripTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tripTable->setAlternatingRowColors(true);
    auto addTrip = [&](const QString& id, const QString& r, const QString& d, const QString& p) {
        int row = tripTable->rowCount(); tripTable->insertRow(row);
        tripTable->setItem(row, 0, new QTableWidgetItem(id));
        tripTable->setItem(row, 1, new QTableWidgetItem(r));
        tripTable->setItem(row, 2, new QTableWidgetItem(d));
        tripTable->setItem(row, 3, new QTableWidgetItem(p));
    };
    addTrip("TRP-201", "Route A", "18 Apr 2026", "38");
    addTrip("TRP-198", "Route A", "17 Apr 2026", "42");
    addTrip("TRP-195", "Route B", "17 Apr 2026", "29");
    tripLayout->addWidget(tripTable);
    tabs->addTab(tripTab, "Trip History");

    // ── Tab 3: Maintenance Log ─────────────────────────────────────
    auto* maintTab    = new QWidget();
    auto* maintLayout = new QVBoxLayout(maintTab);
    auto* maintTable  = new QTableWidget(0, 4);
    maintTable->setHorizontalHeaderLabels({"Job ID", "Description", "Date", "Cost (PKR)"});
    maintTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    maintTable->horizontalHeader()->setSortIndicatorShown(true);
    maintTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    maintTable->setAlternatingRowColors(true);
    auto addMaint = [&](const QString& id, const QString& d, const QString& dt, const QString& c) {
        int row = maintTable->rowCount(); maintTable->insertRow(row);
        maintTable->setItem(row, 0, new QTableWidgetItem(id));
        maintTable->setItem(row, 1, new QTableWidgetItem(d));
        maintTable->setItem(row, 2, new QTableWidgetItem(dt));
        maintTable->setItem(row, 3, new QTableWidgetItem(c));
    };
    addMaint("MJ-055", "Tyre Replacement",    "10 Apr 2026", "12,500");
    addMaint("MJ-041", "Brake Fluid Service", "01 Mar 2026", "3,200");
    addMaint("MJ-030", "Engine Oil Change",   "15 Jan 2026", "2,800");
    maintLayout->addWidget(maintTable);
    tabs->addTab(maintTab, "Maintenance Log");

    // ── Tab 4: Fuel Log ────────────────────────────────────────────
    auto* fuelTab    = new QWidget();
    auto* fuelLayout = new QVBoxLayout(fuelTab);
    auto* fuelTable  = new QTableWidget(0, 4);
    fuelTable->setHorizontalHeaderLabels({"Date", "Litres", "Rate (PKR/L)", "Total Cost (PKR)"});
    fuelTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    fuelTable->horizontalHeader()->setSortIndicatorShown(true);
    fuelTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    fuelTable->setAlternatingRowColors(true);
    auto addFuel = [&](const QString& d, const QString& l, const QString& r, const QString& c) {
        int row = fuelTable->rowCount(); fuelTable->insertRow(row);
        fuelTable->setItem(row, 0, new QTableWidgetItem(d));
        fuelTable->setItem(row, 1, new QTableWidgetItem(l));
        fuelTable->setItem(row, 2, new QTableWidgetItem(r));
        fuelTable->setItem(row, 3, new QTableWidgetItem(c));
    };
    addFuel("18 Apr 2026", "40.0", "290", "11,600");
    addFuel("15 Apr 2026", "35.5", "290", "10,295");
    addFuel("12 Apr 2026", "42.0", "285", "11,970");
    fuelLayout->addWidget(fuelTable);
    tabs->addTab(fuelTab, "Fuel Log");

    auto* closeBtn = new QPushButton("Close");
    connect(closeBtn, &QPushButton::clicked, this, &VehicleProfileDialog::close);

    layout->addWidget(title);
    layout->addWidget(tabs);
    layout->addWidget(closeBtn);
}
