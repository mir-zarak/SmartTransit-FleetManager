#pragma once
#include "utilities/CustomString.h"

enum class UserRole {
    ADMIN,
    DRIVER,
    CONDUCTOR,
    DISPATCHER,
    MAINTENANCE,
    GUEST
};

struct UserAccount {
    CustomString username;
    CustomString passwordHash;
    UserRole     role;
    bool         isLocked;
    int          failedAttempts;

    UserAccount() : role(UserRole::GUEST), isLocked(false), failedAttempts(0) {}

    UserAccount(const CustomString& u, const CustomString& ph, UserRole r)
        : username(u), passwordHash(ph),
        role(r), isLocked(false), failedAttempts(0) {}
};

class AuthController {
private:


    UserAccount  m_accounts[10];   // fixed max 10 users (no std::vector)
    int          m_accountCount;
    int          m_loggedInIndex;  // -1 = nobody logged in
    bool         m_isLoggedIn;

    AuthController();

    // Prevent copying — Singleton
    AuthController(const AuthController&)            = delete;
    AuthController& operator=(const AuthController&) = delete;

    // Simple hash — sums char values with position multiplier
    CustomString hashPassword(const CustomString& password) const;

    int findUser(const CustomString& username) const;

public:
    static constexpr int MAX_FAILED_ATTEMPTS = 3;
    static AuthController& getInstance();

    void initialize();

    // Login / Logout
    bool         login(const CustomString& username,
               const CustomString& password);
    void         logout();

    // Session queries
    bool         isLoggedIn()       const;
    UserRole     getCurrentRole()   const;
    CustomString getCurrentUser()   const;
    bool         isAdmin()          const;

    // Account management
    bool         isAccountLocked(const CustomString& username) const;
    void         resetLock(const CustomString& username);
    int          getFailedAttempts(const CustomString& username) const;
};