#include "controllers/AuthController.h"
#include <cstring>
#include <cstdio>

// ─── Constructor — seeds default accounts ────────────────────────────────────
AuthController::AuthController()
    : m_accountCount(0), m_loggedInIndex(-1), m_isLoggedIn(false) {}

// ─── Singleton ────────────────────────────────────────────────────────────────
AuthController& AuthController::getInstance() {
    static AuthController instance;
    return instance;
}

// ─── Simple password hash (no std::string, no external libs) ─────────────────
// Combines char values with position to produce a numeric hash as CustomString
CustomString AuthController::hashPassword(const CustomString& password) const {
    unsigned long hash = 5381;
    for (int i = 0; i < password.length(); ++i) {
        hash = ((hash << 5) + hash) +
               static_cast<unsigned char>(password[i]); // hash * 33 + c
    }
    // convert to hex string manually
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%lu", hash);
    return CustomString(buf);
}

// ─── Find user index by username (-1 if not found) ───────────────────────────
int AuthController::findUser(const CustomString& username) const {
    for (int i = 0; i < m_accountCount; ++i) {
        if (m_accounts[i].username == username)
            return i;
    }
    return -1;
}

// ─── Initialize — create default accounts ────────────────────────────────────
void AuthController::initialize() {
    // Admin account
    m_accounts[m_accountCount++] = UserAccount(
        CustomString("admin"),
        hashPassword(CustomString("admin123")),
        UserRole::ADMIN
        );
    // Driver account
    m_accounts[m_accountCount++] = UserAccount(
        CustomString("driver1"),
        hashPassword(CustomString("drive123")),
        UserRole::DRIVER
        );
    // Conductor account
    m_accounts[m_accountCount++] = UserAccount(
        CustomString("conductor1"),
        hashPassword(CustomString("cond123")),
        UserRole::CONDUCTOR
        );
    // Dispatcher account
    m_accounts[m_accountCount++] = UserAccount(
        CustomString("dispatch1"),
        hashPassword(CustomString("disp123")),
        UserRole::DISPATCHER
        );
    // Maintenance account
    m_accounts[m_accountCount++] = UserAccount(
        CustomString("tech1"),
        hashPassword(CustomString("tech123")),
        UserRole::MAINTENANCE
        );
}

// ─── Login ────────────────────────────────────────────────────────────────────
bool AuthController::login(const CustomString& username,
                           const CustomString& password) {
    int idx = findUser(username);

    // User not found
    if (idx == -1) return false;

    // Account locked
    if (m_accounts[idx].isLocked) return false;

    // Check password
    if (m_accounts[idx].passwordHash == hashPassword(password)) {
        m_accounts[idx].failedAttempts = 0;
        m_loggedInIndex = idx;
        m_isLoggedIn    = true;
        return true;
    }

    // Wrong password — increment failed attempts
    m_accounts[idx].failedAttempts++;
    if (m_accounts[idx].failedAttempts >= MAX_FAILED_ATTEMPTS)
        m_accounts[idx].isLocked = true;

    return false;
}

// ─── Logout ───────────────────────────────────────────────────────────────────
void AuthController::logout() {
    m_loggedInIndex = -1;
    m_isLoggedIn    = false;
}

// ─── Session queries ──────────────────────────────────────────────────────────
bool AuthController::isLoggedIn() const {
    return m_isLoggedIn;
}

UserRole AuthController::getCurrentRole() const {
    if (!m_isLoggedIn || m_loggedInIndex == -1)
        return UserRole::GUEST;
    return m_accounts[m_loggedInIndex].role;
}

CustomString AuthController::getCurrentUser() const {
    if (!m_isLoggedIn || m_loggedInIndex == -1)
        return CustomString("Guest");
    return m_accounts[m_loggedInIndex].username;
}

bool AuthController::isAdmin() const {
    return getCurrentRole() == UserRole::ADMIN;
}

// ─── Account management ───────────────────────────────────────────────────────
bool AuthController::isAccountLocked(const CustomString& username) const {
    int idx = findUser(username);
    return idx != -1 && m_accounts[idx].isLocked;
}

void AuthController::resetLock(const CustomString& username) {
    int idx = findUser(username);
    if (idx != -1) {
        m_accounts[idx].isLocked       = false;
        m_accounts[idx].failedAttempts  = 0;
    }
}

int AuthController::getFailedAttempts(const CustomString& username) const {
    int idx = findUser(username);
    return idx != -1 ? m_accounts[idx].failedAttempts : 0;
}