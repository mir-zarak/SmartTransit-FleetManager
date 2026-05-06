#include "gui/StaffManagementWindow.h"
#include "gui/CommonQt.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

StaffManagementWindow::StaffManagementWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Staff Management");
    setMinimumSize(700, 500);

    auto* layout = new QVBoxLayout(this);
    auto* title  = new QLabel("Staff Management");
    QFont f = title->font(); f.setPointSize(14); f.setBold(true);
    title->setFont(f);
    title->setAlignment(Qt::AlignCenter);

    auto* table = new QTableWidget();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"ID", "Name", "Role", "On Duty", "Salary (PKR)"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSortIndicatorShown(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);

    // Seed sample data
    auto addRow = [&](const QString& id, const QString& name, const QString& role,
                      const QString& duty, const QString& salary) {
        int row = table->rowCount(); table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(id));
        table->setItem(row, 1, new QTableWidgetItem(name));
        table->setItem(row, 2, new QTableWidgetItem(role));
        table->setItem(row, 3, new QTableWidgetItem(duty));
        table->setItem(row, 4, new QTableWidgetItem(salary));
    };
    addRow("S001", "Ahmed Khan",   "Driver",     "Yes", "45,000");
    addRow("S002", "Sara Ali",     "Conductor",  "No",  "35,000");
    addRow("S003", "Bilal Raza",   "Dispatcher", "Yes", "50,000");
    addRow("S004", "Fatima Noor",  "Admin",      "Yes", "60,000");
    addRow("S005", "Usman Tariq",  "Maintenance","No",  "40,000");

    auto* closeBtn = new QPushButton("Close");
    connect(closeBtn, &QPushButton::clicked, this, &StaffManagementWindow::close);

    layout->addWidget(title);
    layout->addWidget(table);
    layout->addWidget(closeBtn);
}
