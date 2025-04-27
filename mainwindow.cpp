#include "mainwindow.h"
#include "ui_mainwindow.h"
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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signupButton_clicked()
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
    QString filePath = QCoreApplication::applicationDirPath() + "/users.txt";
    QFile file(filePath);

    // Debug the file path to make sure we're writing to the expected location
    qDebug() << "Writing to file path:" << filePath;

    // Save to file
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {  // Use WriteOnly instead of Append to rewrite the entire file
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
        QMessageBox::critical(this, "File Error", "Could not open users.txt to save user.");
        qDebug() << "File open error:" << file.errorString();
        return;
    }
}

// Add this method to your MainWindow class
void MainWindow::loadUsersFromFile()
{
    // Clear existing users
    users.clear();

    // Get file path dynamically
    QString filePath = QCoreApplication::applicationDirPath() + "/users.txt";
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

                    qDebug() << "Loaded user:" << username << "with role:" << role;
                }
            }
        }

        file.close();
    } else {
        qDebug() << "Users file doesn't exist or couldn't be opened for reading";
    }
    }





