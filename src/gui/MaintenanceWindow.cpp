#include "gui/MaintenanceWindow.h"
#include "gui/CommonQt.h"
#include <stdexcept>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

MaintenanceWindow::MaintenanceWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Maintenance Management");
    setMinimumSize(700, 500);

    auto* layout = new QVBoxLayout(this);
    auto* title  = new QLabel("Maintenance Jobs");
    QFont f = title->font(); f.setPointSize(14); f.setBold(true);
    title->setFont(f); title->setAlignment(Qt::AlignCenter);

    auto* vehicleInput = new QLineEdit(); vehicleInput->setPlaceholderText("Vehicle ID");
    auto* descInput    = new QLineEdit(); descInput->setPlaceholderText("Job Description");
    auto* costInput    = new QLineEdit(); costInput->setPlaceholderText("Estimated Cost (PKR)");
    auto* dateEdit     = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);

    auto* form = new QFormLayout();
    form->addRow("Vehicle ID:",      vehicleInput);
    form->addRow("Description:",     descInput);
    form->addRow("Estimated Cost:",  costInput);
    form->addRow("Scheduled Date:",  dateEdit);

    auto* table = new QTableWidget();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Vehicle ID", "Description", "Cost (PKR)", "Date"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSortIndicatorShown(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);

    auto* addBtn   = new QPushButton("🔧 Schedule Job");
    auto* closeBtn = new QPushButton("Close");

    connect(addBtn, &QPushButton::clicked, this, [=]() {
        try {
            if (vehicleInput->text().isEmpty() || descInput->text().isEmpty())
                throw std::invalid_argument("Vehicle ID and Description are required.");
            int row = table->rowCount();
            table->insertRow(row);
            table->setItem(row, 0, new QTableWidgetItem(vehicleInput->text()));
            table->setItem(row, 1, new QTableWidgetItem(descInput->text()));
            table->setItem(row, 2, new QTableWidgetItem(costInput->text().isEmpty() ? "TBD" : costInput->text()));
            table->setItem(row, 3, new QTableWidgetItem(dateEdit->date().toString("dd/MM/yyyy")));
            vehicleInput->clear(); descInput->clear(); costInput->clear();
        } catch (const std::exception& ex) {
            QMessageBox::warning(this, "Error", ex.what());
        }
    });

    connect(closeBtn, &QPushButton::clicked, this, &MaintenanceWindow::close);

    layout->addWidget(title);
    layout->addLayout(form);
    layout->addWidget(addBtn);
    layout->addWidget(table);
    layout->addWidget(closeBtn);
}
