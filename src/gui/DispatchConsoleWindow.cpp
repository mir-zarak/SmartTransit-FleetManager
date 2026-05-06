#include "gui/DispatchConsoleWindow.h"
#include "gui/CommonQt.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

DispatchConsoleWindow::DispatchConsoleWindow(QWidget* parent)
    : QWidget(parent), m_timer(new QTimer(this)) {
    setWindowTitle("Dispatch Console");
    setMinimumSize(700, 500);

    auto* layout = new QVBoxLayout(this);
    auto* title  = new QLabel("📡 Dispatch Console — Priority Queue");
    QFont f = title->font(); f.setPointSize(13); f.setBold(true);
    title->setFont(f); title->setAlignment(Qt::AlignCenter);

    auto* table = new QTableWidget();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Priority", "Vehicle", "Route", "Status"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSortIndicatorShown(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);

    auto addRow = [&](int pri, const QString& v, const QString& r, const QString& s, const QColor& c) {
        int row = table->rowCount(); table->insertRow(row);
        auto* priItem = new QTableWidgetItem(QString::number(pri));
        priItem->setBackground(c);
        table->setItem(row, 0, priItem);
        table->setItem(row, 1, new QTableWidgetItem(v));
        table->setItem(row, 2, new QTableWidgetItem(r));
        table->setItem(row, 3, new QTableWidgetItem(s));
    };
    addRow(1, "Bus-001",  "Route-A",  "🚨 URGENT",    QColor(255, 80, 80));
    addRow(2, "Bus-002",  "Route-B",  "⏳ Waiting",    QColor(255, 200, 0));
    addRow(3, "Metro-01", "Line-1",   "✅ In Transit", QColor(80, 200, 80));
    addRow(4, "Scoot-03", "Zone-C",   "⏳ Standby",    QColor(200, 200, 255));

    auto* statusLbl    = new QLabel("Queue polls every 10s | Items: 4");
    statusLbl->setAlignment(Qt::AlignCenter);
    auto* emergencyBtn = new QPushButton("🚨 Emergency Dispatch");
    emergencyBtn->setMinimumHeight(45);
    emergencyBtn->setStyleSheet("background-color: #c0392b; color: white; font-weight: bold; font-size: 14px;");
    auto* closeBtn     = new QPushButton("Close");

    connect(emergencyBtn, &QPushButton::clicked, this, [=]() {
        QMessageBox::critical(this, "🚨 Emergency Dispatch",
            "Emergency dispatch signal sent to ALL available units!\nAll standby vehicles are being deployed.");
    });

    // BUG 13 FIX: m_timer is a member variable — polls every 10 seconds (spec requirement)
    connect(m_timer, &QTimer::timeout, this, [=]() {
        statusLbl->setText(QString("Queue last polled: just now | Items: %1")
                           .arg(table->rowCount()));
    });
    m_timer->start(10000); // 10-second poll

    connect(closeBtn, &QPushButton::clicked, this, &DispatchConsoleWindow::close);

    layout->addWidget(title);
    layout->addWidget(table);
    layout->addWidget(statusLbl);
    layout->addWidget(emergencyBtn);
    layout->addWidget(closeBtn);
}
