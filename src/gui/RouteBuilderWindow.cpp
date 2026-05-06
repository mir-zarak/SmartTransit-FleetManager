#include "gui/RouteBuilderWindow.h"
#include "gui/CommonQt.h"
#include <stdexcept>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

RouteBuilderWindow::RouteBuilderWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Route Builder");
    setMinimumSize(700, 500);

    auto* layout  = new QVBoxLayout(this);
    auto* title   = new QLabel("Route Builder");
    QFont f = title->font(); f.setPointSize(14); f.setBold(true);
    title->setFont(f); title->setAlignment(Qt::AlignCenter);

    auto* stopInput = new QLineEdit();
    stopInput->setPlaceholderText("Enter stop name (e.g., City Centre)...");
    auto* stopList  = new QListWidget();
    stopList->setAlternatingRowColors(true);
    auto* distLbl   = new QLabel("Total Stops: 0 | Est. Distance: 0.0 km");
    distLbl->setAlignment(Qt::AlignCenter);

    auto* addBtn    = new QPushButton("➕ Add Stop");
    auto* removeBtn = new QPushButton("➖ Remove Selected");
    auto* upBtn     = new QPushButton("⬆ Move Up");
    auto* downBtn   = new QPushButton("⬇ Move Down");
    auto* saveBtn   = new QPushButton("💾 Save Route");
    auto* closeBtn  = new QPushButton("Close");

    auto* btnRow = new QHBoxLayout();
    btnRow->addWidget(addBtn); btnRow->addWidget(removeBtn);
    btnRow->addWidget(upBtn);  btnRow->addWidget(downBtn);

    auto updateStats = [=]() {
        int count = stopList->count();
        // Simple distance estimate: 1.5km per stop interval
        double dist = (count > 1) ? (count - 1) * 1.5 : 0.0;
        distLbl->setText(QString("Total Stops: %1 | Est. Distance: %2 km")
                         .arg(count).arg(dist, 0, 'f', 1));
    };

    connect(addBtn, &QPushButton::clicked, this, [=]() {
        QString stop = stopInput->text().trimmed();
        if (!stop.isEmpty()) {
            stopList->addItem(stop);
            stopInput->clear();
            updateStats();
        } else {
            QMessageBox::warning(this, "Error", "Stop name cannot be empty.");
        }
    });

    connect(removeBtn, &QPushButton::clicked, this, [=]() {
        int row = stopList->currentRow();
        if (row >= 0) { delete stopList->takeItem(row); updateStats(); }
    });

    connect(upBtn, &QPushButton::clicked, this, [=]() {
        int row = stopList->currentRow();
        if (row > 0) {
            auto* item = stopList->takeItem(row);
            stopList->insertItem(row - 1, item);
            stopList->setCurrentRow(row - 1);
        }
    });

    connect(downBtn, &QPushButton::clicked, this, [=]() {
        int row = stopList->currentRow();
        if (row < stopList->count() - 1) {
            auto* item = stopList->takeItem(row);
            stopList->insertItem(row + 1, item);
            stopList->setCurrentRow(row + 1);
        }
    });

    connect(saveBtn, &QPushButton::clicked, this, [=]() {
        try {
            if (stopList->count() < 2)
                throw std::invalid_argument("A route needs at least 2 stops.");
            QMessageBox::information(this, "Route Saved",
                QString("✅ Route saved with %1 stops.").arg(stopList->count()));
        } catch (const std::exception& ex) {
            QMessageBox::warning(this, "Error", ex.what());
        }
    });

    connect(closeBtn, &QPushButton::clicked, this, &RouteBuilderWindow::close);

    layout->addWidget(title);
    layout->addWidget(stopInput);
    layout->addLayout(btnRow);
    layout->addWidget(stopList);
    layout->addWidget(distLbl);
    layout->addWidget(saveBtn);
    layout->addWidget(closeBtn);
}
