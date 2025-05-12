#include "login.h"
#include "ui_login.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardPaths>
#include "adminwindow.h"
#include "managerwindow.h"
#include "employeewindow.h"
#include "user.h"


Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
    , adminWindow(nullptr)
    , managerWindow(nullptr)
    , employeeWindow(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Log In");
}

Login::~Login()
{
    delete ui;
    delete adminWindow;
    delete managerWindow;
    delete employeeWindow;
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
    User loggedInUser("", "", ""); // Initialize with default values to avoid potential issues

    for (const User& user : users) {
        if (user.getUsername() == enteredUsername && user.getPassword() == enteredPassword) {
            loginSuccess = true;
            loggedInUser = user; // Assign the found user object
            ui->label_loginError->clear();
            break;
        }
    }

    if (loginSuccess) {
        QMessageBox::information(this, "Login Successful","Welcome, " + loggedInUser.getUsername() + "!\nYou are logged in as: " + loggedInUser.getRole());

        ui->lineEdit_Lusername->clear();
        ui->lineEdit_Lpassword->clear();
        ui->label_loginError->clear();
        if (loggedInUser.getRole().toLower() == "admin") {
            openAdminWindow();
        }
        else if (loggedInUser.getRole().toLower() == "manager") {
            openManagerWindow(loggedInUser);
        }
        else if (loggedInUser.getRole().toLower() == "employee") {
            openEmployeeWindow();
        }
        else {
            QMessageBox::information(this, "Role Not Recognized","Your role (" + loggedInUser.getRole() + ") does not have a specific interface.");
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
    QString filePath = "/Users/Xenaragy/Desktop/InventoryProject/users.txt";
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
        adminWindow = new AdminWindow(this);
    }
    adminWindow->show();
}

void Login::openManagerWindow(const User& loggedInUser)
{
    if (!managerWindow) {
        managerWindow = new ManagerWindow(loggedInUser, this);
    } else {
        managerWindow->show();
    }
}

void Login::openEmployeeWindow()
{
    if (!employeeWindow) {
        employeeWindow = new EmployeeWindow(this);
    }
    employeeWindow->show();
}
