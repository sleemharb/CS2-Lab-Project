#include "signup.h"
#include "ui_signup.h"
#include "user.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <vector>
#include <QMessageBox>
#include <QComboBox>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>

using namespace std;

signup::signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);
    this->setWindowTitle("Signup");
    loadUsersFromFile();
    ui->label_passwordError->clear();
}

signup::~signup()
{
    delete ui;
}

bool validatePassword(const QString& password) {
    if (password.length() < 8)
        return false;

    bool numbers = false;
    bool special = false;
    QString specialChars = "!@#$%^&*()_+-=[]{};':\"\\|,.<>/?";

    for (const QChar& c : password) {
        if (c.isDigit())
            numbers = true;
        if (specialChars.contains(c))
            special = true;
    }
    return numbers && special;
}

void signup::on_signupButton_clicked()
{
    ui->label_passwordError->clear();

    QString enteredUsername = ui->lineEdit_Susername->text();
    QString enteredPassword = ui->lineEdit_Spassword->text();
    QString enteredRole = ui->comboBox_Srole->currentText();

    if (enteredUsername.isEmpty() || enteredPassword.isEmpty() || enteredRole.isEmpty()) {
        return;
    }

    if (!validatePassword(enteredPassword)) {
        ui->label_passwordError->setText("Password must be at least 8 characters long, contain at least one number, and at least one special character.");
        ui->label_passwordError->setStyleSheet("color: red;");
        return;
    }

    loadUsersFromFile();
    for (const User& user : users) {
        if (user.getUsername() == enteredUsername) {
            QMessageBox::warning(this, "Duplicate User", "This username already exists.");
            return;
        }
    }

    User newUser(enteredUsername, enteredPassword, enteredRole);
    users.push_back(newUser);
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/users.txt";

    QFile file(filePath);


    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << newUser.toString() << "\n";
        qDebug() << "User successfully written to file: " << newUser.toString();
        file.close();

        QMessageBox::information(this, "User Registered", "User successfully registered!");
        ui->lineEdit_Susername->clear();
        ui->lineEdit_Spassword->clear();
        ui->comboBox_Srole->setCurrentIndex(0);
        ui->label_passwordError->clear();
    } else {
        QMessageBox::critical(this, "File Error", "Could not open users.txt to save user.");
        return;
    }
}


void signup::loadUsersFromFile()
{
    users.clear();
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/users.txt";
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
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

void signup::displayAllUsers()
{
    loadUsersFromFile();
    if (users.empty()) {
        QMessageBox::information(this, "User List", "No users found in the system.");
        return;
    }
    QString userList = "All Users in System:\n\n";
    userList += "Username\tRole\n";
    userList += "------------------------\n";

    for (const User& user : users) {
        userList += user.getUsername() + "\t" + user.getRole() + "\n";
    }

    userList += "\n------------------------\n";
    userList += "Total Users: " + QString::number(users.size());
    QMessageBox::information(this, "User List", userList);
}

void signup::on_displayUsersButton_clicked()
{
    displayAllUsers();
}



