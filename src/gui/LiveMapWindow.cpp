#include "gui/LiveMapWindow.h"
#include "gui/CommonQt.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>

// Internal canvas widget — draws schematic city map
class MapCanvas : public QWidget {
    int m_tick{};
public:
    explicit MapCanvas(QWidget* p = nullptr) : QWidget(p) {
        setMinimumSize(650, 400);
        setStyleSheet("background-color: #1a1a2e; border-radius: 8px;");
    }
    void advance() { ++m_tick; update(); }
protected:
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        // Draw route lines
        p.setPen(QPen(QColor(80, 80, 120), 3));
        p.drawLine(60, 200, 580, 200);   // horizontal
        p.drawLine(320, 60,  320, 360);  // vertical
        p.drawLine(60, 200, 180, 80);    // diagonal

        // Draw stops (white circles)
        p.setBrush(Qt::white); p.setPen(QPen(Qt::white, 2));
        for (const QPoint& pt : {QPoint(60,200), QPoint(200,200), QPoint(320,200),
                                  QPoint(450,200), QPoint(580,200), QPoint(320,60),
                                  QPoint(320,360), QPoint(180,80)}) {
            p.drawEllipse(pt, 6, 6);
        }

        // Stop labels
        p.setPen(QColor(200,200,200)); p.setFont(QFont("Arial", 8));
        p.drawText(65, 220,  "Terminal A");
        p.drawText(205, 220, "Stop B");
        p.drawText(325, 220, "City Centre");
        p.drawText(455, 220, "Stop D");
        p.drawText(530, 220, "Terminal E");

        // Animate vehicle 1 along horizontal route
        int x1 = 60 + (m_tick * 8) % 520;
        p.setBrush(QColor(0, 200, 100)); p.setPen(QPen(Qt::green, 2));
        p.drawEllipse(QPoint(x1, 200), 9, 9);
        p.setPen(Qt::green); p.drawText(x1 - 8, 188, "B01");

        // Animate vehicle 2 along vertical route
        int y2 = 60 + (m_tick * 5 + 100) % 300;
        p.setBrush(QColor(50, 150, 255)); p.setPen(QPen(Qt::cyan, 2));
        p.drawEllipse(QPoint(320, y2), 9, 9);
        p.setPen(Qt::cyan); p.drawText(330, y2 - 4, "M01");
    }
};

LiveMapWindow::LiveMapWindow(QWidget* parent) : QWidget(parent), m_timer(new QTimer(this)) {
    setWindowTitle("Live Map — Novaris City");
    setMinimumSize(700, 500);

    auto* layout    = new QVBoxLayout(this);
    auto* title     = new QLabel("🗺  Live City Map");
    QFont f = title->font(); f.setPointSize(13); f.setBold(true);
    title->setFont(f); title->setAlignment(Qt::AlignCenter);

    auto* canvas    = new MapCanvas(this);
    auto* statusLbl = new QLabel("Vehicles active: 2 | Refreshes every 5s");
    statusLbl->setAlignment(Qt::AlignCenter);
    auto* closeBtn  = new QPushButton("Close");

    // BUG 13 FIX: m_timer is a member, not a local — connected to refresh
    connect(m_timer, &QTimer::timeout, this, [=]() {
        canvas->advance();
        statusLbl->setText(QString("Vehicles active: 2 | Tick #%1 | Auto-refreshing every 5s")
                           .arg(m_tick));
        ++m_tick;
    });
    m_timer->start(5000); // 5-second refresh (spec requirement)

    connect(closeBtn, &QPushButton::clicked, this, &LiveMapWindow::close);

    layout->addWidget(title);
    layout->addWidget(canvas);
    layout->addWidget(statusLbl);
    layout->addWidget(closeBtn);
}
