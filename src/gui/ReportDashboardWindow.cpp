#include "gui/ReportDashboardWindow.h"
#include "gui/CommonQt.h"
#include "entities/IReportGenerator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QTextBrowser>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>

ReportDashboardWindow::ReportDashboardWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Report Dashboard");
    setMinimumSize(700, 500);

    auto* layout = new QVBoxLayout(this);
    auto* title  = new QLabel("📊 Report Dashboard");
    QFont f = title->font(); f.setPointSize(13); f.setBold(true);
    title->setFont(f); title->setAlignment(Qt::AlignCenter);

    auto* reportBox = new QComboBox();
    reportBox->addItems({"Fleet Utilisation", "Revenue", "Emissions",
                         "Incidents", "Driver Performance", "Route Efficiency"});

    auto* preview = new QTextBrowser();
    preview->setMinimumHeight(250);

    auto* genBtn    = new QPushButton("📋 Generate Report");
    auto* exportBtn = new QPushButton("💾 Export CSV");
    auto* closeBtn  = new QPushButton("Close");

    auto* btnRow = new QHBoxLayout();
    btnRow->addWidget(genBtn);
    btnRow->addWidget(exportBtn);
    btnRow->addWidget(closeBtn);

    // Polymorphic report generation via IReportGenerator
    connect(genBtn, &QPushButton::clicked, this, [=]() {
        try {
            IReportGenerator* gen = nullptr;
            switch (reportBox->currentIndex()) {
                case 0: gen = new FleetUtilisationReport();   break;
                case 1: gen = new RevenueReport();            break;
                case 2: gen = new EmissionsReport();          break;
                case 3: gen = new IncidentReport();           break;
                case 4: gen = new DriverPerformanceReport();  break;
                case 5: gen = new RouteEfficiencyReport();    break;
            }
            if (gen) {
                CustomString result = gen->generateReport();
                preview->setText(QString::fromUtf8(result.c_str()));
                delete gen; gen = nullptr;
            }
        } catch (const std::exception& ex) {
            QMessageBox::critical(this, "Report Error", ex.what());
        }
    });

    connect(exportBtn, &QPushButton::clicked, this, [=]() {
        try {
            QString path = QFileDialog::getSaveFileName(
                this, "Export CSV", "report.csv", "CSV Files (*.csv)");
            if (!path.isEmpty()) {
                IReportGenerator* gen = nullptr;
                switch (reportBox->currentIndex()) {
                    case 0: gen = new FleetUtilisationReport();  break;
                    case 1: gen = new RevenueReport();           break;
                    case 2: gen = new EmissionsReport();         break;
                    case 3: gen = new IncidentReport();          break;
                    case 4: gen = new DriverPerformanceReport(); break;
                    case 5: gen = new RouteEfficiencyReport();   break;
                }
                if (gen) {
                    gen->exportCSV(CustomString(path.toUtf8().constData()));
                    delete gen; gen = nullptr;
                    QMessageBox::information(this, "Exported",
                        QString("✅ Report exported to:\n%1").arg(path));
                }
            }
        } catch (const std::exception& ex) {
            QMessageBox::critical(this, "Export Error", ex.what());
        }
    });

    connect(closeBtn, &QPushButton::clicked, this, &ReportDashboardWindow::close);

    layout->addWidget(title);
    layout->addWidget(reportBox);
    layout->addWidget(preview);
    layout->addLayout(btnRow);
}
