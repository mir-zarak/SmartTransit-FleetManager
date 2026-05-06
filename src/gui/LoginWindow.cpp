#include "gui/LoginWindow.h"
#include "gui/MainDashboard.h"
#include "gui/CommonQt.h"
#include "controllers/AuthController.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("SmartTransit EMS - Login");
    setFixedSize(350, 250);

    auto* layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(40, 30, 40, 30);

    auto* title = new QLabel("SmartTransit Login");
    title->setAlignment(Qt::AlignCenter);

    auto* usernameInput = new QLineEdit();
    usernameInput->setPlaceholderText("Username");

    auto* passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);

    auto* loginBtn = new QPushButton("Login");

    layout->addWidget(title);
    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addWidget(loginBtn);

    connect(loginBtn, &QPushButton::clicked, this, [=]() {
        QString user = usernameInput->text().trimmed();
        QString pass = passwordInput->text();

        // Empty field check
        if (user.isEmpty() || pass.isEmpty()) {
            QMessageBox::warning(this, "Login Failed",
                                 "Username and password cannot be empty.");
            return;
        }

        CustomString csUser(user.toStdString().c_str());
        CustomString csPass(pass.toStdString().c_str());

        auto& auth = AuthController::getInstance();

        // Check if account is locked
        if (auth.isAccountLocked(csUser)) {
            int attempts = auth.getFailedAttempts(csUser);
            QMessageBox::critical(this, "Account Locked",
                                  QString("Account locked after %1 failed attempts.\n"
                                          "Contact administrator.").arg(attempts));
            return;
        }

        // Attempt login
        if (auth.login(csUser, csPass)) {
            auto* dashboard = new MainDashboard();
            dashboard->setAttribute(Qt::WA_DeleteOnClose);
            dashboard->show();
            this->close();
        } else {
            int remaining = AuthController::MAX_FAILED_ATTEMPTS -
                            auth.getFailedAttempts(csUser);

            if (auth.isAccountLocked(csUser)) {
                QMessageBox::critical(this, "Account Locked",
                                      "Too many failed attempts. Account is now locked.");
            } else {
                QMessageBox::warning(this, "Access Denied",
                                     QString("Invalid credentials. %1 attempt(s) remaining.")
                                         .arg(remaining));
            }
            passwordInput->clear();
            passwordInput->setFocus();
        }
    });
}