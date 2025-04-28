#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set window title
    this->setWindowTitle("User Management System");

    signup = new class signup(this);
    login = new class login(this);
}

MainWindow::~MainWindow()
{
    delete ui;
        delete signup;
        delete login;

}


void MainWindow::on_msignupButton_clicked()
{
    // Show the signup window
    signup->show();
}


void MainWindow::on_mloginButton_clicked()
{
    // Show the login window
    login->show();
}

