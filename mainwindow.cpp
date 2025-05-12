#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("User Management System");
    login = new class Login(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete login;

}


void MainWindow::on_mloginButton_clicked()
{
    login->show();
}

