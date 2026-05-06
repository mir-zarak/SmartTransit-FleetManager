#pragma once
#include <QWidget>
#include <QMessageBox>
#include <QTimer>

class DispatchConsoleWindow : public QWidget {
    Q_OBJECT
private:
    QTimer* m_timer;   // BUG 13 FIX: must be member variable, not local

public:
    explicit DispatchConsoleWindow(QWidget* parent = nullptr);
};
