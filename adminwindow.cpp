#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QMainWindow>
#include <QStandardPaths>
#include <QListWidgetItem>

AdminWindow::AdminWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Page");
    loadUsersFromFile();
    refreshUserList();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_deleteUser_clicked()
{
    QListWidgetItem* currentItem = ui->listWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Error", "Please select a user to delete.");
        return;
    }

    QString username = currentItem->text();

    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(this, "Confirm Deletion","Are you sure you want to delete user '" + username + "'?", QMessageBox::Yes | QMessageBox::No);

    if (confirm == QMessageBox::Yes) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->getUsername() == username) {
                users.erase(it);
                break;
            }
        }
        saveUsersToFile();
        refreshUserList();
        QMessageBox::information(this, "User Deleted", "User '" + username + "' has been deleted.");
    }

}

void AdminWindow::on_adminLogout_clicked()
{
    this->close();
    if (parentWidget()) {
        parentWidget()->show();
    }
}
void AdminWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString username = item->text();
    for (const User& user : users) {
        if (user.getUsername() == username) {
            QString details = "Username: " + user.getUsername() + "\n"+ "Role: " + user.getRole();
            QMessageBox::information(this, "User Details", details);
            break;
        }
    }
}

void AdminWindow::refreshUserList()
{
    ui->listWidget->clear();
    for (const User& user : users) {
        ui->listWidget->addItem(user.getUsername());
    }
}
void AdminWindow::loadUsersFromFile()
{
    users.clear();
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/users.txt";
    QFile file(filePath);

    qDebug() << "Admin: Attempting to load users from:" << filePath;

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

                    qDebug() << "Admin: Loaded user:" << username << "with role:" << role;
                }
            }
        }

        file.close();
        qDebug() << "Admin: Successfully loaded" << users.size() << "users";
    } else {
        qDebug() << "Admin: Users file doesn't exist or couldn't be opened for reading:"
                 << (file.exists() ? file.errorString() : "File doesn't exist yet");
    }
}

void AdminWindow::listUsers() {
    loadUsersFromFile();

    if (users.empty()) {
        QMessageBox::information(this, "User List", "No users found in the system.");
        return;
    }

    QString userList = "All Users in System:\n\n";
    userList += "Username\tRole\n";
    userList += "-----------------------------\n";

    for (const User& user : users) {
        userList += user.getUsername() + "\t" + user.getRole() + "\n";
    }

    userList += "\n-----------------------------\n";
    userList += "Total Users: " + QString::number(users.size());

    QMessageBox::information(this, "User List", userList);
}

void AdminWindow::on_listUsers_clicked()
{
    listUsers();
}

void AdminWindow::saveUsersToFile()
{
    QString filePath = "/Users/bassantibrahim/Desktop/InventoryProject/users.txt";
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for (const User& user : users) {
            out << user.getUsername() << "," << user.getPassword() << "," << user.getRole() << "\n";
        }

        file.close();
        qDebug() << "Admin: Users saved to file.";
    } else {
        qDebug() << "Admin: Failed to open file for writing: " << file.errorString();
    }
}

void AdminWindow::on_createUser_clicked()
{
    signup* signUpWindow = new signup(this);

    if (signUpWindow->exec() == QDialog::Accepted) {
        qDebug() << "New user has been created and saved!";

    }

    delete signUpWindow;
}

