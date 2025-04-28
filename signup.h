#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMainWindow>
#include "user.h"
#include <vector>
using namespace std;

namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_signupButton_clicked();
    void on_displayUsersButton_clicked();

private:
    Ui::signup *ui;
    vector<User> users;
    // New method to load users from file
    void loadUsersFromFile();
    void displayAllUsers();
};

#endif // SIGNUP_H
