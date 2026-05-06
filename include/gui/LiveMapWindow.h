#pragma once
#include <QWidget>
#include <QMessageBox>
#include <QTimer>

class LiveMapWindow : public QWidget {
    Q_OBJECT
private:
    QTimer* m_timer;   // BUG 13 FIX: member variable (spec requirement)
    int     m_tick{};

public:
    explicit LiveMapWindow(QWidget* parent = nullptr);
};
