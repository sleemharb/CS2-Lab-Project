#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardPaths>
#include <QListWidgetItem>
#include "mainwindow.h"
#include "user.h"
using namespace std;

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_deleteUser_clicked();
    void on_adminLogout_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void on_createUser_clicked();

private:
    Ui::AdminWindow *ui;
    std::vector<User> users;
    MainWindow *mainwindow;
    void loadUsersFromFile();
    void saveUsersToFile();
    void refreshUserList();
    void listUsers();
};

#endif // ADMINWINDOW_H
