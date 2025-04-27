// User.cpp
#include "User.h"

// Constructor
User::User(const QString& username, const QString& password, const QString& role)
    : username(username), password(password), role(role) {}

// Getter functions
QString User::getUsername() const { return username; }
QString User::getPassword() const { return password; }
QString User::getRole() const { return role; }

// Setter functions
void User::setUsername(const QString& uname) { username = uname; }
void User::setPassword(const QString& pword) { password = pword; }
void User::setRole(const QString& r) { role = r; }

// Convert user to a string (for saving to file)
QString User::toString() const {
    return username + "," + password + "," + role;
}
