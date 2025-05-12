#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <vector>
#include "user.h"

class AdminWindow;
class ManagerWindow;
class EmployeeWindow;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_LLogin_clicked();

private:
    Ui::Login *ui;
    std::vector<User> users;

    AdminWindow *adminWindow;
    ManagerWindow *managerWindow;
    EmployeeWindow *employeeWindow;

    void loadUsersFromFile();
    void openAdminWindow();
    void openManagerWindow(const User& loggedInUser);
    void openEmployeeWindow();
};

#endif // LOGIN_H
