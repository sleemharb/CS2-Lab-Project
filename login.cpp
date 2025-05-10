#include "login.h"
#include "ui_login.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
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
        ui->label_loginError->setText("Please enter both username and password.");
        ui->label_loginError->setStyleSheet("color: red;");
        return;
    }
    loadUsersFromFile();
    bool loginSuccess = false;
    QString userRole;

    for (const User& user : users) {
        if (user.getUsername() == enteredUsername && user.getPassword() == enteredPassword) {
            loginSuccess = true;
            userRole = user.getRole();
            ui->label_loginError->clear();
            break;
        }
    }

    if (loginSuccess) {
        QMessageBox::information(this, "Login Successful","Welcome, " + enteredUsername + "!\nYou are logged in as: " + userRole);

        ui->lineEdit_Lusername->clear();
        ui->lineEdit_Lpassword->clear();
        ui->label_loginError->clear();
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
        ui->label_loginError->setText("Incorrect username or password.");
        ui->label_loginError->setStyleSheet("color: red;");
    }
}

void Login::loadUsersFromFile()
{
    users.clear();
    QString filePath = "../../users.txt";
    QFile file(filePath);

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
                }
            }
        }

        file.close();
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
