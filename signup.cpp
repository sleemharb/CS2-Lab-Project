#include "signup.h"
#include "ui_signup.h"
#include "user.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <vector>
#include <QMessageBox>
#include <QDebug>
#include <QComboBox>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>

signup::signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);
    this->setWindowTitle("Signup");
    loadUsersFromFile();
}

signup::~signup()
{
    delete ui;
}

void signup::on_signupButton_clicked()
{
    QString enteredUsername = ui->lineEdit_Susername->text();
    QString enteredPassword = ui->lineEdit_Spassword->text();
    QString enteredRole = ui->comboBox_Srole->currentText(); // Get selected role from combo box

    // Validate input
    if (enteredUsername.isEmpty() || enteredPassword.isEmpty() || enteredRole.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields (username, password, role).");
        return;
    }

    // Load existing users first to check for duplicates
    loadUsersFromFile();

    // Check for duplicate username
    for (const User& user : users) {
        if (user.getUsername() == enteredUsername) {
            QMessageBox::warning(this, "Duplicate User", "This username already exists.");
            return;
        }
    }

    // Create new user
    User newUser(enteredUsername, enteredPassword, enteredRole);
    users.push_back(newUser);

    // Get file path dynamically
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/users.txt";

    // Debug the file path to make sure we're writing to the expected location
    qDebug() << "Writing to file path:" << filePath;

    // Make sure the directory exists
    QDir dir = QFileInfo(filePath).dir();
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Save to file
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Write all users to the file
        for (const User& user : users) {
            out << user.toString() << "\n";
            qDebug() << "Writing user:" << user.toString();
        }

        file.close();
        QMessageBox::information(this, "User Registered", "User successfully registered!");

        // Clear input fields
        ui->lineEdit_Susername->clear();
        ui->lineEdit_Spassword->clear();
        ui->comboBox_Srole->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "File Error", "Could not open users.txt to save user. Error: " + file.errorString());
        qDebug() << "File open error:" << file.errorString();
        return;
    }
}

void signup::loadUsersFromFile()
{
    // Clear existing users
    users.clear();

    // Get file path dynamically
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/users.txt";
    QFile file(filePath);

    qDebug() << "Attempting to load users from:" << filePath;

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
        qDebug() << "Successfully loaded" << users.size() << "users";
    } else {
        qDebug() << "Users file doesn't exist or couldn't be opened for reading:" << file.errorString();
    }
}

// Add this function to your signup class
void signup::displayAllUsers()
{
    // First refresh the vector from file to ensure we have the latest data
    loadUsersFromFile();

    // Check if we have any users
    if (users.empty()) {
        QMessageBox::information(this, "User List", "No users found in the system.");
        return;
    }

    // Create a string to display all users
    QString userList = "All Users in System:\n\n";
    userList += "Username\tRole\n";
    userList += "------------------------\n";

    // Add each user to the list
    for (const User& user : users) {
        userList += user.getUsername() + "\t" + user.getRole() + "\n";
    }

    // Add summary
    userList += "\n------------------------\n";
    userList += "Total Users: " + QString::number(users.size());

    // Display the list in a message box
    QMessageBox::information(this, "User List", userList);
}

void signup::on_displayUsersButton_clicked()
{
    displayAllUsers();
}

