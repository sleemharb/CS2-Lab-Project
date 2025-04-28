#include "employeewindow.h"
#include "ui_employeewindow.h"

EmployeeWindow::EmployeeWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EmployeeWindow)
{
    ui->setupUi(this);
}

EmployeeWindow::~EmployeeWindow()
{
    delete ui;
}
