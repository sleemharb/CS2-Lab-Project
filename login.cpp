#include "login.h"
#include "ui_login.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QStandardPaths>
#include "adminwindow.h"
#include "managerwindow.h"
#include "employeewindow.h"


Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Log In");

    // Initialize pointers to role-specific windows
    adminWindow = new class AdminWindow (this);
    managerWindow = new class ManagerWindow (this);
    employeeWindow = new class EmployeeWindow (this);
}

Login::~Login()
{
    delete ui;
    if (adminWindow) delete adminWindow;
    if (managerWindow) delete managerWindow;
    if (employeeWindow) delete employeeWindow;
}

void Login::on_pushButton_LLogin_clicked()
{
    QString enteredUsername = ui->lineEdit_Lusername->text();
    QString enteredPassword = ui->lineEdit_Lpassword->text();

    if (enteredUsername.isEmpty() || enteredPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter both username and password");
        return;
    }
    loadUsersFromFile();
    bool loginSuccess = false;
    QString userRole;

    for (const User& user : users) {
        if (user.getUsername() == enteredUsername && user.getPassword() == enteredPassword) {
            loginSuccess = true;
            userRole = user.getRole();
            break;
        }
    }

    if (loginSuccess) {
        QMessageBox::information(this, "Login Successful","Welcome, " + enteredUsername + "!\nYou are logged in as: " + userRole);

        ui->lineEdit_Lusername->clear();
        ui->lineEdit_Lpassword->clear();
        if (userRole.toLower() == "admin") {
            openAdminWindow();
        }
        else if (userRole.toLower() == "manager") {
            openManagerWindow();
        }
        else if (userRole.toLower() == "employee") {
            openEmployeeWindow();
        }
        else {
            QMessageBox::information(this, "Role Not Recognized","Your role (" + userRole + ") does not have a specific interface.");
            return;
        }

        this->hide();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}

void Login::loadUsersFromFile()
{
    users.clear();
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/users.txt";
    QFile file(filePath);

    qDebug() << "Attempting to load users from:" << filePath;

    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                QStringList parts = line.split(",");
                if (parts.size() >= 3) {
                    QString username = parts[0];
                    QString password = parts[1];
                    QString role = parts[2];

                    User user(username, password, role);
                    users.push_back(user);

                    qDebug() << "Loaded user:" << username << "with role:" << role;
                }
            }
        }

        file.close();
        qDebug() << "Successfully loaded" << users.size() << "users for authentication";
    } else {
        qDebug() << "Users file doesn't exist or couldn't be opened for reading:"
                 << (file.exists() ? file.errorString() : "File doesn't exist yet");
    }
}

void Login::openAdminWindow()
{
    if (!adminWindow) {
        adminWindow = new AdminWindow();
    }
    adminWindow->show();
}

void Login::openManagerWindow()
{
    if (!managerWindow) {
        managerWindow = new ManagerWindow();
    }
    managerWindow->show();
}

void Login::openEmployeeWindow()
{
    if (!employeeWindow) {
        employeeWindow = new EmployeeWindow();
    }
    employeeWindow->show();
}
