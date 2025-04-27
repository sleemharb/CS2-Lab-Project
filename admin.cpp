// Admin.cpp
#include "Admin.h"
#include "User.h"
#include <iostream>
using namespace std;

vector<User*> Admin::users;

Admin::Admin(const string& username, const string& password)
    : User(username, password, "Admin") {}

bool Admin::hasPermission(const string& permission) const {
    return true; // Admin has all permissions
}

void Admin::createUser(const string& username, const string& password, const string& role) {
    cout << "Creating user: " << username << ", Role: " << role << endl;
    // Simulate creating user (actual creation would need more logic)
}

void Admin::listUsers() const {
    cout << "Listing all users..." << endl;
    // Simulate listing users
}

bool Admin::validatePassword(const string& password) const {
    return this->password == password;
}

void Admin::deleteUser(const string& usernameToDelete) {
    cout << "Deleting user: " << usernameToDelete << endl;
    // Simulate deleting user
}
