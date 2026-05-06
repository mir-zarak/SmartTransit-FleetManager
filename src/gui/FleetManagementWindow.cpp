#include "gui/FleetManagementWindow.h"
#include "gui/CommonQt.h"

#include "controllers/FleetController.h"
#include "entities/CityBus.h"

FleetManagementWindow::FleetManagementWindow(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);

    auto* title = new QLabel("Fleet Management");
    title->setAlignment(Qt::AlignCenter);

    // 🔹 INPUT FIELDS
    auto* typeInput = new QLineEdit();
    typeInput->setPlaceholderText("Vehicle Type (e.g. Bus)");

    auto* capacityInput = new QLineEdit();
    capacityInput->setPlaceholderText("Capacity");

    // 🔹 BUTTONS
    auto* addBtn = new QPushButton("Add Vehicle");
    auto* deleteBtn = new QPushButton("Delete Selected");

    // 🔹 TABLE
    auto* table = new QTableWidget();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"ID", "Type", "Status", "Capacity"});
    table->horizontalHeader()->setStretchLastSection(true);

    // 🔥 LOAD FUNCTION
    auto loadTable = [=]() {
        auto& fleet = FleetController::getInstance();
        auto& vehicles = fleet.getAllVehicles();

        table->setRowCount(vehicles.size());

        for (int i = 0; i < vehicles.size(); i++) {
            Vehicle* v = vehicles[i];
            if (!v) continue;

            table->setItem(i, 0, new QTableWidgetItem(QString::number(v->getId())));
            table->setItem(i, 1, new QTableWidgetItem(
                QString::fromStdString(v->getVehicleCategory().c_str())
            ));
            table->setItem(i, 2, new QTableWidgetItem("Active"));
            table->setItem(i, 3, new QTableWidgetItem(
                QString::number(v->getPassengerCapacity())
            ));
        }
    };

    loadTable();

    // 🔥 ADD VEHICLE WITH INPUT
    connect(addBtn, &QPushButton::clicked, this, [=]() {
        bool ok;
        int capacity = capacityInput->text().toInt(&ok);

        if (!ok) return; // invalid input

        auto& fleet = FleetController::getInstance();

        // For now always create CityBus (you can expand later)
        auto* bus = new CityBus();
        bus->setPassengerCapacity(capacity);

        fleet.addVehicle(bus);

        loadTable();

        // clear fields
        typeInput->clear();
        capacityInput->clear();
    });

    // 🔥 DELETE
    connect(deleteBtn, &QPushButton::clicked, this, [=]() {
        int row = table->currentRow();

        if (row >= 0) {
            auto& fleet = FleetController::getInstance();
            fleet.removeVehicle(row);
            loadTable();
        }
    });

    layout->addWidget(title);
    layout->addWidget(typeInput);
    layout->addWidget(capacityInput);
    layout->addWidget(addBtn);
    layout->addWidget(deleteBtn);
    layout->addWidget(table);
}