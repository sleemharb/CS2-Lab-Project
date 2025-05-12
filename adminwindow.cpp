#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMainWindow>
#include <QStandardPaths>
#include <QTableWidgetItem>
#include <QHeaderView>

AdminWindow::AdminWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Page");
    loadUsersFromFile();
    refreshUserList();
    connect(ui->tableWidget, &QTableWidget::cellClicked, this, &AdminWindow::on_tableWidget_cellClicked);
    connect(ui->createUser, &QPushButton::clicked, this, &AdminWindow::on_createUser_clicked);
    connect(ui->adminLogout, &QPushButton::clicked, this, &AdminWindow::on_adminLogout_clicked);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_deleteUser_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Error", "Please select a user to delete.");
        return;
    }

    QString username = ui->tableWidget->item(row, 0)->text();

    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(this, "Confirm Deletion",
                                    "Are you sure you want to delete user '" + username + "'?",
                                    QMessageBox::Yes | QMessageBox::No);

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

void AdminWindow::on_tableWidget_cellClicked(int row, int column)
{
    QString username = ui->tableWidget->item(row, 0)->text();
    for (const User& user : users) {
        if (user.getUsername() == username) {
            QString details = "Username: " + user.getUsername() + "\n" + "Role: " + user.getRole();
            break;
        }
    }
}

void AdminWindow::refreshUserList()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(users.size());
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Username" << "Role");

    for (int row = 0; row < users.size(); ++row) {
        QTableWidgetItem* userItem = new QTableWidgetItem(users[row].getUsername());
        userItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 0, userItem);

        QTableWidgetItem* roleItem = new QTableWidgetItem(users[row].getRole());
        roleItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 1, roleItem);
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
}

void AdminWindow::loadUsersFromFile()
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

void AdminWindow::saveUsersToFile()
{
    QString filePath = "/Users/Xenaragy/Desktop/InventoryProject/users.txt";
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for (const User& user : users) {
            out << user.getUsername() << "," << user.getPassword() << "," << user.getRole() << "\n";
        }

        file.close();
    }
}
void AdminWindow::on_createUser_clicked()
{
    this->hide();
    signup signUpWindow(this);
    signUpWindow.exec();
    this->show();
    loadUsersFromFile();
    refreshUserList();
}
